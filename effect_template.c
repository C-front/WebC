#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <emscripten.h>

typedef struct {
    void (*effect)();
    int* dependencies;
    int* prev_dependencies;
    int dep_count;
} Effect;

static Effect** effects = NULL;
static int effect_count = 0;

static int* create_dependencies(const int* deps, int count) {
    int* new_deps = (int*)malloc(count * sizeof(int));
    
    for (int i = 0; i < count; i++) {
        new_deps[i] = deps[i];
    }
    return new_deps;
}

static bool deps_changed(const int* old_deps, const int* new_deps, int count) {
    for (int i = 0; i < count; i++) {
        if (old_deps[i] != new_deps[i]) {
            return true;
        }
    }
    return false;
}

static void free_effect(Effect* eff) {
    if (eff) {
        free(eff->dependencies);
        free(eff->prev_dependencies);
        free(eff);
    }
}

EMSCRIPTEN_KEEPALIVE
void register_effect(
    void (*effect)(),
    const int* dependencies, 
    int dep_count
) {
    Effect* eff = (Effect*)malloc(sizeof(Effect));
    
    eff->dependencies = create_dependencies(dependencies, dep_count);
    eff->prev_dependencies = create_dependencies(dependencies, dep_count);
    eff->dep_count = dep_count;
    eff->effect = effect;
    
    effects = (Effect**)realloc(effects, (effect_count + 1) * sizeof(Effect*));
    effects[effect_count++] = eff;
    
    eff->effect();
}

EMSCRIPTEN_KEEPALIVE
void update_dependencies(int effect_index, const int* new_deps, int dep_count) {
    
    Effect* eff = effects[effect_index];
    
    bool changed = deps_changed(eff->prev_dependencies, new_deps, dep_count);
    
    for (int i = 0; i < dep_count; i++) {
        eff->dependencies[i] = new_deps[i];
    }
    
    if (changed) {   
        for (int i = 0; i < dep_count; i++) {
            eff->prev_dependencies[i] = new_deps[i];
        }
        
        if (eff->effect) {
            eff->effect();
        }
    }
}

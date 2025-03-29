#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

typedef struct {
    int value;
} State;

State* create_state(int initial_value) {
    State* state = (State*)malloc(sizeof(State));
    state->value = initial_value;
    return state;
}

void set_state(State* state, int new_value) {
    state->value = new_value;
}

int get_state(State* state) {
    return state->value;
}

EMSCRIPTEN_KEEPALIVE
State* init_state(int initial_value) {
    return create_state(initial_value);
}

EMSCRIPTEN_KEEPALIVE
void update_state(State* state, int new_value) {
    set_state(state, new_value);
}

EMSCRIPTEN_KEEPALIVE
int read_state(State* state) {
    return get_state(state);
}

EMSCRIPTEN_KEEPALIVE
void free_state(State* state) {
    free(state);
}

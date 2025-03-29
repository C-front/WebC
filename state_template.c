#include <stdio.h>
#include <stdlib.h>

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

State* init_state(int initial_value) {
    return create_state(initial_value);
}

void update_state(State* state, int new_value) {
    set_state(state, new_value);
}

int read_state(State* state) {
    return get_state(state);
}

void free_state(State* state) {
    free(state);
}

int main() {
    State* my_state = init_state(10);

    printf("start: %d\n", read_state(my_state));

    update_state(my_state, 20);
    printf("update: %d\n", read_state(my_state));

    update_state(my_state, 30);
    printf("update 2: %d\n", read_state(my_state));

    free_state(my_state);

    return 0;
}
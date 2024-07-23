#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 100
#define MAX_TRANSITIONS 100

typedef struct {
    int num_states;
    int num_transitions;
    int transitions[MAX_STATES][MAX_TRANSITIONS]; 
    int epsilon_transitions[MAX_STATES][MAX_TRANSITIONS]; 
    int epsilon_transition_count[MAX_STATES];
} NFA;

void initialize_nfa(NFA *nfa, int num_states) {
    nfa->num_states = num_states;
    nfa->num_transitions = 0;
 {
 for (int i = 0; i < num_states; i++) {
        nfa->epsilon_transition_count[i] = 0;
    }
}

void add_epsilon_transition(NFA *nfa, int from_state, int to_state) {
    nfa->epsilon_transitions[from_state][nfa->epsilon_transition_count[from_state]++] = to_state;
}

void find_epsilon_closure(NFA *nfa, int state, int *closure, int *closure_size) {
    int stack[MAX_STATES];
    int top = -1;
    int visited[MAX_STATES] = {0};

    
    stack[++top] = state;
    visited[state] = 1;

    while (top >= 0) {
        int current_state = stack[top--];
        closure[(*closure_size)++] = current_state;

        for (int i = 0; i < nfa->epsilon_transition_count[current_state]; i++) {
            int next_state = nfa->epsilon_transitions[current_state][i];
            if (!visited[next_state]) {
                stack[++top] = next_state;
                visited[next_state] = 1;
            }
        }
    }
}

void print_epsilon_closure(NFA *nfa) {
    for (int i = 0; i < nfa->num_states; i++) {
        int closure[MAX_STATES];
        int closure_size = 0;
        find_epsilon_closure(nfa, i, closure, &closure_size);
        printf("e-closure of state %d: {", i);
        for (int j = 0; j < closure_size; j++) {
            printf("%d", closure[j]);
            if (j < closure_size - 1) {
                printf(", ");
            }
        }
        printf("}\n");
    }
}

int main() {
    NFA nfa;
    initialize_nfa(&nfa, 4); 
    add_epsilon_transition(&nfa, 0, 1);
    add_epsilon_transition(&nfa, 1, 2);
    add_epsilon_transition(&nfa, 2, 3);
    add_epsilon_transition(&nfa, 1, 3);
    add_epsilon_transition(&nfa, 3, 0);


    print_epsilon_closure(&nfa);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAPE_LENGTH 100
#define MAX_STATES 10
#define BLANK '_'


typedef struct {
    int current_state;
    char read_symbol;
    char write_symbol;
    char move_direction; 
    int next_state;
} Transition;


typedef struct {
    char tape[TAPE_LENGTH];
    int head_position;
    int current_state;
    Transition transitions[MAX_STATES][TAPE_LENGTH];
    int num_transitions;
} TuringMachine;

void initialize_tm(TuringMachine *tm, const char *input) {
    memset(tm->tape, BLANK, TAPE_LENGTH);
    strncpy(tm->tape, input, strlen(input));
    tm->head_position = 0;
    tm->current_state = 0;
    tm->num_transitions = 0;
}

void add_transition(TuringMachine *tm, int current_state, char read_symbol, char write_symbol, char move_direction, int next_state) {
    Transition t = {current_state, read_symbol, write_symbol, move_direction, next_state};
    tm->transitions[current_state][read_symbol] = t;
    tm->num_transitions++;
}

void simulate_tm(TuringMachine *tm) {
    while (tm->current_state != -1) { 
        char read_symbol = tm->tape[tm->head_position];
        Transition t = tm->transitions[tm->current_state][read_symbol];
        
       
        printf("State: %d, Head Position: %d, Tape: %s\n", tm->current_state, tm->head_position, tm->tape);
        
        tm->tape[tm->head_position] = t.write_symbol;
        tm->current_state = t.next_state;

        if (t.move_direction == 'L') {
            tm->head_position--;
        } else if (t.move_direction == 'R') {
            tm->head_position++;
        }

      
        if (tm->head_position < 0 || tm->head_position >= TAPE_LENGTH) {
            printf("Error: Head moved out of tape bounds.\n");
            break;
        }
    }
}

int main() {
    TuringMachine tm;
    initialize_tm(&tm, "1101"); 

    
    add_transition(&tm, 0, '1', 'X', 'R', 1);
    add_transition(&tm, 1, '1', '1', 'R', 1);
    add_transition(&tm, 1, '0', '0', 'R', 1);
    add_transition(&tm, 1, BLANK, BLANK, 'L', -1); 

  
    simulate_tm(&tm);

    return 0;
}


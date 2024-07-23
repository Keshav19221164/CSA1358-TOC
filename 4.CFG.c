#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int E();
int E_prime();
int T();
int T_prime();
int F();
void error(const char *message);
const char *input;
int current_position;
int match(char expected) {
    if (input[current_position] == expected) {
        current_position++;
        return 1;
    }
    return 0;
}
int E() {
    if (T()) {
        if (E_prime()) {
            return 1;
        }
    }
    return 0;
}
int E_prime() {
    if (match('+')) {
        if (T()) {
            if (E_prime()) {
                return 1;
            }
        }
        return 0;
    }
    return 1;
}
int T() {
    if (F()) {
        if (T_prime()) {
            return 1;
        }
    }
    return 0;
}
int T_prime() {
    if (match('*')) {
        if (F()) {
            if (T_prime()) {
                return 1;
            }
        }
        return 0;
    }
    return 1; 
}
int F() {
    if (match('(')) {
        if (E()) {
            if (match(')')) {
                return 1;
            }
        }
        return 0;
    } else if (isalpha(input[current_position])) { 
        current_position++;
        return 1;
    }
    return 0;
}


void error(const char *message) {
    fprintf(stderr, "Error: %s at position %d\n", message, current_position);
    exit(1);
}

int main() {
    char buffer[100];
    printf("Enter a string: ");
    scanf("%s", buffer);
    input = buffer;
    current_position = 0;

    if (E() && input[current_position] == '\0') {
        printf("The string is valid.\n");
    } else {
        error("Invalid string");
    }

    return 0;
}


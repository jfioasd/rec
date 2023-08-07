#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int sp_ret;

void printStack(int sp, int *stack, bool nl) {
    printf(" [ ");
    for(int x=0; x < sp; x ++) {
        printf("%d ", stack[x]);
    }
    printf("] ");
    if (nl) {
        printf("\n");
    }
}

char* skip_bkt(char *pc, char up, char down, int step) {
    char *offset = pc + step;
    int level = 1;

    while (*offset && level > 0) {
        level += *offset == up;
        level -= *offset == down;
        offset += step;
    }

    return offset;
}

bool run(char *prog, int sp, int *stack) {
    // Return value = whether we need to break out of an infinite loop
    // (0) = no, (1) = yes
    int x, v, tmp;
    bool debug = false;

    for(char *pc = prog; *pc; pc++) {
        sp = (sp < 0) ? 0 : sp;

        switch(*pc) {
            case '0': case '1': case '2':
            case '3': case '4': case '5':
            case '6': case '7': case '8':
            case '9':
                if(isdigit(*(pc-1)))
                    stack[sp-1] = stack[sp-1] * 10 + *pc - 48;
                else
                    stack[sp++] = *pc - 48;
                break;

            case '/':
                stack[sp-1] += 1;
                break;

            case '\\':
                stack[sp-1] -= 1;
                break;

            case ':':
                x = stack[sp-1];
                tmp = (x < 0) ? -1: sp - 2;
                stack[sp-1] = stack[tmp - x];
                break;

            case ';':
                x = stack[sp-1];
                v = stack[sp-2];
                tmp = (x < 0) ? -1 : sp - 3;
                stack[tmp - x] = v;
                sp -= 2;
                break;

            case '^':
                sp --;
                if (stack[sp] == 0)
                    pc = skip_bkt(pc, '[', ']', 1) - 1;
                break;

            case ']':
                pc = skip_bkt(pc, ']', '[', -1);
                break;

            // Debugging commands
            case 'P':
                printf("%d\n", stack[sp-1]);
                sp --;
                break;

            case 'R':
                scanf("%d", &v);
                stack[sp++] = v;
                break;

            case 'p':
                putchar(stack[sp-1]);
                sp --;
                break;

            case 'r':
                v = getchar();
                stack[sp++] = v;
                break;

            case 's':
                printStack(sp, stack, true);
                break;

            case 'b':
                debug = true;
                break;
        }

        if (debug && !isspace(*pc)) {
            printf("(%d) %c", (int)(pc-prog), *pc);
            printStack(sp, stack, false);

            char cmd;
            if (scanf("%c", &cmd) == EOF) {
                exit(0);
            }

            switch (cmd){
                // Don't need to handle for '\n' case
                case 'c':
                    getchar();
                    debug = false;
                    break;
                case 'q':
                    exit(0);
                    break;
            }
        }
    }
    
    // For REPL (since local values are lost across function calls)
    sp_ret = sp;

    return 0;
}

int main(int argc, char **argv) {
    // *stack = pointer to bottom of stack
    int *stack = (int*)malloc(sizeof(int) * 20000);
    int sp = 0;

    if (argc < 2) {
        char *s = (char*) malloc(sizeof(char) * 100);
        unsigned long len = 0;
        
        for(;;) {
            printf("r> ");
            len = getline(&s, &len, stdin);
            
            if(len == -1) {
                free(s);
                break;
            }

            run(s, sp, stack);
            sp = sp_ret;

            printStack(sp, stack, true);
        }
    } else {
        FILE *fp = fopen(argv[1], "r");
        char prog[2000] = {};

        fread(&prog, sizeof(char), -1, fp);
        fclose(fp);

        run(prog, sp, stack);
    }

    free(stack);
}

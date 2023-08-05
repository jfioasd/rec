#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// "stack" basically means the pointer
//  to the bottom of the stack.
int *stack, *sp;
int *stack_ret, *sp_ret;

void printStack(int *sp, int *stack, bool nl) {
    printf(" s: [ ");
    for(int *x = stack; x < sp; x ++) {
        printf("%d ", *x);
    }
    printf("] ");
    if (nl) {
        printf("\n");
    }
}

bool run(char *prog, int *sp, int *stack) {
    // Return value = whether we need to break
    //                out of an infinite loop
    // (0) = no, (1) = yes
    int x, v, *tmp;
    char *right;
    int level = 0;

    bool debug = false;
    for(char *pc = prog; *pc; pc++) {
        switch(*pc) {
            case '0': case '1': case '2':
            case '3': case '4': case '5':
            case '6': case '7': case '8':
            case '9':
                if(isdigit(*(pc-1)))
                    *(sp-1) = *(sp-1) * 10 + *pc - 48;
                else
                    *(sp++) = *pc - 48;
                break;
            case '/':
                *(sp-1) += 1;
                break;
            case '\\':
                *(sp-1) -= 1;
                break;
            case ':':
                x = *(sp-1);
                tmp = (x < 0) ? stack - 1: sp - 2;
                *(sp-1) = *(tmp - x);
                break;
            case ';':
                x = *(sp-1);
                v = *(sp-2);
                tmp = (x < 0) ? stack - 1 : sp - 3;
                *(tmp - x) = v;
                sp -= 2;
                break;
            case '^':
                sp --;
                if (*sp == 0)
                    return 1;
                break;
            case '[':
                right = pc + 1;
                level = 1;
                while(*right && level > 0) {
                    level += *right == '[';
                    level -= *right == ']';
                    right ++;
                }
                *(right-1) = '\0';

                while(run(pc+1, sp, stack) == 0);

                *(right-1) = ']';
                pc = right;
                break;

            // Debugging commands
            case 'P':
                printf("%d\n", *(sp-1));
                sp --;
                break;
            case 'R':
                scanf("%d", &v);
                *(sp++) = v;
                break;
            case 'p':
                putchar(*(sp-1));
                sp --;
                break;
            case 'r':
                v = getchar();
                *(sp++) = v;
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
            if (getchar() == -1)
                exit(0);
        }
    }

    stack_ret = stack;
    sp_ret = sp;
    return 0;
}

int main(int argc, char **argv) {
    stack = (int*)malloc(20000 * sizeof(int));
    sp = stack;

    if (argc < 2) {
        char *s = (char*) malloc(100 * sizeof(char));
        unsigned long len = 0;
        for(;;) {
            printf("r> ");
            len = getline(&s, &len, stdin);

            if(len == -1) {
                free(s);
                break;
            }

            run(s, sp, stack);
            
            printStack(sp_ret, stack_ret, true);
            stack = stack_ret;
            sp = sp_ret;
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

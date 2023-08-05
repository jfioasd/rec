#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// *stack = pointer to bottom of stack
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

bool run(char *prog, int *sp, int *stack) {
    // Return value = whether we need to break out of an infinite loop
    // (0) = no, (1) = yes
    int x, v, *tmp;
    char *right;
    int level = 0;

    bool debug = false;
    for(char *pc = prog; *pc; pc++) {
        sp = (sp < stack) ? stack : sp;
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
                    pc = skip_bkt(pc, '[', ']', 1) - 1;
                break;
            case ']':
                pc = skip_bkt(pc, ']', '[', -1);
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
            case 'x':
                debug = false;
                break;
        }
        if (debug && !isspace(*pc)) {
            printf("(%d) %c", (int)(pc-prog), *pc);
            printStack(sp, stack, false);
            if (getchar() == -1)
                exit(0);
        }
    }

    // For REPL (since local values are lost across function calls)
    stack_ret = stack;
    sp_ret = sp;
    return 0;
}

int main(int argc, char **argv) {
    stack = (int*)malloc(sizeof(int) * 20000);
    sp = stack;

    if (argc < 2) {
        char *s = (char*) malloc(sizeof(char) * 1);
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

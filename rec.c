#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int run(char pc[], int *sp, int *stack) {
    // Return value = whether we need to break
    //                out of an infinite loop
    // (1) = no, (0) = yes
    int x, v;
    char *right;
    int level = 0;
    for(; *pc; pc++) {
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
                if (x < 0)
                    *(sp-1) = *(stack-1-x);
                else
                    *(sp-1) = *(sp-2-x);
                break;
            case ';':
                x = *(sp-1);
                v = *(sp-2);
                if (x < 0)
                    *(stack-1-x) = v;
                else
                    *(sp-3-x) = v;
		        sp -= 2;
                break;
            case '^':
                sp --;
                if (!*sp)
                    return 0;
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

                while(run(pc+1, sp, stack));
                
                *(right-1) = ']';
                pc = right;
                break;

            // Debugging commands
            case 'P':
                printf("%d", *(sp-1));
                sp --;
                break;
        }
    }
    // Print whole stack
    printf("[ ");
    for(int *x = stack; x < sp; x ++) {
        printf("%d ", *x);
    }
    printf("]\n");

    return 1;
}

int main(int argc, char **argv) {
    int *stack = (int*)malloc(20000 * sizeof(int));
    int *sp = stack;

    FILE *fp = fopen(argv[1], "r");
    char prog[2000] = {};

    fread(&prog, sizeof(char), -1, fp);
    fclose(fp);

    run(prog, sp, stack);
    free(stack);
}

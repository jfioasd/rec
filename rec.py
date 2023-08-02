import sys

stack = []

def run_rec(prog):
    ptr = 0
    while ptr < len(prog):
        if prog[ptr] in '0123456789':
            if ptr>0 and prog[ptr-1] in '0123456789':
                stack.append(stack.pop()*10+int(prog[ptr]))
            else:
                stack.append(int(prog[ptr]))
        elif prog[ptr] == '/':
            stack[-1] += 1
        elif prog[ptr] == '\\':
            stack[-1] -= 1
        elif prog[ptr] == ':':
            x = stack.pop()
            stack.append(stack[~x])
        elif prog[ptr] == ';':
            x, v = stack.pop(), stack.pop()
            stack[~x] = v
        elif prog[ptr] == '^':
            assert(stack.pop() != 0)

        elif prog[ptr] == '[':
            level = 1
            right = ptr + 1
            while level:
                level += prog[right] == '['
                level -= prog[right] == ']'
                right += 1

            sliced_prog = prog[ptr+1:right-1]
            while True:
                try:
                    run_rec(sliced_prog)
                except:
                    break

            ptr = right
            continue

        # For debugging purposes
        elif prog[ptr] == 'P':
            print(stack.pop())
        elif prog[ptr] == 'R':
            stack.append(int(input()))

        ptr += 1

if __name__ == '__main__':
    prog = open(sys.argv[-1]).read()
    if '-i' in sys.argv:
        stack = eval(input())

    run_rec(prog)
    if '-d' in sys.argv:
        print(stack)

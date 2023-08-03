import sys

stack = []

def run_rec(prog):
    ptr = 0
    try:
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
                if not stack.pop():
                    raise AssertionError

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
                    except AssertionError:
                        break

                ptr = right
                continue

            # For debugging purposes
            elif prog[ptr] == 'P':
                print(stack.pop())
            elif prog[ptr] == 'R':
                stack.append(int(input()))
            elif prog[ptr] == 's':
                last = max(0, ptr-1)
                while last and prog[last].isspace():
                    last -= 1
                print(f'({prog[last]} {last})', stack)

            ptr += 1
    except IndexError as e:
        print("IndexError:", e)
        print(f's: ({prog[ptr]} {ptr})', stack)
        exit(0)

if __name__ == '__main__':
    if "-r" not in sys.argv:
        prog = open(sys.argv[-1]).read()
        run_rec(prog)
    else:
        print("Type Ctrl-D to exit")
        while True:
            line = input("r> ")
            run_rec(line)
            print(stack)

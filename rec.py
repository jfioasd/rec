import sys

stack = []

def run_rec(prog, debug = False):
    "Return value = whether we need to break out of a while loop"
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
                    return True

            elif prog[ptr] == ']':
                raise IndexError('unbalanced brackets')
            elif prog[ptr] == '[':
                level = 1
                right = ptr + 1
                while level:
                    level += prog[right] == '['
                    level -= prog[right] == ']'
                    right += 1

                sliced_prog = prog[ptr+1:right-1]
                while True:
                    x = run_rec(sliced_prog)
                    if x == True:
                        break

                ptr = right
                continue

            # For debugging purposes
            elif prog[ptr] == 'P':
                print(stack.pop())
            elif prog[ptr] == 'R':
                stack.append(int(input()))
            elif prog[ptr] == 'p':
                print(end = chr(stack.pop()))
            elif prog[ptr] == 'r':
                x = sys.stdin.read(1)
                if x == '':
                    stack.append(-1)
                else:
                    stack.append(ord(x))
            elif prog[ptr] == 's':
                last = max(0, ptr-1)
                while last and prog[last].isspace():
                    last -= 1
                print(f'({last}) {prog[last]}', stack)
            elif prog[ptr] == 'b':
                debug = True

            if debug and not prog[ptr].isspace():
                x = input(f'({ptr}) {prog[ptr]} ' + str(stack) + ' ')

            ptr += 1

    except Exception as e:
        if str(e) == 'string index out of range':
            e = 'unbalanced brackets'
        print(e)
        print(f's: ({ptr}) {prog[ptr]}', stack)
        exit(1)

    return False

if __name__ == '__main__':
    if len(sys.argv) < 2 or "-r" in sys.argv:
        while True:
            try:
                line = input("r> ")
            except EOFError:
                break
            run_rec(line)
            print("s:",stack)
    else:
        prog = open(sys.argv[-1]).read()
        try:
            if '-d' in sys.argv:
                run_rec(prog, True)
            else:
                run_rec(prog)
        except EOFError:
            pass

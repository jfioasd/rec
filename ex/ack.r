0 0 0\                        [0^ Initialize stack as [0 0 -1].
                                  -1 is used to check if the stack has only one item left ]
R R                           [0^ Push arguments onto stack ]
[ 0\\; 0\;                    [0^ Loop: store m & n into the first two numbers. [m n -1] ]
  [ 0\\:/         0\: ^       [0^ Cond1: Push n+1 if m = 0. ]
    0\: \0; 1     0\\:^       [0^ Cond2: Push m-1, 1 if n = 0. ]
    0\: 0; 0\\: \ 0   ^ ]     [0^ Else: Push m-1, m, n-1. ]
  1: / ^                      [0^ Check if second-to-last item + 1 is 0. (i.e. = -1)]
] P                           [0^ After loop: print resulting value on stack.]

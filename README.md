## Rec
This repository holds the Python & C interpreters for https://esolangs.org/wiki/Rec.

The language is summarized below:

|Command|Behavior|
|:--:| :--:|
|`123`| Push the non-negative number onto the stack.|
|`/`| Successor; increment TOS. |
|`\`| Predecessor; decrement TOS.|
|`:`| Load; Pops `x`, pushes `stack[~x]`. |
|`;`| Store; Pops `v` and `x`. Assigns `stack[~x]` to `v`.|
|`[ ... ]`| Infinite loop; executes <code>...</code> forever. |
|`^`| Pops `x`. If `x == 0`, break out of innermost `[ ... ]` loop. <br>(Or terminates program, if not in `[ ... ]` loop.) |

## Interpreter Spec
Both interpreters hosted here have a REPL (which you can access with no CLI arguments) and a debugger (which prints program info as the interpreter executes commands). (Use enter to step through the debugger.)

You can use <code>Ctrl-D</code> to exit both the interpreter and the debugger.

### Added Commands
* `P`: Pop & print TOS as integer.
* `R`: Read an integer from input, and push the value.
* `p`: Pop & print TOS as a char.
* `r`: Read a char from input, and push the ord value.
* `s`: Prints the entire stack at the current point of execution.
* `b`: Breakpoint; starts debug mode at this part of program.

## See also
* [Recur interpreter](https://github.com/laerling/recur/), where you can find some examples of an old version of this language.
## Rec
This repository holds the Python & C interpreters for [Rec](https://esolangs.org/wiki/Rec). (Though I don't want to maintain the Python interpreter anymore.)

The language is summarized below:

|Command|Behavior|
|:--:| :--:|
|`123`| Push the non-negative number onto the stack.|
|`/`| Successor; increment TOS. |
|`\`| Predecessor; decrement TOS.|
|`:`| Load; Pops `x`, pushes `stack[~x]`. |
|`;`| Store; Pops `v` and `x`. Assigns `stack[~x]` to `v`.|
|`[ ... ]`| Infinite loop; executes <code>...</code> forever. |
|`^`| Pops `x`. If `x == 0`, break out of innermost `[ ... ]` loop. <br>(Or terminates program, if not in a `[ ... ]` loop.) |

## Pitfalls
These tips will save you a lot of bugs when using the language.

* `-1` is `0\`, not `1\` (which is `0`)!
* `;` pops 2 values from the stack!
  * E.g. `[1 2 3 0 1]`: when `;` is called, the new TOS is `3`, not `0`. So this will turn the stack to `[1 0 3]`.

## Interpreter Spec
Both interpreters here have a REPL (which you can access with no CLI arguments) and a debugger (which you may enter by adding breakpoints `b` in the program).

Use Enter to step through the debugger.

You can use <code>Ctrl-D</code> to exit the REPL.

### Added Commands
* `P`: Pop & print TOS as integer.
* `R`: Read an integer from input, and push the value.
* `p`: Pop & print TOS as a char.
* `r`: Read a char from input, and push the ord value.
* `s`: Prints the entire stack at the current point of execution.
* `b`: Breakpoint; starts debugger at this part of program.

### Commands in the debugger (C interpreter)
* `\n`: Step to next iteration.
* `c`: Continue; Stop displaying debugging information until the next breakpoint.
* `q`: Quit; Exit the debugger. (You can't use Ctrl-D because it's broken; I don't know how to fix it.)

### Python-only flags
Admittedly, these flags are kind of useless.
* `-r`: Enter REPL mode.
* `-d`: Enter debugger mode for the entire program.

## See also
* [Recur interpreter](https://github.com/laerling/recur/) (written by laerling), where you can find some examples of an old version of this language.

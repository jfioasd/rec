# rec
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

# See also
* [Recur interpreter](https://github.com/laerling/recur/), where you can find some examples of an old version of this language.

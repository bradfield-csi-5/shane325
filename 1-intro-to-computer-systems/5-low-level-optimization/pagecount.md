### Pagecount program
Here are my answers and notes regarding the `pagecount.c` program.

**Which instructions would you expect the compiler to generate for this function?**
- I would expect the compiler to reserve some register space for 12 variables.
- I would expect to see a loop, with a counter register, and an expression.
- There will be a set of instructions for the `pagecount` function.

**What does it in fact generate?**
- Lot's of branches (L0-7).
- Lot's of `mov`, `add`, and _shift_ instructions when indexing into an array with the modulus operator.

- Push `rbp` (callee saved) onto the stack.
- Moves value at stack pointer into register `rbp`.
- Subtracts 144 from the stack pointer (increasing the stack by 144).
- Starts to populate our carved out memory block (the 144).
- Calculates and `mov`'s 1 to the power of 32, 40, 52, 12, 16, and 32.
- 1^32 is initially stored in `rax` and then retrieved from there again (instead of recalculating it).
- Starts the first for loop and branches to `.L4`.
- Compares `i` with the constant 9999999 and jumps to `.l5` is less than.
- Does a lot of calculations and moves before incrementing `i` by 1 and resuming execution at the next line (which is back at `.L4`).
- This loop continues until `i` is not longer less than 9999999.
- Calls `clock` twice.
- Sets `i` back to zero and jumps to `.L6` to start the second for loop.
- `.L6` compares `i` to 9999999 and jumps to `.L7` if less than.
- Again it does the same calculations as `.L5` and also calls `pagecount`.
- `pagecount` calculates two unsigned ints and uses them to bitshift and saves the result in our return register `rax` before returning.
- Control return to `.L7` and it increments `i` and starts the loop over again.
- After the loop finished (back in `.L6`) we call clock once more.
- We calculate two more variables, do some printing and finish.

**If you change the optimization level, is the function substantially different?**

At `-O`:
- Using registers `r12-14` instead.
- Pushing to the stack 5 times.
- Subtracts 64 (not 144) from the stack pointer.
- The array creation and population are unchanged.
- The `ignore` is initialized and calculated later on (after out call to `clock`).
- `.L3` contains all of the logic and expressions for our first for loop. All condensed into one branch.
- Our second loop and all the `pagecount` logic is inlined in `.L4`. It never branches to `pagecount` although this function does exist.o
- In general, more inlining and a lot less instructions. Not jumping around as much.

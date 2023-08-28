### Loop Order
Here are my notes and answers regarding the `loop-order.c` program.

**Which function takes longer to run?**
- My assumption is that the column order will take longer to run (option_two).
- Adding some simple time tracking using `time.h` I was able to show that:
	- `option_one` runs in `4.5ns per element`.
	- `option_two` runs in `13.5ns per element`.
- These results prove that the row order runs a lot faster than the column order.

**Do they execute the same number of instructions?**
- Using `valgrind --tool=cachegrind ./option...` shows the following output:
	- For `option_one`: `I refs:        240,154,416`.
	- For `option_two`: `I refs:        240,154,416`.
- It looks like both function execute the same number of instructions.

**What do you notice about the cache utilization of each program? How much better is one than the other? Does this match your expectations?**
- Running `cg_annotate` on each program I see the following results:
	-  

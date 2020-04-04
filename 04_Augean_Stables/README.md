### 04 Augean Stables :ox:

#### Valgrind:

```bash
valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./a.out
```
**Original**

![stables_original]()

**Corrected**

![!stables_corrected]()

#### AddressSanitizer:

```bash
gcc -O1 -g -fsanitize=address -fno-omit-frame-pointer stables.c
```
**Original**

![stables_original]()

**Corrected**

![!stables_corrected]()
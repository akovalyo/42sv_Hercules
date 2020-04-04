### 04 Augean Stables :ox:

#### Valgrind:

```bash
valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./a.out
```
**Original**

![stables_original](https://github.com/akovalyo/42sv_Hercules/blob/master/04_Augean_Stables/scr/stables_1.png?raw=true)

**Corrected**

![!stables_corrected](https://github.com/akovalyo/42sv_Hercules/blob/master/04_Augean_Stables/scr/stables_2.png?raw=true)

#### AddressSanitizer:

```bash
gcc -O1 -g -fsanitize=address -fno-omit-frame-pointer stables.c
```
**Original**

![stables_original](https://github.com/akovalyo/42sv_Hercules/blob/master/04_Augean_Stables/scr/stables_3.png?raw=true)

**Corrected**

![!stables_corrected](https://github.com/akovalyo/42sv_Hercules/blob/master/04_Augean_Stables/scr/stables_4.png?raw=true)
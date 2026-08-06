# Valgrind Analysis

## Environment and commands

I ran Valgrind in an Ubuntu 24.04 Docker container because Valgrind was unavailable on the host macOS system.

```bash
valgrind --leak-check=full --show-leak-kinds=all ./heap_example
valgrind --leak-check=full --track-origins=yes ./aliasing_example
```

The provided Makefile uses `-Werror`. On Ubuntu, GCC detected the intentional use-after-free in `aliasing_example.c` and rejected the build. For the Valgrind experiment only, I compiled that program without `-Werror`. I did not change the source code.

## `heap_example`: definite memory leak

Valgrind reported:

```text
6 bytes in 1 blocks are definitely lost
by person_new (heap_example.c:21)
by main (heap_example.c:51)
```

### Classification

This is a definite memory leak caused by lost ownership of the heap allocation holding Alice's name.

### Memory object and lifetime

`person_new("Alice", 30)` allocates:

```text
Person structure  <- alice
name buffer        <- alice->name, containing "Alice\0"
```

The name allocation is 6 bytes: five characters plus the terminating null byte. Later, `person_free_partial(alice)` frees the `Person` structure but does not free `alice->name`.

Once the structure is freed, the only pointer that stored the name-buffer address was inside that freed structure. The name buffer remains allocated, but the program no longer has an owning pointer through which it can free it. Therefore Valgrind classifies the six bytes as **definitely lost**.

Bob does not leak because the program frees both `bob->name` and `bob`.

The correction would be to free the owned member before freeing its owner:

```c
free(alice->name);
free(alice);
```

## `aliasing_example`: use-after-free

Before deallocation, the output showed that `a` and `b` had the same address. Therefore they are aliases of one 20-byte heap block holding five `int` values.

```text
a ----\
       -> [0, 11, 22, 33, 44]
b ----/
```

`free(a)` releases this one block. It does not alter `a` or `b`, so both variables retain a dangling address. The allocation's lifetime has ended.

### Error 1: invalid read

Valgrind reported:

```text
Invalid read of size 4
main (aliasing_example.c:42)
Address ... is 8 bytes inside a block of size 20 free'd
```

The expression `b[2]` reads an `int`, which is 4 bytes. Index 2 is 8 bytes after the beginning of the five-element allocation. That access is invalid because the block was already freed at line 38.

### Error 2: invalid write

Valgrind reported:

```text
Invalid write of size 4
main (aliasing_example.c:44)
Address ... is 12 bytes inside a block of size 20 free'd
```

The statement `b[3] = 1234` writes a 4-byte `int` at offset 12. The index is within the original array bounds, but bounds are irrelevant after `free`: the object is no longer alive. This is a use-after-free write.

### Error 3: invalid read

Valgrind reported:

```text
Invalid read of size 4
main (aliasing_example.c:45)
Address ... is 12 bytes inside a block of size 20 free'd
```

The final `printf` reads `b[3]` after the invalid write. This is another use-after-free read.

### Leak result

Valgrind reported:

```text
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 3 errors from 3 contexts
```

Thus, this program has no leak. Its three reported errors are all accesses to memory whose lifetime ended at `free(a)`.

## AI review and correction

An AI-assisted interpretation initially described the three Valgrind reports as three separate memory bugs. That is incomplete. They are three invalid operations, but they share one root cause: `a` and `b` alias the same allocation, and that allocation was freed once through `a`.

Another potentially misleading conclusion is that only `b` becomes dangling. This is false. `free(a)` deallocates the heap block, not the variable `a`; both `a` and `b` retain the former address and both are dangling immediately afterward.

I verified this conclusion against the source code, the identical printed addresses for `a` and `b`, the compiler's use-after-free warnings, and Valgrind's allocation/free stack traces.
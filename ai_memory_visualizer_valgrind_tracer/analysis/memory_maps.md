# Memory Maps: Stack, Heap, and Aliasing Analysis

## Method

I compiled the programs with the provided Makefile and ran them normally. I used the printed addresses to validate the lifetime and aliasing maps below. Addresses are runtime-specific; the important facts are which pointers refer to the same object and when each object is alive.

## 1. `stack_example.c`

`main` calls `walk_stack(0, 3)`. Each recursive invocation has a separate stack frame containing the parameters `depth` and `max_depth`, plus the local variable `marker`.

At depth 0, `marker` is `0`. At depths 1, 2, and 3, its values are `10`, `20`, and `30`. The output shows distinct addresses for `marker` at each depth, proving that every recursive call owns a different local variable.

`walk_stack` also calls `dump_frame("enter", depth)` before recursion and `dump_frame("exit", depth)` after recursion. During each call to `dump_frame`, the stack contains:

```text
Stack frame: dump_frame(label, depth)
  local_int = 100 + depth
  local_buf[16]
  p_local -> local_int
```

For example, at depth 2:

```text
local_int = 102
local_buf[0] = 'C'
p_local = &local_int
```

`p_local` aliases `local_int`: it stores the address of that local variable. It does not point to heap memory. Both `p_local` and `local_int` are valid only while that particular `dump_frame` call is active. When `dump_frame` returns, its frame is removed from the stack and the pointer must not be used.

The output addresses decrease as recursion becomes deeper on this machine. That direction is an implementation detail; the required conclusion is that each active call has an independent stack frame and independent local objects.

## 2. `aliasing_example.c`

`main` contains the stack variables:

```text
a: int *
b: int *
n: int = 5
```

### Allocation and initialization

`main` calls `make_numbers(5)`. Inside `make_numbers`, `arr` receives one heap allocation for five `int` values:

```text
Heap block H1: 5 * sizeof(int) = 20 bytes
H1 = [0, 11, 22, 33, 44]
```

`make_numbers` returns the address of H1 to `a`. Its local variables `i` and `arr` disappear when the function returns, but H1 remains alive because it was allocated on the heap.

```text
Stack in main: a -> H1
Heap:          H1 = [0, 11, 22, 33, 44]  (alive)
```

### Aliasing

The statement `b = a;` copies an address; it does not copy the array.

```text
Stack in main:
  a ----\
         -> H1
  b ----/

Heap:
  H1 = [0, 11, 22, 33, 44]  (alive)
```

The normal run printed the same address for `a` and `b`, and both `a[2]` and `b[2]` were `22`. Therefore, `a` and `b` are aliases of the same allocation.

### Deallocation and invalid accesses

`free(a);` releases H1. `free` does not change either pointer variable automatically.

```text
Stack in main:
  a -> H1 (dangling)
  b -> H1 (dangling)

Heap:
  H1 is freed; no program access is valid.
```

After that call:

- `b[2]` is an invalid read.
- `b[3] = 1234` is an invalid write.
- Printing `b[3]` is another invalid read.

The fact that the normal run printed a value does not make the accesses valid. The allocation has already ended; the behavior is undefined.

## 3. `heap_example.c`

`person_new` makes two allocations for each `Person`:

```text
Person allocation: sizeof(Person)
Name allocation:   strlen(name) + 1
```

After both calls in `main`:

```text
alice -> Person A
           name -> "Alice\0"  (6 bytes)
           age  = 30

bob   -> Person B
           name -> "Bob\0"    (4 bytes)
           age  = 41
```

`bob->name` and `bob` are both freed, so Bob's two allocations are correctly released.

`person_free_partial(alice)` frees only the `Person` structure. It does not free `alice->name`. The pointer to the six-byte `"Alice\0"` allocation is lost when the structure is freed, so that allocation becomes a memory leak.

Correct ownership-aware destruction would be:

```c
free(alice->name);
free(alice);
```

## AI Review and Correction

An AI-generated explanation initially claimed that only `b` becomes dangling after `free(a)` because `a` was passed to `free`. That is incorrect.

`free(a)` releases the heap allocation H1, not the variable named `a`. Since `a` and `b` contain the same address, both pointer values refer to freed storage immediately after the call. Therefore, both are dangling pointers. Assigning `a = NULL` afterward would only change `a`; it would not repair `b`.

The compiler and Valgrind evidence support this correction: the compiler warned about use-after-free, and Valgrind reported invalid reads and writes through `b` after the allocation was freed.
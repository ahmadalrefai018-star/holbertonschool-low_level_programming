# Crash Report: `crash_example.c`

## Observed behavior

The program prints:

```text
crash_example: deterministic NULL dereference (segmentation fault)
requesting n=0
```

It then terminates with a segmentation fault.

Valgrind reported:

```text
Invalid write of size 4
main (crash_example.c:32)
Address 0x0 is not stack'd, malloc'd or (recently) free'd
Process terminating with default action of signal 11 (SIGSEGV)
```

## Root cause

The root cause is a null-pointer dereference at line 32:

```c
nums[0] = 42;
```

`nums[0]` is equivalent to `*(nums + 0)`. Therefore, this statement attempts to write one `int` (4 bytes) through the pointer value stored in `nums`.

The value of `nums` is `NULL` at this point.

## Full causal chain

1. In `main`, `n` is initialized to `0`.
2. `main` calls `allocate_numbers(n)`, which is `allocate_numbers(0)`.
3. `allocate_numbers` tests `if (n <= 0)`.
4. Since `0 <= 0` is true, the function returns `NULL` immediately.
5. No array allocation occurs; `malloc` is not reached for this execution path.
6. `main` stores the returned `NULL` value in its local pointer variable `nums`.
7. Line 32 executes `nums[0] = 42`.
8. This dereferences address `0x0`, which is not a valid writable object.
9. The invalid write produces undefined behavior. In this run, the operating system reports `SIGSEGV`.

## Memory category and lifetime

`nums` is a local pointer variable in `main`, so the variable itself is stored in the stack frame of `main`.

However, its value is `NULL`; it does not point to a stack object or a heap allocation. The invalid access is not a use-after-free and is not an array-bounds error. It is a null-pointer dereference caused by trying to write through a pointer that does not designate any object.

The crash is deterministic for `n = 0` because `allocate_numbers(0)` always follows the early-return path and always returns `NULL`.

## Valgrind interpretation

Valgrind identifies an **invalid write of size 4** because the assignment writes one `int`.

The address is `0x0`, directly confirming that the failing pointer value is `NULL`. The report also identifies line 32 as the exact failing statement.

Valgrind lists 1,024 bytes as “still reachable” when the process terminates. This is not evidence that the program leaked an application allocation. The program ended abruptly at the invalid access, and the remaining block is runtime/library memory still reachable at termination.

## AI suggestions: evaluation

An AI tool could correctly suggest that the program should check whether `nums` is `NULL` before dereferencing it. That is a valid safety measure.

However, an explanation claiming that `malloc` failed would be incorrect for this execution. `malloc` was never called: the `n <= 0` check returned `NULL` first. Similarly, a claim that `free` caused the crash would be incorrect because no call to `free` occurs before line 32.

## Suggested fix

A possible fix is to reject non-positive sizes and check the return value before using it:

```c
nums = allocate_numbers(n);
if (nums == NULL)
    return (1);

nums[0] = 42;
```

For this program, `n` must also be set to a positive value if an array element is intended to exist.
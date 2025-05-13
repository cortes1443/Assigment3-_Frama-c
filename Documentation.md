
# Documentation: `verify_assignment` Function in Frama-C

## Purpose

The function `verify_assignment` is designed to operate on two integers `i` and `j`. It modifies their values deterministically and returns the result of their product after these modifications.

This document explains the purpose, contract, and formal verification of the function using **Frama-C** with the `-wp` (weakest precondition) and `-wp-rte` (runtime error checking) options.

---

## Code

```c
/*@
    requires (i * j + 2 * j + 3 * i == 0);
    ensures \result == 6;
*/
int verify_assignment(int i, int j) {
    j += 3;
    i += 2;

    return i * j;
}
```

---

## Explanation

### 1. `requires (i * j + 2 * j + 3 * i == 0)`

This is the **precondition**. It defines the condition that must be true **before** the function is called in order for the contract to be valid.

This expression can be interpreted as:

```
(i * j) + 2 * j + 3 * i == 0
```

This condition restricts the values of `*i` and `*j` such that, after adding 2 to `*i` and 3 to `*j`, their product will be 6.

We can verify that this works by solving the equation:

Let’s define:
```
x = i, y = j

After the function runs:
new_x = x + 2
new_y = y + 3

We want: (x + 2) * (y + 3) == 6
```

Expanding the product:
```
(x + 2)(y + 3) = xy + 2y + 3x + 6
```

We want this to be equal to 6, so:
```
xy + 2y + 3x + 6 == 6
=> xy + 2y + 3x == 0  ← this is exactly our precondition
```

✅ **Conclusion**: If the precondition is met, then the return value is guaranteed to be 6.

---

### 2. ✅ `ensures \result == 6;`

This is the **postcondition**. It specifies what the function guarantees to return if the precondition was satisfied.

Thanks to the math explained above, the function will always return 6 if called under the precondition constraint.

---

## Formal Verification with Frama-C

You can verify this contract automatically using:

```bash
frama-c -wp -wp-rte verify_assignment.c
```

- `-wp` checks that the function obeys the logic of the contract (pre/post conditions).
- `-wp-rte` verifies that there are no runtime errors such as:
  - Dereferencing null pointers
  - Integer overflows
  - Division by zero
  - Memory access errors

If all is correct, Frama-C will show no alarms or verification failures, confirming that the function is both **logically correct** and **safe** under the specified conditions.
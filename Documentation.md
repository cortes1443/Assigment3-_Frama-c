
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
We want to prove the validity of the following Hoare triple:

```
{ i*j + 2*j + 3*i = 0 } 
j := j + 3; 
i := i + 2 
{ i * j = 6 }
```

---

## Step 1: Apply the composition rule `{P} S1; S2 {Q}`

We use the backward composition rule:

```
{P} S1; S2 {Q} ⇔ {P} S1 {R} ∧ {R} S2 {Q}
```

In this case:

- `S1 = j := j + 3`
- `S2 = i := i + 2`
- `Q = i * j = 6`

We define:

- `R = i := i + 2 {i * j = 6}`

---

## Step 2: Backward substitution in the postcondition

Apply the assignment `i := i + 2` backward:

```
i * j = 6
[i -> i + 2] ⇒ (i + 2) * j = 6
```

So:

```
R = (i + 2) * j = 6
```

---

## Step 3: Backward substitution in the previous assignment

Now apply the assignment `j := j + 3` backward:

```
(i + 2) * j = 6
[j -> j + 3] ⇒ (i + 2) * (j + 3) = 6
```

---

## Step 4: Expand the expression

Expanding the product:

```
(i + 2) * (j + 3) = i*j + 2*j + 3*i + 6 = 6
```

Subtracting 6 from both sides:

```
i*j + 2*j + 3*i = 0
```

---

## Conclusion

We have verified that the precondition:

The Hoare triple is verified.

---

### 2.  `ensures \result == 6;`

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

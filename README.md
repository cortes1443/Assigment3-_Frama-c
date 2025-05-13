
# `verify_assignment` - Formal Verification with Frama-C

- **Full Name:** Juan Diego Cortes Galvis

---

## Environment & Tools

- **Operating System:** WSL (Windows Subsystem for Linux) 2.4.13.0
- **Frama-C Version:** Frama-C 25.0 (Manganese)
- **GCC Compiler:** gcc (Debian 12.2.0-14)
- **Automated Prover:** alt-ergo version 2.4.1
- **Editor Used:** GNU Nano 7.2
---

## How to Run the Verification

1. **Save the following C code into a file named `root.c`:**

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

2. **Open a terminal and run Frama-C with the following command:**

```bash
frama-c -wp -wp-rte root.c
```

3. **Expected Output:**
   If the contract is correct and no runtime errors are detected, Frama-C should display a message indicating successful proof and no alarms.

---

## 📚 Reference Sources

- **ChatGPT** by OpenAI: Used for discussion, explanation of ACSL contracts, and general support.
- **Frama-C WP Tutorial** by Allan Blanchard:
  - Title: *"Getting started with Frama-C WP"*
  - URL: [https://allan-blanchard.fr/publis/frama-c-wp-tutorial-en.pdf](https://allan-blanchard.fr/publis/frama-c-wp-tutorial-en.pdf)

These sources helped understand how to write formal specifications in ACSL and verify them using Frama-C.
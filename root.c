/*@
    requires (i * j + 2 * j + 3 * i == 0);
    ensures \result == 6;
*/
int verify_assignment(int i, int j) {
    j += 3;
    i += 2;

    return i * j;
}
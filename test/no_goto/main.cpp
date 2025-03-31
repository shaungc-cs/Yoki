void f() {
L1:
  int a = 0;

  if (a == 0) {
    goto L1;
  }
}

int main(int argc, const char **argv) {
  f();
  return 0;
}

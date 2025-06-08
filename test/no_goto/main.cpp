void f1() {
L1:
  int a = 0;

  if (a == 0) {
    goto L1;
  }
}

void f2() {
L2:
  int a = 0;

  if (a == 0) {
    goto L2;
  }
}

int main(int argc, const char **argv) {
  f1();
  f2();
  return 0;
}

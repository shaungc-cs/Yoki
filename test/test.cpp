void f1() {}

void test() {}

class A {
public:
  void memF() {}
  int menf2() { return 2; }
};

int main(int argc, const char **argv) {
  A a;
  a.memF();
  a.menf2();
  return 0;
}

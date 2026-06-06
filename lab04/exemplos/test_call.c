int foo(int x, int y) {
  int a;
  int b;
  int c;
  a = 1;
  b = 2;
  c = 3;
  a = bar(a, b + c);
  return a + b;
}

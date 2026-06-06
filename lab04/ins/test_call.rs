fn foo(x: i32, y: i32) -> i32 {
    let mut a: i32;
    let mut b: i32;
    let mut c: i32;
  a = 1;
  b = 2;
  c = 3;
  a = bar(a, b + c);
  return a + b;
}
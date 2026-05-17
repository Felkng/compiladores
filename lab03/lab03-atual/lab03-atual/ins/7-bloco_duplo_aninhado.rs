fn calcular() -> i32 {
    let mut a: i32;
  a = 5;
  {
    let mut b: i32;
    b = a * 3;
    {
    let mut c: i32;
      c = b + 1;
      return c;
    }
  }
}
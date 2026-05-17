fn triplo_aninhado() -> i32 {
    let mut a: i32;
  a = 1;
  {
    let mut b: i32;
    b = a + 2;
    {
    let mut c: i32;
      c = b * 3;
      {
    let mut d: i32;
        d = c - 1;
        return d;
      }
    }
  }
}
fn principal() -> i32 {
    let mut x: i32;
  x = 1;
  {
    let mut y: i32;
    y = x + 2;
    return y;
  }
}
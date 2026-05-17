fn sombraParametro(x: i32) -> i32 {
    let mut acum: i32;
  acum = x * 2;
  {
    let mut x: i32;
    x = acum + 9;
    let mut resultado: i32;
    resultado = x * x;
    return resultado;
  }
}
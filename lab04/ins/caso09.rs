fn formula(base: i32) -> i32 {
    let mut res: i32;
    res = !estaVazio( ) + (calcular(base) * obterMultiplicador(ajustar(base)));
}
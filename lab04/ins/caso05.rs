fn loop() -> i32 {
    let mut contador: i32;
    while ( continuarExecucao(contador) ) {
        contador = contador + 1;
    }
}
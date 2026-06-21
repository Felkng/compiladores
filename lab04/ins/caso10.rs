fn processarMatriz() -> i32 {
    let mut celula: i32;
    while ( possuiLinha( ) ) {
        while ( possuiColuna( ) ) {
            celula = processarCelula(obterX( ), obterY(maximo( )));
        }
    }
}
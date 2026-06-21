fn buscar() -> i32 {
    let mut sinalizador: i32;
    while ( lerProximo( ) ) {
        if ( extrairValor( ) == 0 ) {
            return obterPadrao( );
        }
    }
}
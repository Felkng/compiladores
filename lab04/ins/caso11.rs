fn validarFluxo(status: i32) -> bool {
    let mut estadoAtual: i32;
    estadoAtual = status;
    while ( verificarStatus(estadoAtual) ) {
        if ( !validarToken(gerarToken( )) ) {
            estadoAtual = atualizar(estadoAtual, falha( ));
        } else {
            return proximaEtapa( );
        }
    }
}
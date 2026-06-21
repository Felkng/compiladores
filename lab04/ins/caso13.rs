fn simular(passos: i32) -> f32 {
    let mut contadorPassos: i32;
    contadorPassos = passos;
    while ( contadorPassos > obterMinimo( ) ) {
        if ( checarCondicao(contadorPassos + calcularDelta( )) ) {
            contadorPassos = contadorPassos - extrairPasso( );
        } else {
            contadorPassos = contadorPassos / aplicarFator(obterDivisor(contadorPassos), retornarInercia( ));
        }
    }
    return obterResultadoFinal( );
}
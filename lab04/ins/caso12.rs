fn checarSensor(leitura: f32) -> i32 {
    let mut copiaLeitura: f32;
    copiaLeitura = leitura;
    if ( calibrar(copiaLeitura) == obterAlvo( ) ) {
        if ( dispararAlarme( ) ) {
            return 1;
        }
    }
    if ( !estaPronto( ) < limiteCritico( ) ) {
        copiaLeitura = lerSegundaOpcao(copiaLeitura * ajustar( ));
    }
    return verificarSistema( );
}
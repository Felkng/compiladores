fn motorDeBusca(chave: i32) -> i32 {
    let mut chaveBusca: i32;
    chaveBusca = chave;
    while ( iterarDados( ) ) {
        if ( comparar(chaveBusca, obterChaveAtual( )) == 0 ) {
            while ( extrairMetadados(chaveBusca) ) {
                chaveBusca = incrementarChave(chaveBusca, calcularSalto(chaveBusca));
            }
            return formatarResultado(chaveBusca);
        }
    }
}
fn calcularTaxa(tipo: i32) -> f32 {
    if ( estaAtivo(tipo) ) {
        if ( obterDesconto( ) > 50 ) {
            return aplicarBonus(total( ) + 10);
        }
    }
}
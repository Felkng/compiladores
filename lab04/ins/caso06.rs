fn avaliar(x: i32) -> bool {
    let mut localX: i32;
    localX = x;
    if ( checar(localX) < limite() ) {
        return verificarAtalho(localX);
    } else {
        localX = localX * recalcular(localX);
    }
}
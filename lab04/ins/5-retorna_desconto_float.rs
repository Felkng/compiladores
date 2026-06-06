fn descontar(preco: f32, taxa: f32) -> f32 {
    let mut final: f32;
  final = preco * (1.0 - taxa);
  return final;
}
fn F24(from: i32, to: i32, step: i32) {
    let mut i: i32;
    let mut product: i32 = 1;
    i = from;
    while (i < to) {
        product = product * i;
        i = i + step;
    }
}
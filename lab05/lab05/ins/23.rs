fn F23(start: i32, limit: i32, step: i32) {
    let mut i: i32 = start;
    let mut total: i32 = 0;
    while (i < limit) {
        total = total + i;
        i = i + step;
    }
}
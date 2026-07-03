fn F25(val: i32, times: i32, factor: i32) {
    let mut i: i32 = 0;
    let mut result: i32 = val;
        result = result * factor;
        i = i + 1;
    while (i < times) {
        result = result * factor;
        i = i + 1;
    }
}
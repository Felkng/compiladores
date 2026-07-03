fn power(base: i32, exp: i32) -> i32 {
    if (exp == 0) return 1;
    return base * power(base, exp - 1);
}
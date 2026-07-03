fn F12() {
    let mut x: i32 = 5;
    {
    let mut x: i32 = 10;
        x = x + 1;
    }
}
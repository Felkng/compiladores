fn F50(n: i32, a: i32, b: i32) -> i32 {
    let mut sum: i32 = 0;
    let mut temp: i32 = (a * b) - (a + b) / 2;
    if ((n % 2 == 0) && (a + b > 0)) {          
        sum = (n * n) + (a * 2) - (b / 2);
    }
    if ((a * a + b * b) % 3 == 0) {             
        sum = sum + (a + b) * (a - b);
    } else {
        sum = sum - ((a + b) * (a + b)) / (n + 1);
    }
    while (n > 1) {                             
        sum = sum + (n * temp) - (n % 3) + (a + b);
        n = n - ((n % 2) + 1);
    }
    n = 0;
    while (n < 4) {
        sum = sum + (n * n) - (a - b) * (n + 1);
        n = n + 1;
    }
    if (sum > 100) {
    let mut r: i32 = ((sum / 3) - F50(n + 1, a - 1, b + 2)) * 2 + (a % 3);
        sum = sum + r;
    }
    return sum + ((a * b) % (n + 2)) - temp;
}
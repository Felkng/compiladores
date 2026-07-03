fn F28(n: i32, a: i32, b: i32) -> i32 {
    let mut sum: i32 = 0;
    if (n <= 0) {                   
        return 0;
    }
    if (a > b) {                    
        sum = a - b;
    } else {
        sum = b - a;
    }
    while (n > 0) {                 
        sum = sum + n;
        n = n - 1;
    }
    n = 0;
    while (n < 3) {
        sum = sum + n;
        n = n + 1;
    }
    if (sum > 10) {                 
        return F50(sum / 3, a, b);  
    }
    return sum;
}
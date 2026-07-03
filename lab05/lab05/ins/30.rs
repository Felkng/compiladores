fn F50(n: i32, a: i32, b: i32) -> i32 {
    let mut sum: i32 = 0;
    let mut temp: i32 = (a * b) - (a + b) / 2;
    if ((n % 2 == 0) && (a + b > 0)) {        
    let mut x: i32 = (n * n) + (a * 2);
        {
    let mut y: i32 = x - (b / 2);
            sum = y + helper(a, b, n);          
        }
    }
    if ((a * a + b * b) % 3 == 0) {            
    let mut y: i32 = (a + b) * (a - b);
        {
            sum = sum + y;                      
        }
    } else {
    let mut d: i32 = ((a + b) * (a + b)) / (n + 1);
        {
            sum = sum - d;                      
        }
    }
    while (n > 1) {                            
    let mut step: i32 = ((n % 3) + 1);
        {
            sum = sum + (n * temp) - step + (a + b); 
            n = n - ((n % 2) + 1);
        }
    }
    n = 0;
    while (n < 4) {
    let mut v: i32 = (n * n) - (a - b) * (n + 1);
        {
            sum = sum + v;                      
        }
        n = n + 1;
    }
    if (sum > 100) {                           
        {
    let mut r: i32 = ((sum / 3) - F50(n + 1, a - 1, b + 2)) * 2 + (a % 3);
            sum = sum + r;
        }
    }
    let mut tail: i32 = ((a * b) % (n + 2)) - temp;
    sum = sum + tail;
    return sum;
}
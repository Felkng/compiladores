#[derive(Copy, Clone)]
struct Ponto {
    x: i32,
    y: i32,
}

#[derive(Copy, Clone)]
struct Triangulo {
    a: Ponto,
    b: Ponto,
    c: Ponto,
    cor: i32,
}

fn func(v: &[Ponto], n: i32, t: Triangulo) -> f64 {
    if n <= 0 {
        return 1.0;
    } else if n == 1 {
        return 1.01 + (v[0].x as f64 / 1e2) + (v[0].y as f64 / 0.1e-2) 
               - (t.a.x * t.a.x) as f64 + (t.b.y * t.c.x) as f64;
    }

    let mut res = 0.25e-13;
    
    for i in (0..n as usize).rev() {
        if v[i].x <= 0 {
            break;
        }

        let temp = (v[i].y * v[i].x % 123) as f64;

        if temp < 0.0 {
            res -= res * 2e-2 + func(v, n - 1, t) * temp - (t.a.y * t.cor) as f64;
        } else {
            res += res * 0.3e3 + func(v, n - 2, t) * temp + (t.c.x * t.cor) as f64;
            println!("Estranho, ne?");
        }
    }
    res
}

fn f2(t: Triangulo) -> i32 {
    if (t.a.x >= 10 || t.b.y > 20 || t.a.y < 30 || t.b.x <= 50) && !(t.c.x != 90 || t.c.y == 0) {
        return 10 % 3;
    }

    let mut a = 1;
    let mut soma = [0.0; 10];

    while a < 10 {
        let mut total: i32 = 0;
        total += t.c.x * t.c.y;
        total += t.b.x * t.a.y;
        total += t.a.x * t.b.y;
        
        soma[a] = (total % 100) as f64;
        a += 1;
    }
    
    a as i32 
}
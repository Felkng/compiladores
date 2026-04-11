struct ponto_t {
    x: i32,
    y: i32
}

struct triangulo_t {
    a: ponto_t,
    b: ponto_t,
    c: ponto_t,
    cor: i32
}

fn func(v: &[ponto_t], n: i32, T: triangulo_t) -> f64 {
    if (n <= 0) {
        return 1.0;
    } else {
        if (n == 1) {
            return 1.01 + v[0].x as f64 / 1.0e2 + v[0].y as f64 / 0.1e-2 - (T.a.x * T.a.x) as f64 + (T.b.y * T.c.x) as f64;
        }
    }
    let mut res: f64 = 0.25e-13;
    let mut i: i32 = n - 1;
    while (i >= 0 && v[i].x > 0) {
        let temp: f64 = (v[i].y * v[i].x % 123) as f64;
        if (temp < 0.0) {
            res = res - (res * 2.0e-2 + func(v, n - 1, T) * temp - (T.a.y * T.cor) as f64);
        } else {
            res = res + (res * 0.3e3 + func(v, n - 2, T) * temp + (T.c.x * T.cor) as f64);
            printf("Estranho, ne?\n");
        }
        i = i - 1;
    }
    return res;
}

fn F2(T: triangulo_t) -> i32 {
    let mut A: i32 = 0;
    let mut soma: [f64];
    if ((T.a.x >= 10 || T.b.y > 20 || T.a.y < 30 || T.b.x <= 50) && !(T.c.x != 90 || T.c.y == 0)) {
        return 10 % 3;
    } else {
        A = 1;
    }
    while (A < 10) {
        let mut total: i32 = 0;
        total = total + T.c.x * T.c.y;
        total = total + T.b.x * T.a.y;
        total = total + T.a.x * T.b.y;
        soma[A] = (total % 100) as f64;
        A = A + 1;
    }
    return A;
}

fn fatorialA(n: i32) -> i32 {
    if (n <= 1) { return 1; }
    return n * fatorialA(n - 1);
}

fn fatorialB(n: i32) -> i32 {
    let a: i32 = n - 1;
    if (n <= 1) { return 1; }
    return n * fatorialB(a);
}

fn fatorialC(n: i32, P: i32) -> i32 {
    if (n <= 1) { return 1; }
    return fatorialC(n - 1, P * n);
}

fn fatorialD(n: i32, P: i32) -> i32 {
    let a: i32 = n - 1;
    let b: i32 = P * n;
    if (n <= 1) { return 1; }
    return fatorialD(a, b);
}

fn fatorialE(n: i32, P: i32) -> i32 {
    if (n <= 1) {
        return 1;
    } else {
        let a: i32 = n - 1;
        let b: i32 = P * n;
        return fatorialD(a, b);
    }
}

fn C1(a: i32, b: i32) -> i32 {
    if (a < b) { return 1; }
    return 2;
}

fn C2(a: i32, b: i32) -> i32 {
    if (a <= b) { return 1; }
    return 2;
}

fn C3(a: i32, b: i32) -> i32 {
    if (a > b) { return 1; }
    return 2;
}

fn C4(a: i32, b: i32) -> i32 {
    if (a >= b) { return 1; }
    return 2;
}

fn C5(a: i32, b: i32) -> i32 {
    if (a == b) { return 1; }
    return 2;
}

fn C5_v2(a: i32, b: i32) -> i32 {
    if (a != b) { return 1; }
    return 2;
}

fn D1(a: i32, b: i32) -> i32 {
    if (a != b && a < b) { return 1; }
    return 2;
}

fn D2(a: i32, b: i32) -> i32 {
    if (!(a != b && a < b)) { return 1; }
    return 2;
}

fn D3(a: i32, b: i32) -> i32 {
    if ((!(a != b && a < b)) || (a + 2 == b)) { return 1; }
    return 2;
}

fn E1(a: i32, b: i32) -> i32 {
    let X: bool = ((!(a != b && a < b)) || (a + 2 == b));
    if (a != b || X || a + 5 == b) {
        a = a + 1;
    }
    return 2;
}

fn E2(a: i32, b: i32) -> i32 {
    let X: bool = ((!(a != b && a < b)) || (a + 2 == b));
    while (a != b || X || a + 5 == b) {
        a = a + 1;
        while (a < b) {
            b = b - 1;
        }
    }
    return 2;
}

fn E2_v2(a: i32, b: i32) -> bool {
    let X: bool = ((!(a != b && a < b)) || (a + 2 == b));
    while (a != b || X || a + 5 == b) {
        a = a + 1;
        while (fatorialA(a) < b) {
            b = b - 1;
        }
    }
    return X || a > 0;
}

struct ponto_2d_t {
    x: i32,
    y: i32
}

struct ponto_3d_t {
    x: i32,
    y: i32,
    z: i32
}

struct segmento_2d_t {
    ini: ponto_2d_t,
    fim: ponto_2d_t
}

struct segmento_3d_t {
    ini: ponto_3d_t,
    fim: ponto_3d_t
}

fn F1(seg: segmento_2d_t, p: ponto_2d_t) -> f64 {
    let ax: f64 = seg.ini.x as f64;
    let ay: f64 = seg.ini.y as f64;
    let bx: f64 = seg.fim.x as f64;
    let by: f64 = seg.fim.y as f64;
    let px: f64 = p.x as f64;
    let py: f64 = p.y as f64;
    let abx: f64 = bx - ax;
    let aby: f64 = by - ay;
    let apx: f64 = px - ax;
    let apy: f64 = py - ay;
    let ab2: f64 = abx * abx + aby * aby;
    let t: f64 = (apx * abx + apy * aby) / ab2;
    if (t < 0.0) { t = 0.0; }
    if (t > 1.0) { t = 1.0; }
    let qx: f64 = ax + t * abx;
    let qy: f64 = ay + t * aby;
    let dx: f64 = px - qx;
    let dy: f64 = py - qy;
    return sqrt(dx * dx + dy * dy);
}

fn dist2(a: ponto_2d_t, b: ponto_2d_t) -> i64 {
    let dx: i64 = a.x as i64 - b.x as i64;
    let dy: i64 = a.y as i64 - b.y as i64;
    return dx * dx + dy * dy;
}

fn F2_v2(seg: segmento_2d_t, p: ponto_2d_t) -> i64 {
    let ax: i64 = seg.ini.x as i64;
    let ay: i64 = seg.ini.y as i64;
    let bx: i64 = seg.fim.x as i64;
    let by: i64 = seg.fim.y as i64;
    let px: i64 = p.x as i64;
    let py: i64 = p.y as i64;
    let abx: i64 = bx - ax;
    let aby: i64 = by - ay;
    let apx: i64 = px - ax;
    let apy: i64 = py - ay;
    let bpx: i64 = px - bx;
    let bpy: i64 = py - by;
    let dot1: i64 = apx * abx + apy * aby;
    let dot2: i64 = bpx * abx + bpy * aby;
    if (dot1 <= 0) {
        return dist2(p, seg.ini);
    }
    if (dot2 >= 0) {
        return dist2(p, seg.fim);
    }
    let cross: i64 = abx * apy - aby * apx;
    return (cross * cross) / (abx * abx + aby * aby);
}

fn area_poligono(p: &[ponto_2d_t], n: i32) -> f64 {
    let mut soma: i64 = 0;
    let mut i: i32 = 0;
    while (i < n) {
        let j: i32 = (i + 1) % n;
        soma = soma + (p[i].x as i64 * p[j].y as i64 - (p[j].x as i64 * p[i].y as i64));
        i = i + 1;
    }
    if (soma < 0) {
        soma = 0 - soma;
    }
    return soma as f64 / 2.0;
}

fn area_pol() -> f64 {
    let mut poli: [ponto_2d_t];
    return area_poligono(poli, 150);
}

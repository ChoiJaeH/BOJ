using cpx = complex<double>;
using vec = vector<cpx>;
const double PI = acos(-1);

void FFT(vec& f, bool inv) {
    int n = f.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit)) bit >>= 1;
        if (i < j) swap(f[i], f[j]);
    }
    for (int i = 1; i < n; i <<= 1) {
        double x = inv ? PI / i : -PI / i;
        cpx w = cpx(cos(x), sin(x));
        for (int j = 0; j < n; j += i << 1) {
            cpx p = cpx(1, 0);
            for (int k = 0; k < i; k++) {
                cpx tmp = f[i + j + k] * p;
                f[i + j + k] = f[j + k] - tmp;
                f[j + k] += tmp;
                p *= w;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++) {
            f[i] /= n;
        }
    }
}

vec mul(vec& f, vec& g) {
    vec pf(f.begin(), f.end()), pg(g.begin(), g.end());
    int n = 1;
    while (n < max(pf.size(), pg.size())) n <<= 1;
    n <<= 1;
    pf.resize(n), pg.resize(n);
    FFT(pf, 0); FFT(pg, 0);
    vec h(n);
    for (int i = 0; i < n; i++) h[i] = pf[i] * pg[i];
    FFT(h, 1);
    for (int i = 0; i < n; i++) {
        h[i] = cpx(round(h[i].real()), 0);
    }
    return h;
}
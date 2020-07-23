using ull = unsigned long long;
 
vector<ull> alist = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
 
// calculate (x + y) % m; overflow-safe
inline ull addmod(ull x, ull y, ull m) {
    x %= m;
    y %= m;
    return (x >= m - y? x - (m - y) : x + y);
}
 
// calculate (x * y) % m; overlow-safe
inline ull mulmod(ull x, ull y, ull m) {
    x %= m;
    y %= m;
    ull r = 0;
    while (y > 0) {
        if (y % 2 == 1)
            r = addmod(r, x, m);
        x = addmod(x, x, m);
        y /= 2;
    }
    return r;
}
 
// calculate x^y % m; overflow-safe
ull powmod(ull x, ull y, ull m) {
    x %= m;
    ull r = 1ULL;
    while (y > 0) {
        if (y % 2 == 1)
            r = mulmod(r, x, m);
        x = mulmod(x, x, m);
        y /= 2;
    }
    return r;
}
 
// true for probable prime, false for composite
inline bool miller_rabin(ull n, ull a) {
    ull d = n - 1;
    while (d % 2 == 0) {
        if (powmod(a, d, n) == n-1)
            return true;
        d /= 2;
    }
    ull tmp = powmod(a, d, n);
    return tmp == n-1 || tmp == 1;
}
 
bool is_prime(ull n) {
    if (n <= 1)
        return false;
    if (n <= 10000000000ULL) {
        for (ull i = 2; i*i <= n; i++)
            if (n % i == 0)
                return false;
        return true;
    }
    for (ull a : alist)
        if (!miller_rabin(n, a))
            return false;
    return true;
}

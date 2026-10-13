#include <bits/stdc++.h>
// По модулю
using namespace std;

#define int long long
#define all(x) x.begin(), x.end()

template<typename T>
ostream& operator << (ostream& out, const vector<T>& a){
    for (const auto& e : a){
        out << e << ' ';
    }
    return out;
}

const int mod = 998244353;

int fpow(int a, int p){
    if (p == 0){
        return 1;
    }
    if (p & 1){
        return fpow(a, p - 1) * a % mod;
    }
    return fpow(a*a % mod, p >> 1);
}

vector<int> roots;

vector<int> operator * (vector<int> a, vector<int> b){

    int sz = 1;
    while ((1 << sz) < (int)a.size() + (int)b.size()){
        sz++;
    }

    int SZ = 1 << sz;

    vector<int> rev(SZ);
    for (int i = 0; i < SZ; i++){
        int j = 0;
        for (int b = 0; b < sz; b++){
            j <<= 1;
            j |= (i >> b) & 1;
        }
        rev[i] = j;
    }

    auto fft = [&](vector<int>& a, int br){
        for (int i = 0; i < SZ; i++){
            if (rev[i] < i){
                swap(a[rev[i]], a[i]);
            }
        }

        for (int j = 1; j <= sz; j++){
            int root = fpow(br, 1 << (sz - j));
            int sj = 1 << j;
            int ssj = sj >> 1;
            int x = 1;
            for (int k = 0; k < ssj; k++){
                for (int i = 0; i < SZ; i += sj){
                    int z0 = a[i + k];
                    int z1 = x * a[i + k + ssj] % mod;
                    a[i + k] = z0 + z1;
                    if (a[i + k] > mod){
                        a[i + k] -= mod;
                    }
                    a[i + k + ssj] = z0 - z1;
                    if (a[i + k + ssj] < 0){
                        a[i + k + ssj] += mod;
                    }
                }
                x = x * root % mod;
            }
        }
    };

    a.resize(SZ);
    b.resize(SZ);

    fft(a, roots[sz]);
    fft(b, roots[sz]);

    vector<int> c(SZ);
    for (int i = 0; i < SZ; i++){
        c[i] = a[i] * b[i] % mod;
    }

    fft(c, fpow(roots[sz], mod - 2));
    int rn = fpow(SZ, mod - 2);
    for (auto& e : c){
        e = (e * rn) % mod;
    }

    while (c.size() > 1 && c.back() == 0){
        c.pop_back();
    }
    return c;
}

vector<int> inverse(const vector<int>& p, vector<int> q, int sz){
    if (sz >= (int)p.size()){
        return q;
    }

    vector<int> p_;
    for (int i = 0; i < 2*sz && i < (int)p.size(); i++){
        p_.push_back(p[i]);
    }

    p_ = p_ * q;
    p_.resize(2*sz);
    for (auto& e : p_){
        e = mod - e;
    }
    p_[0] = (p_[0] + 1) % mod;

    p_ = p_ * q;
    p_.resize(2*sz);
    for (int i = 0; i < (int)q.size(); i++){
        p_[i] = q[i];
    }

    return inverse(p, p_, sz << 1);
}

void init_roots(){
    int mx_sz = 21;
    int j = 1;
    for (; j < mod; j++){
        if (fpow(j, 1 << (mx_sz - 1)) == (mod - 1)){
            break;
        }
    }
    if (j == mod){
        cout << "very big size palinom. not found root!";
        exit(0);
    }

    for (int i = mx_sz; i >= 0; i--) {
        roots.push_back(j);
        j = j * j % mod;
    }

    reverse(all(roots));
}

signed main(){

    freopen("output.txt", "w", stdout);

    init_roots();
    vector<int> a = {1, 1, 1};
    cout << a * a << endl;
    cout << a * inverse(a, {fpow(a[0], mod - 2)}, 1) << endl;

}




// В комплексных

vector<int> operator * (const vector<int>& a, const vector<int>& b){
    int SZ = 1;
    while (SZ < (int)a.size() + (int)b.size() - 1){
        SZ <<= 1;
    }
    vector<int> rv(SZ);
    for (int i = 1, j = 0; i < SZ; i++){
        int b = SZ >> 1;
        for (; b <= j; b >>= 1){
            j -= b;
        }
        rv[i] = j += b;
    }
    double ang = 2 * acosl(-1) / SZ;
    base root(cos(ang), sin(ang));
 
    auto fft = [&](vector<base>& a, base br){
        for (int i = 0; i < SZ; i++){
            if (rv[i] < i){
                swap(a[i], a[rv[i]]);
            }
        }
 
        for (int j = 2; j <= SZ; j <<= 1){
            base root = br;
            for (int i = j; i < SZ; i <<= 1){
                root *= root;
            }
            int lj = j >> 1;
            vector<base> rt(lj);
            rt[0] = 1;
            for (int i = 1; i < lj; i++){
                rt[i] = rt[i - 1] * root;
            }
 
            for (int i = 0; i < SZ; i += j){
                base z;
                auto il = a.begin() + i;
                auto ir = il + lj;
                auto en = ir;
                auto it = rt.begin();
                for (; il != en; il++, ir++, it++){
                    z = *ir * *it;
                    *ir = *il - z;
                    *il += z;
                }
            }
        }
    };
 
    vector<base> A(SZ);
    for (int i = 0; i < a.size(); i++){
        A[i] = a[i];
    }
    fft(A, root);
 
    vector<base> B(SZ);
    for (int i = 0; i < b.size(); i++){
        B[i] = b[i];
    }
    fft(B, root);
 
    for (int i = 0; i < SZ; i++){
        A[i] *= B[i];
    }
    fft(A, base(1) / root);
 
    vector<int> c(a.size() + b.size() - 1);
    for (int i = 0; i < c.size(); i++){
        c[i] = (int)round(A[i].real() / SZ) % mod;
    }
 
    return c;
}
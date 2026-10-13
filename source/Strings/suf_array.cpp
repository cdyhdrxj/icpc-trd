const int ALPHA = 'z' + 1;
 
struct SufArray {
    int n;
    vi p, c, lcp;
 
    SufArray(string &s) {
        n = (int)s.size();
 
        p = vi(n);
        c = vi(n);
        vi cnt(ALPHA, 0);
 
        for (auto x : s)
            cnt[x]++;
        for (int i = 1; i < ALPHA; i++)
            cnt[i] += cnt[i-1];
        for (int i = 0; i < n; i++)
            p[--cnt[s[i]]] = i;
 
        int classes = 1;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i-1]])
                classes++;
            c[p[i]] = classes - 1;
        }
 
        vi pn(n), cn(n);
        for (int h = 0; (1 << h) < n; h++) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
 
            cnt = vi(classes, 0);
            for (int i = 0; i < n; i++)
                cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i-1];
            for (int i = n-1; i >= 0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];
 
            classes = 1;
            cn[pn[0]] = 0;
            for (int i = 1; i < n; i++) {
                int m1 = (p[i] + (1 << h)) % n;
                int m2 = (p[i-1] + (1 << h)) % n;
 
                if (c[p[i]] != c[p[i-1]] || c[m1] != c[m2])
                    classes++;
                
                cn[p[i]] = classes - 1;
            }
            c = cn;
        }
    }
 
    void build_lcp(string &s) {
        lcp = vi(n);
        int k = 0;
        for (int i = 0; i < n - 1; i++) {
            int pi = c[i];
            int j = p[pi - 1];
            while (s[i + k] == s[j + k])
                k++;
            
            lcp[pi] = k;
            k = max(k - 1, 0ll);
        }
    }
};
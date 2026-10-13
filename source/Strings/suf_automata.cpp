const int ALPHA = 26;
 
struct state {
    int len, link;
    int next[ALPHA];
    state() {
        fill(next, next + ALPHA, -1);
    }
};
 
const int MAXLEN = 1e6;
state st[MAXLEN << 1];
int sz, last;

void sa_init() {
    sz = last = 0;
    st[0].len = 0;
    st[0].link = -1;
    sz++;
}
 
void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p;
    for (p = last; p != -1 && st[p].next[c - 'a'] == -1; p = st[p].link)
        st[p].next[c - 'a'] = cur;
    if (p == -1)
        st[cur].link = 0;
    else {
        int q = st[p].next[c - 'a'];
        if (st[p].len + 1 == st[q].len)
            st[cur].link = q;
        else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            for (int i = 0; i < ALPHA; i++)
                st[clone].next[i] = st[q].next[i];
            st[clone].link = st[q].link;
            for (; p != -1 && st[p].next[c - 'a'] == q; p = st[p].link)
                st[p].next[c - 'a'] = clone;
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}
 
void build(string &s) {
    sa_init();
    for (auto c : s)
        sa_extend(c);
}
 
bool find(string &s) {
    int cur = 0;
    for (auto c : s) {
        if (st[cur].next[c - 'a'] == -1)
            return false;
        
        cur = st[cur].next[c - 'a'];
    }
 
    return true;
}
using pii = pair<int,int>;
using vi = vector<int>;
using vpi = vector<pii>;
using vvpi = vector<vpi>;

bool comp(int i, int j) {
    return vh[i] < vh[j]; // порядок DFS / Эйлера
}
vvpi gr1;       // виртуальное дерево: {сосед, длина ребра}
vi used;        // used[i] = 1, если вершина была выбрана в запросе
int ans = 0;    // ответ, если считаем сумму попарных расстояний
int al = 0;     // количество выбранных вершин
// Опционально: подсчёт ответа на виртуальном дереве
int dfs1(int v, int p = -1) {
    int cnt = 0;
    for (auto [to, w] : gr1[v]) {
        if (to == p) continue;
        int sub = dfs1(to, v);
        ans += sub * (al - sub) * w;
        cnt += sub;
    }
    if (used[v]) cnt++;
    return cnt;
}

void build_virtual_tree(vi a) {
    ans = 0;
    int n = (int)a.size();
    gr1.clear();
    sort(a.begin(), a.end(), comp);
    // Добавляем LCA соседних вершин в порядке DFS
    vi vip = a;
    for (int i = 0; i + 1 < n; i++) {
        vip.pb(get_lca(a[i], a[i + 1]));
    }
    int mx = *max_element(vip.begin(), vip.end());
    al = n;
    vi b = a; // исходные выбранные вершины
    // Оставляем только выбранные вершины + их LCA
    sort(vip.begin(), vip.end());
    vip.erase(unique(vip.begin(), vip.end()), vip.end());
    sort(vip.begin(), vip.end(), comp);
    vi inds(mx + 10, 0);
    used.assign((int)vip.size(), 0);
    for (int i = 0; i < (int)vip.size(); i++) {
        inds[vip[i]] = i;
    }
    for (int x : b) {
        used[inds[x]] = 1;
    }
    // Построение виртуального дерева стеком
    stack<int> st;
    st.push(vip[0]);
    gr1.resize((int)vip.size());
    for (int i = 1; i < (int)vip.size(); i++) {
        int x = vip[i];
        while (!is_anc(st.top(), x)) st.pop();
        int u = inds[st.top()];
        int v = inds[x];
        int w = abs(h[st.top()] - h[x]); // расстояние в исходном дереве
        gr1[u].pb({v, w});
        gr1[v].pb({u, w});
        st.push(x);
    }
    // Корень виртуального дерева — индекс 0
    // Если нужен только каркас дерева, dfs1(0) можно не вызывать.
    dfs1(0);
}

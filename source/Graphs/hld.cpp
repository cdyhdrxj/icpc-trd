void dfs(int v){
    used[v] = 1;
    int mx = 0;
    sm[v] = 0;
    for(auto to:gr[v]){
        if(used[to])continue;
        p[to] = v;
        h[to] = h[v] + 1;
        dfs(to);
        sm[v] += sm[to];
        mx= max(mx,sm[to]);
    }
    for(auto to:gr[v]){
        if(to == p[v])continue;
        if(sm[to] == mx){
            mx = sm[to];
            heavy[v] = to; //находим тяжелое ребро
        }
    }
    sm[v]++; //кол-во детей в поддереве вершины включая её
} 
void dfs_do(int v, int tp = 0){//построение массива с проходом по тяжелым ребрам
    a.pb(v);
    ind[v] = (int)a.size()-1;//индекс вершины в массиве для до
    top[v] = tp;//верхняя вершина в тяжелом пути
    if(heavy[v] != -1)dfs_do(heavy[v],tp);
    for(auto to:gr[v]){
        if(to == p[v])continue;
        if(to == heavy[v])continue;
        dfs_do(to,to);
    }
}
 
int get_ans(int u, int v){
    int ans = 0;//ответ собираем пока ищем lca
    while(1){
        int _u = top[u];
        int _v = top[v];
        if(_u == _v){
            ans += t.get_sum(ind[u], ind[v]);//запрос в до на отрезке
            return ans;
        }
        if(h[_v] < h[_u]){
            ans += t.get_sum(ind[u], ind[_u]);//запрос в до на отрезке
            u = p[_u];
        }
        else{
            ans += t.get_sum(ind[v], ind[_v]);//запрос в до на отрезке
            v = p[_v];
        }
    }
}

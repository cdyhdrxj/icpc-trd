//map можно заменить на массив или вектор
struct node{
    map<int,int> edge;
    bool is_term;
    int link; //суф ссылка
    char to_p;
    int p;
    int nxt;
    map<int,int> goo[4]; // переход из вершины по символу
    node(){
        link = -1;
        p = -1;
        nxt = -1;
        is_term = false;
    }
};
 
struct bor{
    vector<node>t;
    int sz;
    void assign(){
        t.resize(1);
        sz= 1;
    }
    void add_word(string &s, int ind){
        int v = 0;
        for(auto it:s){
            int c = it;
            if(t[v].edge[c] == -1){
                t[v].edge[c] = sz;sz++;
                t.emplace_back(node());
            }
            int _v = t[v].edge[c];
            t[_v].p = v;
            t[_v].to_p = it;
            v = _v;
        }
        t[v].is_term = true;
    }
    int go(int v, int c);
    int get_link(int v){
        if(t[v].link != -1)return t[v].link;
        if(v == 0 || t[v].p == 0){
            t[v].link = 0;
        }
        else{
            t[v].link = go(get_link(t[v].p),t[v].to_p);
        }
        return t[v].link;
    }
    int nxt(int v){
        if(t[v].nxt != -1)return t[v].nxt;
        if(v == 0)return 0;
        if(t[get_link(v)].is_term){
            t[v].nxt = t[v].link;
        }
        else{
            t[v].nxt = nxt(get_link(v));
        }
        return t[v].nxt;
    }
    void go_through_term(int v, int ind){ // проход по всем терминальным от тек вершины
        for(int u = v; u != 0; u = nxt(u)){
            if(t[u].is_term)
                //doing something
        }
    }
    void do_text(string &s){
        int v =0;
        int ind = 0;
        for(auto it:s){
            v = go(v,it);
            //go_through_term(v,ind); если надо пройти по всем терминальным от тек вершины, если надо
            ind++;
        }
    }
};
 
int bor::go(int v, int c){
    int cc = c;
    if(t[v].goo[cc] != -1)return t[v].goo[cc];
    if(t[v].edge[cc] != -1){
        t[v].goo[cc] = t[v].edge[cc];
    }
    else{
        if(v == 0)
            t[v].goo[cc] = 0;
        else
            t[v].goo[cc] = go(get_link(v),c);
    }
    return t[v].goo[cc];
}

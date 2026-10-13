mt19937_64 rnd(42);

struct Node {
    int x;

    int cnt = 1;
    int val = 0;
    int psh = 0;
    Node *l = NULL;
    Node *r = NULL;

    Node (int X) : x(X) {} 

    int i(){
        return (l ? l->cnt : 0) + 1;
    }

    void push(){
        if (l){
            l->psh += psh;
            l->val += psh;
        }
        if (r){
            r->psh += psh;
            r->val += psh;
        }
        psh = 0;
    }

    void recalc(){
        cnt = (l ? l->cnt : 0) + (r ? r->cnt : 0) + 1;
    }

    void add_l(Node *v){
        push();
        l = v;
        recalc();
    }
    void add_r(Node *v){
        push();
        r = v;
        recalc();
    }
};

Node *merge(Node *l, Node *r){
    if (!l){
        return r;
    }
    if (!r){
        return l;
    }

    l->push();
    r->push();
    if (rnd() % (l->cnt + r->cnt) < l->cnt){
        l->add_r(merge(l->r, r));
        return l;
    }else{
        r->add_l(merge(l, r->l));
        return r;
    }
}

pair<Node *, Node *> split(Node *cur, int k){
    if (!cur){
        return {NULL, NULL};
    }

    cur->push();
    if (cur->x > k){
        auto spl = split(cur->l, k);
        cur->add_l(spl.second);
        return {spl.first, cur};
    }else{
        auto spl = split(cur->r, k);
        cur->add_r(spl.first);
        return {cur, spl.second};
    }
}

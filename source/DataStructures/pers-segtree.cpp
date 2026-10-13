const int SZ = 1 << 18;

struct Node{
    Node *l = NULL, *r = NULL;
    int sum = 0;
};

void build(Node* cur, int lx = 0, int rx = SZ){
    if(rx - lx == 1){
        // TODO
        cur->sum = 0;
        return;
    }

    int m = (lx + rx) >> 1;
    cur->l = new Node; build(cur->l, lx, m);
    cur->r = new Node; build(cur->r, m, rx);
}

Node* upd(int i, Node* cur, int lx = 0, int rx = SZ){
    cur = new Node(*cur);

    if(rx - lx == 1){
        cur->sum++;
        return cur;
    }

    int m = (lx + rx) >> 1;
    if(i < m) cur->l = upd(i, cur->l, lx, m);
    else cur->r = upd(i, cur->r, m, rx);

    cur->sum = cur->l->sum + cur->r->sum;
    return cur;
}

vector<Node*> roots;
void add(int i){
    Node* root = new Node(*roots.back());
    roots.push_back(upd(i, root));
}

int kth(Node* l, Node* r, int k, int lx = 0, int rx = SZ){
    if(rx - lx == 1)
        return lx;

    int m = (lx + rx) >> 1;
    int s = r->l->sum - l->l->sum;
    
    if(s >= k)
        return kth(l->l, r->l, k, lx, m);
    else
        return kth(l->r, r->r, k-s, m, rx);
}

void solve(){
    Node *root = new Node;
    build(root); roots.push_back(root);

}

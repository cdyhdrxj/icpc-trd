const int k = 26;
struct Trie{
	struct Node{
		Node* to[k] = {0};
		bool terminal = false;
	};

	Node* root;

	void init(){
		root = new Node();
	}

	void add(string& s) {
		Node* v = root;
		for (char c : s) {
			c -= 'a';
			if (!v->to[c])
				v->to[c] = new Node();
			v = v->to[c];
		}
		v->terminal = true;
	}

	void erase(string& s) {
		Node* v = root;
		int fl = 1;
		for (char c : s) {
			c -= 'a';
			if (!v->to[c]) {
				fl = 0;
				break;
			}
			v = v->to[c];
		}
		if(fl) v->terminal = false;
	}

	void build(vector<string>& a){
		init();
		for(auto &s : a)
			add(s);
	}

	Trie(vector<string>& a){
		build(a);
	}
};

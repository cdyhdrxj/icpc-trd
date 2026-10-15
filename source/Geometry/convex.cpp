struct Point { ll x, y; };

Point operator - (const Point &a, const Point &b) {
	return {a.x - b.x, a.y - b.y};
}

ll cross_product(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

bool operator < (const Point &p, const Point &q) {
	return p.x < q.x || (p.x == q.x && p.y < q.y);
}

vector<Point> convex_hull(vector<Point> &a) {
	vector<Point> up, dw; 
	sort(a.begin(), a.end());
	
	for(auto p : a){
		while(up.size() > 1 && cross_product(p - up.back(), up.back() - up[up.size() - 2]) >= 0)
			up.pop_back();
		up.push_back(p);
 
		while(dw.size() > 1 && cross_product(p - dw.back(), dw.back() - dw[dw.size() - 2]) <= 0)
			dw.pop_back();
		dw.push_back(p);
	}
	dw.pop_back();
	reverse(dw.begin(), dw.end());
	dw.pop_back();
	up.insert(up.end(), dw.begin(), dw.end());
 
	return up;
}

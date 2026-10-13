#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-7;
double pi = acos(-1);

struct Line{
    double a, b, c;
    Point v;
    Line (double A, double B, double C) : a(A), b(B), c(C) {
        double len = Point(a, b).len;
        a /= len; b /= len; c /= len;

        if (a < 0 || a == 0 && b < 0){
            a *= -1; b *= -1; c *= -1;
        }

        v = Point(-b, a);
    }

    Line (const Point& p, const Point& q){
        a = p.y - q.y;
        b = q.x - p.x;
        c = -(p.x*a + p.y*b);
        *this = Line(a, b, c);
    }

    Line (){}

    double distance(const Point& p) const {
        return abs(a*p.x + b*p.y + c);
    }

    double vect(const Point& p) const {
        return a*p.x + b*p.y + c;
    }
};

pair<int, Point> intersect(const Line& l, const Line& m){
    double z = l.a * m.b - l.b * m.a;
    if (z == 0){
        if (l.c == m.c){
            return {1, Point()};
        }
        return {-1, Point()};
    }

    double x = -(l.c * m.b - l.b * m.c) / z;
    double y = -(l.a * m.c - l.c * m.a) / z;
    return {0, Point(x, y)};
}

struct Beam {
    Line l;
    Point v;
    Point b;
    Beam (const Point& p, const Point& q) : b(p), v(q), l(p, q){}
    Beam (){}

    double distance(const Point& p) const {
        if (scal(v - b, p - b) < 0){
            return sqrt(dst_2(b, p));
        }
        return l.distance(p);
    }

    bool in_sector(const Point& p) const {
        return scal(v - b, p - b) > -eps;
    }
};

double distance(const Beam& a, const Beam& b){
    const auto& res = intersect(a.l, b.l);
    if (res.first == 0){
        const Point& p = res.second;
        // cout << p << endl;
        if (a.in_sector(p) && b.in_sector(p)){
            return 0;
        }
    }

    return min(a.distance(b.b), b.distance(a.b));
}

struct Segment {
    Point p, q;
    Beam b1, b2;
    Line l;
    Segment (Point p, Point q) : p(min(p, q)), q(max(p, q)), b1(p, q), b2(q, p), l(p, q) {}
    Segment () {}
    
    double distance(const Point& p) const {
        return max(b1.distance(p), b2.distance(p));
    }

    bool in_sector(const Point& p) const {
        return b1.in_sector(p) && b2.in_sector(p);
    }
};

double distance(const Segment& s, const Segment& t){
    const auto& res = intersect(s.l, t.l);
    if (res.first == 0){
        const Point& p = res.second;
        if (s.in_sector(p) && t.in_sector(p)){
            return 0;
        }
    }

    return min(
        min(s.distance(t.p), s.distance(t.q)),
        min(t.distance(s.p), t.distance(s.q))
    );
}

struct Circle {
    Point c;
    double r;
    double rr;

    Circle () {}
    Circle (const Point& C, double R) : c(C), r(R), rr(R * R) {}

    double distance_center_2(const Point& p){
        return distance_2(c, p);
    }

    int point_position(const Point& p){
        double d = distance_center_2(p);
        if (d < rr - eps){
            return 1;
        }
        if (d < rr + eps){
            return 0;
        }
        return -1;
    }

    pair<int, pair<Point, Point>> tangent(const Point& p){
        if (point_position(p) == 1){
            return {0, {Point(), Point()}};
        }

        if (point_position(p) == 0){
            return {1, {Point(), Point()}};
        }

        double cq = r;
        double cp = distance(c, p);
        double pq = sqrt(cp*cp - cq*cq);

        double sp = pq * pq / cp;
        double sq = cq * pq / cp;

        Point SP = (c - p) * (sp / cp);
        Point SQ = SP.rotate(pi / 2) * (sq / SP.len);

        return {2, {SP, SQ}};
    }
};

void solve(){

    Point p, o;
    double r;
    cin >> o >> r >> p;

    Circle c(o, r);

    auto res = c.tangent(p);

    cout << res.first << '\n';

    if (res.first == 0){
        return;
    }

    if (res.first == 1){
        cout << p;
        return;
    }

    const Point& v = res.second.first;
    const Point& u = res.second.second;

    cout << p + v << '\n';

    cout << v.len << ' ' << u.len << '\n';

    cout << p + v + u.rotate(pi) << '\n' << p + v + u;

}
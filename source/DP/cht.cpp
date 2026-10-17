typedef long long integer;
typedef long double ld;
struct Line {
    integer k, b;
    Line():
    k(0), b(0) {}
    Line(integer k, integer b):
    k(k), b(b) {}
    ld operator()(ld x) {
        return x * (ld)k + (ld)b;
    }
};
const integer INF = 2e18; // change
struct CHT {
    vector<Line> lines;
bool mini; // cht on minimum

ld f(Line l1, Line l2) {
    return (ld)(l1.b - l2.b) / (ld)(l2.k - l1.k);
}

void addLine(integer k, integer b) {
    if (!mini) {
        k = -k;
        b = -b;
    }
    Line l(k, b);
    while (lines.size() > 1) {
        if (lines.back().k == k) {
            if (lines.back().b > b)
                lines.pop_back();
            else
                break;
            continue;
        }
        ld x1 = f(lines.back(), l);
        ld x2 = f(lines.back(),
            lines[lines.size() - 2]);
        if (x1 > x2)
            break;
        lines.pop_back();
    }
    if (!lines.size() || lines.back().k != k)
        lines.push_back(l);
}

CHT(vector<pair<integer, integer> > v,
bool ok = 1) // change
{
    mini = ok;
    lines.clear();
    for (int i = 0; i < v.size(); i++)
        addLine(v[i].first, v[i].second);
}

integer getmin(integer x)
//find of integer!
{
    if (!lines.size())
        return (mini ? INF : -INF);
    int l = 0, r = lines.size();
    while (r - l > 1) {
        int mid = (r + l) / 2;
        if (f(lines[mid], lines[mid - 1])
            <= (ld)x)
            l = mid;
        else
            r = mid;
    }
    integer ans = lines[l].k * x +
    lines[l].b;
    return (mini ? ans : -ans);
}
};
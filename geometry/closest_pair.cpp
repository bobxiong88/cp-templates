#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#define int ll
#define dbg(x) cout << #x << ": " << x << '\n'
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vector<int>> 

struct Point{
    double x, y;
    int i; 
};

bool compX(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool compY(const Point&a, const Point &b) {
    return a.y < b.y;
}

double sqr(double x) {
    return x*x;
}

double dist(Point a, Point b) {
    return sqrt(sqr(a.x - b.x)+ sqr(a.y-b.y));
}

struct Soln{
    double d;
    Point a, b;
    Soln() : d{1e18} {}
    Soln(double d, Point a, Point b) : d{d}, a{a}, b{b} {}
    Soln(Point a, Point b) : d{dist(a, b)}, a{a}, b{b} {}

    bool operator<(const Soln &other) const {
        return d < other.d;
    }
};



Soln findMinSpanningPair(double delta, const vector<Point> &Py, double xmid) {
    int n = Py.size();
    vector<Point> S;
    for (auto p : Py) {
        if (abs(p.x - xmid) <= delta) {
            S.pb(p);
        }
    }
    if (S.size() < 2) {
        return Soln();
    }
    Soln best = Soln(S[0], S[1]);
    for (int i = 0; i < S.size(); i++) {
        int k = 0;
        for (int j = i+1; j < S.size(); j++) {
            if (S[j].y-S[i].y > delta) break;
            best = min(best, Soln(S[i], S[j]));
            k++;
        }
        assert(k<=8);
    }
    return best;
}

Soln solve(const vector<Point> &Px, const vector<Point> &Py) {
    int n = Px.size();
    if (n < 4) {
        Soln best;
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                best = min(best, Soln(Px[i], Px[j]));
            }
        }
        return best;
    } else {
        auto xmid = Px[n/2].x;
        auto PxL = vector<Point>(Px.begin(), Px.begin() + n/2);
        auto PxR = vector<Point>(Px.begin() + n/2, Px.end());
        vector<Point> PyL, PyR;
        for (auto p : Py) {
            if (p.x <= xmid) PyL.push_back(p);
            else PyR.push_back(p);
        }
        auto left = solve(PxL, PyL);
        auto right = solve(PxR, PyR);
        
        double delta = min(left.d, right.d);

        auto span = findMinSpanningPair(delta, Py, xmid);

        return min({left, right, span});
    }
}

Soln shamos(vector<Point> pnts) {
    sort(pnts.begin(), pnts.end(), compX);
    auto Px = pnts;
    sort(pnts.begin(), pnts.end(), compY);
    auto Py = pnts;
    return solve(Px, Py);
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<Point> pnts;
        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            pnts.pb({x,y,i});
        }
        auto ans = shamos(pnts);
        cout << std::setprecision(4) << fixed << ans.d << "\n";
        cout << ans.a.i << " " << ans.b.i << "\n";
    }
}
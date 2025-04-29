#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//#define int ll
#define dbg(x) cout << #x << ": " << x << '\n'
#define pb push_back

// kactl stuff
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef long double ld;

ll MOD = int(1e9)+7;
ll MOD2 = 999998727899999;

// const ll MINL = -9223372036854775808;
// const ll MAXL = 9223372036854775807;
// const int MINI = -2147483648;
// const int MAXI = 2147483647;

ll binpow(ll a, ll b, ll m = MOD) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}


template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	ld dist() const { return sqrt((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ld> P;

// number of steps
const int M = 50;

// number of directions to try
const ld ds = 1000;

// start stepsize
ld eps = 100;

ld f(P p) {
    // fill in f
}

pair<P, ld> solve(P p) {
    for (int i = 0; i < M; i++) {
        ld best = f(p);
        P u(1, 0), nxt;
        u = u*eps;
        for (int j = 0; j < ds; j++) {
            P nxt_j = p + u;
            ld f_j = f(nxt_j);
            if (f_j < best) {
                best = f_j;
                nxt = nxt_j;
            }
            u = u.rotate(2*3.14159265358979323846264338327950288/ds);
        }
        if (best == f(p)) {
            eps = eps*0.5;
        } else {
            p = nxt;
        }
        if (eps <= 1e-15) break;
    }
    return {p, f(p)};
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
}

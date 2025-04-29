

int space() const {
    if (y < 0) return -1;
    if (y == 0 && x >= 0) return 0;
    return 1;
}

bool comp(const P&a, const P&b) {
    if (a.space() != b.space()) return a.space() < b.space();
    return a.cross(b) > 0;
}

sort(pnts.begin(), pnts.end(), comp);

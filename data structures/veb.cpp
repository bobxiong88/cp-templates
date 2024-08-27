#include <bits/stdc++.h>
using namespace std;

const int inf = int(1e9);

struct VEBTree {
    int min = inf, max = -1, 
     log, highSize, lowSize;
    unique_ptr<VEBTree[]> cluster; 
    std::unique_ptr<VEBTree> summary;


    int high(int key) {
        return key >> lowSize;
    }
    int low(int key) {
        return key & ((1 << lowSize) - 1);
    }

    int index(int i, int j) {
        return j + (i << lowSize);
    }
    
    VEBTree() = default;

    VEBTree(int log) : 
        log{log}, 
        highSize{log >> 1},
        lowSize{(log >> 1) + (log&1)} 
    {
        if (highSize >= 1) {
            cluster = std::make_unique<VEBTree[]>(1 << highSize);
            for (int i = 0; i < (1 << highSize); ++i) {
                cluster[i] = VEBTree(lowSize);
            }
            summary = std::make_unique<VEBTree>(highSize);
        } else {
            cluster = nullptr;
            summary = nullptr;
        }
    }; 
    
    int successor(int key) {
        if (key > max) return -1;
        if (key <= min) return min;
        if (log == 1) {
            if (key == 0) {
                return min;
            } else {
                return 1;
            }
        }
        int currCluster = high(key);
        int currInCluster = low(key);
        int nextInCluster = cluster[currCluster].successor(currInCluster);
        if (nextInCluster != -1) return index(currCluster, nextInCluster);
        int nextCluster = summary->successor(currCluster+1);
        if (nextCluster == -1) return -1;
        nextInCluster = cluster[nextCluster].min;
        return index(nextCluster, nextInCluster);
    }

    void insert(int key) {
        min = std::min(min, key);
        max = std::max(max, key);
        if (log > 1) {
            int currCluster = high(key);
            int currInCluster = low(key);
            if (cluster[currCluster].min == inf) summary->insert(currCluster);
            cluster[currCluster].insert(currInCluster);
        }        
    }

    void erase(int key) {
        if (log == 1) {
            if (min == key) {
                if (max == key) {
                    min = inf;
                    max = -1;
                } else {
                    min = max;
                }
            } else if (max == key) {
                max = min;
            }
            return;
        }
        int i = high(key);
        int j = low(key);
        if (cluster[i].min == inf) {
            return;
        }
        cluster[i].erase(j);
        if (cluster[i].min == inf) {
            summary->erase(i);
        }
        if (min == key) {
            if (max == key) {
                min = inf;
                max = -1;
            } else {
                int si = summary->min;
                min = index(si, cluster[si].min);
            }
        } else if (max == key) {
            int si = summary->max;
            max = index(si, cluster[si].max);
        } 
    }
};

int main() {
    int log = 4;
    VEBTree t(log);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int op, k;
        cin >> op >> k;
        if (op == 1) {
            cout << t.successor(k) << "\n";
        } else if (op == 2) {
            t.insert(k);
        } else {
            t.erase(k);
        }

    }
}
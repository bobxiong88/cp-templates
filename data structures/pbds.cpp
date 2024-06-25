#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>


// struct pog{
//     int x, y;
// };
// bool comp(const pog &a, const pog &b){
//     return a.x < a.y;
// }
using namespace std;
using namespace __gnu_pbds;

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> mytree;
int main(){
    while (true){
        int t, x;
        cin >> t >> x;
        if (t == 1) {
            mytree.insert(x);
            cout << "inserted " << x << " into tree\n";
        }
        else if (t == 2){
            cout << "there are " << mytree.order_of_key(x) << " elements strictly smaller than " <<x << "\n";
        }
        else{
            cout << "element at position " << x << " is " << *mytree.find_by_order(x) << "\n";
        }
    }
}

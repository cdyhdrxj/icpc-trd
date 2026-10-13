#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

// Example
ordered_set X;
X.insert(1);

cout << *X.find_by_order(0) << endl; // 2

cout << X.order_of_key(1) << endl;   // 0
cout << X.order_of_key(3) << endl;   // 2
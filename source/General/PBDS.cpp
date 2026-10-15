// Ordered set

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

ordered_set X;
X.insert(1);
X.insert(4);

*X.find_by_order(1); // 4
(end(X) == X.find_by_order(6)); // true

X.order_of_key(-5);  // 0
X.order_of_key(1);   // 0
X.order_of_key(3);   // 1


// Hash table

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};

gp_hash_table<int, int, chash> table;
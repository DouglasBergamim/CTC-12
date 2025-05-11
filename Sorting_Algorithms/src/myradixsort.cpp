
#include <mysortfunctions.h>
#include <queue>
#include <stack>


void myradixsort(std::vector<int> &v, SortStats &stats) {
    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 1;
    // you need to set the depth = the maximum height of the tree of recursion calls. 
    stats.depth_recursion_stack = 1;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    stats.custom1 = 2;


    auto mask = 0x0F;
    const int bits_per_bucket = 4;
    int num_buckets = 1 << bits_per_bucket;
    int max_bits = sizeof(int) * CHAR_BIT;

    std::vector<std::queue<int>> q(num_buckets);
    for (int shift = 0; shift <  max_bits; shift += bits_per_bucket) {
        for (int j : v)
            q[(j >> shift) & mask ].push(j);
        int k = 0;
        for (int j = 0; j < num_buckets; j++){
            while (!q[j].empty()){
                v[k++] = q[j].front();
                q[j].pop();
            }
        }
    }
}

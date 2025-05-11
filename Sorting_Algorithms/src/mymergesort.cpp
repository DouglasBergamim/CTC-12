
#include <mysortfunctions.h>

void mymergesort_recursive(std::vector<int> &v, SortStats &stats) {
    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 0;
    // you need to set the depth = the maximum height of the tree of recursion calls. 
    stats.depth_recursion_stack = 1;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    stats.custom1 = 0; //current path
    std::vector<int> aux(v.size());
    helper_mergesort_recursive(v, stats, 0, v.size() - 1, 1, aux);
}

void helper_mergesort_recursive(std::vector<int> &v,SortStats &stats, int begin, int end, float current_path, std::vector<int> &aux)
{
    ++stats.recursive_calls;
    stats.depth_recursion_stack = std::max(stats.depth_recursion_stack, current_path);
    if (begin < end)
    {
        int m = (begin + end) / 2;
        helper_mergesort_recursive(v,stats, begin, m, current_path + 1, aux);
        helper_mergesort_recursive(v,stats, m + 1, end, current_path + 1, aux);
        merge(v, begin, m, end, aux);
    }
}

void merge(std::vector<int> &v,int begin, int m, int end, std::vector<int>& aux){
    int left= begin;
    int right = m+1;
    int k = begin;

    while (left <= m && right <= end) {
        if (v[left] < v[right]) {
            aux[k++] = v[left++];
        } else {
            aux[k++] = v[right++];
        }
    }

    while (left <= m)
        aux[k++] = v[left++];

    while (right <= end)
        aux[k++] = v[right++];

    std::copy(&aux[begin], &aux[end+1],&v[begin]);
}

void mymergesort_iterative(std::vector<int> &v, SortStats &stats) {
    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 1;
    // you need to set the depth = the maximum height of the tree of recursion calls. 
    stats.depth_recursion_stack = 1;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    stats.custom1 = 2;
    std::vector<int> aux(v.size());
    int b = 1;
    int final = v.size() - 1;
    int r, m, p;
    while (b < final){
        p = 0;
        while (p+b <= final) {
            r = std::min(final, p+ (2*b) - 1);
            m = p + b -1;
            merge(v, p, m, r, aux);
            p += 2*b;
        }
        b *=2;
    }
}
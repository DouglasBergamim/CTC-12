
#include <mysortfunctions.h>

// you only need to mantain the headers. You can create aux funcs, objects, or create a generic quicksort that can work with different functions to select the pivot.

/// the most comon quicksort, with 2 recursive calls
void myquicksort_2recursion_medianOf3(std::vector<int> &v, SortStats &stats) {
    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 0;
    // you need to set the depth = the maximum height of the tree of recursion calls.
    stats.depth_recursion_stack = 0;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    stats.custom1 = 2;
    helper_quicksort_2recursion_medianOf3(v, stats, 0, v.size() - 1, 1);
}// function myquicksort_2recursion_medianOf3

void helper_quicksort_2recursion_medianOf3(std::vector<int> &v, SortStats &stats, int begin, int end, float current_path) {
    ++stats.recursive_calls;
    stats.depth_recursion_stack = std::max(stats.depth_recursion_stack, current_path);
    if (begin < end) {
        median(v, begin, end);
        const int p = particion(v, begin, end);
        helper_quicksort_2recursion_medianOf3(v, stats, begin, p - 1, current_path + 1);
        helper_quicksort_2recursion_medianOf3(v, stats, p+1, end, current_path + 1);
    }
}

int particion(std::vector<int> &v, int begin, int end) {
    int pivot = v[begin];
    int left = begin + 1;
    int right = end;

    while (true) {
        while (left <  end and v[left] < pivot) left++;
        while (right > begin and v[right] >=  pivot) right--;
        if (left >= right)
            break;
        troca(v, left, right);
    }
    troca(v, begin, right);
    return right;
}


void median(std::vector<int> &v, int begin, int end)
{
    int pivot = begin;
    int m = (begin + end) / 2;
    if ((v[m] >= v[begin] and v[m] <= v[end]) or (v[m] >= v[end] and v[m] <= v[begin]))
        pivot = m;
    else if ((v[end] >= v[begin] and v[end] <= v[m]) or ( v[end] >= v[m] and v[end] <= v[begin]))
        pivot = end;
    if (pivot != begin)
        troca(v, pivot, begin);
}


/// quicksort with one recursive call
void myquicksort_1recursion_medianOf3(std::vector<int> &v, SortStats &stats) {
    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 0;
    // you need to set the depth = the maximum height of the tree of recursion calls. 
    stats.depth_recursion_stack = 0;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    stats.custom1 = 2;
    helper_quicksort_1recursion_medianOf3(v, stats, 0, v.size() - 1, 1);
} // function myquicksort_1recursion_medianOf3

void helper_quicksort_1recursion_medianOf3(std::vector<int> &v, SortStats &stats, int begin, int end, float current_path) {
    ++stats.recursive_calls;
    stats.depth_recursion_stack = std::max(stats.depth_recursion_stack, current_path);
    while (begin < end){
        median(v, begin, end);
        const int p = particion(v, begin, end);
        if (p - begin < end - p){
            helper_quicksort_1recursion_medianOf3(v, stats, begin, p - 1, current_path + 1);
            begin = p + 1;
        }
        else {
            helper_quicksort_1recursion_medianOf3(v, stats, p+1, end, current_path + 1);
            end = p - 1;
        }
    }
}
/// quicksort with fixed pivot 
/// be sure to compare with equivalent implementation 
/// e.g., if you do 1 recursive call, compare with the 1recursion version
void myquicksort_fixedPivot(std::vector<int> &v, SortStats &stats){
    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 0;
    // you need to set the depth = the maximum height of the tree of recursion calls. 
    stats.depth_recursion_stack = 0;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    stats.custom1 = 2;
    helper_quicksort_fixedPivot(v, stats, 0, v.size() - 1, 1);
} // myquicksort_fixedPivot

void helper_quicksort_fixedPivot(std::vector<int> &v, SortStats &stats, int begin, int end, float current_path)
{
    ++stats.recursive_calls;
    stats.depth_recursion_stack = std::max(stats.depth_recursion_stack, current_path);
    while (begin < end){
        const int p = particion(v, begin, end);
        if (p - begin < end - p){
            helper_quicksort_fixedPivot(v, stats, begin, p - 1, current_path + 1);
            begin = p + 1;
        }
        else {
            helper_quicksort_fixedPivot(v, stats, p+1, end, current_path + 1);
            end = p - 1;
        }
    }
}

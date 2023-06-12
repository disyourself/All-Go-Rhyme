
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
auto buble_sort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}


int main()
{
    vector<int> a = {7, 7, 48, 8, 8, 64, 2, 5, 1};
    buble_sort(a);
    for_each(a.begin(), a.end(), [](auto x) { cout << x << ' '; });


    return 0;
}

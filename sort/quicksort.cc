#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;



int partition(vector<int> &arr, int l, int r)
{
    int n = arr.size() - 1;
    int i = 0;
    int v = arr[i];
    while (i < n) {
        while (arr[n] > v)
            --n;
        swap(arr[n], arr[i++]);

        while (arr[i] < v)
            ++i;
        swap(arr[i], arr[n--]);
    }
    return i;
}



int main()
{
    vector<int> src = {5, 4, 9, 2, 1, 0, 3, 6, 8};

    std::function<void(vector<int> &)> quicksort = [src](auto &arr) {
        int  n = arr.size();
        auto i = partition(arr, 0, n);
        partition(arr, 0, i - 1);
        partition(arr, i + 1, n);
    };
    quicksort(src);

    for (auto x : src) {
        cout << x;
    };
}

#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

int main()
{
    // メモリが足りなくなりそうなので絶対値が大きい数は探索しない
    // 探索範囲 [-lim, lim)
    const int lim = 1000;
    // 式に使う 7 の個数の上限
    const int N = 10;

    // 7 を i 個使って作れる数の集合
    vector<set<int>> numbers(N+1, set<int>());
    numbers[1].insert(7);  // 7 を 1 個使って作れる数の集合の要素は 7 のみ

    // 7 を i 個使って j を作る式
    // -lim <= j < lim のため、0 <= j + lim < lim * 2 とする（イクセス表現）
    vector<vector<string>> formula(N+1, vector<string>(lim * 2, ""));
    formula[1][7 + lim] = "7";  // 7 を 1 個使って 7 を作る式

    return 0;
}

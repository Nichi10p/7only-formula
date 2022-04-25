#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

#define inRange(left, x, right) (left <= x && x < right)

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

    for (int i = 2; i <= N; i++)
    {
        // i = j + k かつ j <= k を満たす j, k
        // numbers[j] と numbers[k] から numbers[i] の要素を構築
        // 同時に formula[i][?] も更新
        for (int j = 1; j <= (i / 2); j++)
        {
            int k = i - j;
            for (auto &x : numbers[j])
            {
                for (auto &y : numbers[k])
                {
                    if (inRange(-lim, x + y, lim))
                    {
                        numbers[i].insert(x + y);
                        formula[i][x + y + lim] = "(" + formula[j][x + lim] + "+" + formula[k][y + lim] + ")";
                    }
                    if (inRange(-lim, x - y, lim))
                    {
                        numbers[i].insert(x - y);
                        formula[i][x - y + lim] = "(" + formula[j][x + lim] + "-" + formula[k][y + lim] + ")";
                    }
                    if (inRange(-lim, x * y, lim))
                    {
                        numbers[i].insert(x * y);
                        formula[i][x * y + lim] = " " + formula[j][x + lim] + "*" + formula[k][y + lim] + " ";
                    }
                    if (y != 0 && x % y == 0)  // 確実に inRange である
                    {
                        numbers[i].insert(x / y);
                        formula[i][x / y + lim] = " " + formula[j][x + lim] + "/" + formula[k][y + lim] + " ";
                    }

                    if (inRange(-lim, y - x, lim))
                    {
                        numbers[i].insert(y - x);
                        formula[i][y - x + lim] = "(" + formula[k][y + lim] + "-" + formula[j][x + lim] + ")";
                    }
                    if (x != 0 && y % x == 0)  // 確実に inRange である
                    {
                        numbers[i].insert(y / x);
                        formula[i][y / x + lim] = " " + formula[k][y + lim] + "/" + formula[j][x + lim] + " ";
                    }
                }
            }
        }
    }

    cout << formula[9][425 + lim] << endl;
    return 0;
}

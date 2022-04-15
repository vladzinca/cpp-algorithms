#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, k;
    vector<int> x, y;

    void read_input() {
        ifstream fin("walsh.in");
        fin >> n >> k;
        x.push_back(-1);
        y.push_back(-1);
        for (int i = 1, e, f; i <= k; i++) {
            fin >> e >> f;
            x.push_back(e);
            y.push_back(f);
        }
        fin.close();
    }

    int negate(int x) {
        if (x == 0)
            return 1;
        else
            return 0;
    }

    int walsh(int x, int y, int n) {
        if (n == 2) {
            if (x == 2 && y == 2)
                return 1;
            else
                return 0;
        } else {
            if (x <= n / 2 && y <= n / 2)
                return walsh(x, y, n / 2);
            else if (x <= n / 2 && y > n / 2)
                return walsh(x, y - n / 2, n / 2);
            else if (x > n / 2 && y <= n / 2)
                return walsh(x - n / 2, y, n / 2);
            else
                return negate(walsh(x - n / 2, y - n / 2, n / 2));
        }
    }

    vector<int> get_result() {
        vector<int> v;
        v.push_back(-1);
        for (int i = 1; i <= k; i++)
            v.push_back(walsh(x[i], y[i], n));
        return v;
    }

    void print_output(vector<int> result) {
        ofstream fout("walsh.out");
        for (int i = 1; i <= k; i++)
            fout << result[i] << "\n";
        fout.close();
    }
};

int main() {
    auto *task = new (nothrow) Task();
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

class Task
{
public:
    void solve()
    {
        read_input();
        print_output(get_result());
    }

private:
    int n, k;
    vector<int> x, y;

    void read_input()
    {
        ifstream fin("walsh.in");
        fin >> n >> k;
        x.push_back(-1);
        y.push_back(-1);
        for (int i = 1, e, f; i <= k; i++)
        {
            fin >> e >> f;
            x.push_back(e);
            y.push_back(e);
        }
        fin.close();
    }

    vector<int> get_result()
    {
        return x;
    }

    void print_output(vector<int> result)
    {
        ofstream fout("walsh.out");
        for (int i = 1; i <= k; i++)
            fout << result[i] << "\n";
        fout.close();
    }
};

int main()
{
    auto *task = new (nothrow) Task();
    if (!task)
    {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
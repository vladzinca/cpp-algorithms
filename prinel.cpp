#include <bits/stdc++.h>
using namespace std;

struct Object {
    int t;
    int targetTime;
    int price;

    Object(int _t, int _targetTime, int _price)
        : t(_t)
        , targetTime(_targetTime)
        , price(_price) { }
};

bool comparator(Object o1, Object o2) {
    return (1.0 * o1.price / o1.targetTime) > (1.0 * o2.price / o2.targetTime);
}

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, k;
    vector<int> target;
    vector<int> p;
    vector<Object> objs;

    void read_input() {
        ifstream fin("prinel.in");
        fin >> n >> k;
        for (int i = 0, onetarget; i < n; i++) {
            fin >> onetarget;
            target.push_back(onetarget);
            // objs.push_back(Object(weight, price));
        }
        for (int i = 0, onep; i < n; i++) {
            fin >> onep;
            p.push_back(onep);
            objs.push_back(Object(target[i], minOperations(1, target[i]), onep));
        }
        fin.close();
    }

    vector<int> printDivisors(int n)
    {
        vector<int> listaDeNumerePrime;
        for (int i = 1; i <= sqrt(n); i++)
            if (n % i == 0)
                listaDeNumerePrime.push_back(i);
        listaDeNumerePrime.push_back(n);
        return listaDeNumerePrime;
    }

    struct node {
        int val;
        int level;
    };

    // Returns minimum number of operations
    // needed to convert x into y using BFS
    int minOperations(int x, int y)
    {
        // To keep track of visited numbers
        // in BFS.
        set<int> visit;

        // Create a queue and enqueue x into it.
        queue<node> q;
        node n = { x, 0 };
        q.push(n);

        // Do BFS starting from x
        while (!q.empty()) {
            // Remove an item from queue
            node t = q.front();
            q.pop();

            // If the removed item is target
            // number y, return its level
            if (t.val == y)
                return t.level;

            // Mark dequeued number as visited
            visit.insert(t.val);

            // If we can reach y in one more step
            vector<int> divizori = printDivisors(t.val);
            for (int i = 0; i < divizori.size(); i++)
            {
                if (t.val + divizori[i] == y)
                    return t.level + 1;
            }
            // if (t.val * 2 == y || t.val - 1 == y)
            //     return t.level + 1;

            // Insert children of t if not visited
            // already
            // if (visit.find(t.val * 2) == visit.end()) {
            //     n.val = t.val * 2;
            //     n.level = t.level + 1;
            //     q.push(n);
            // }
            // if (t.val - 1 >= 0
            //     && visit.find(t.val - 1) == visit.end()) {
            //     n.val = t.val - 1;
            //     n.level = t.level + 1;
            //     q.push(n);
            // }
            for (int i = 0; i < divizori.size(); i++)
            {
                if (visit.find(t.val + divizori[i]) == visit.end()) {
                    n.val = t.val + divizori[i];
                    n.level = t.level + 1;
                    q.push(n);
                }
            }
        }
        return -1;
    }


    int get_result() {
        // TODO: Aflati profitul maxim care se poate obtine cu obiectele date.
        sort(objs.begin(), objs.end(), comparator);
        // for (int i = 0; i < n; i++){
        //     cout << "Obiectul cu target " << objs[i].t << ", nr operatii " << objs[i].targetTime << " si price-ul " << objs[i].price << " raportul, " << (double) objs[i].price / objs[i].targetTime << "\n";
        // }
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (k - objs[i].targetTime < 0)
                return result;
            else
            {
                // cout << "Obiectul cu target " << objs[i].t << ", nr operatii " << objs[i].targetTime << " si price-ul " << objs[i].price << " raportul, " << (double) objs[i].price / objs[i].targetTime << "\n";
                result += objs[i].price;
                k -= objs[i].targetTime;
            }
        }
        return result;
        // for (int i = 0; i < n; i++) {
        //     if (w > 0) {
        //         if (w >= objs[i].weight) {
        //             output += objs[i].price;
        //             w = w - objs[i].weight;
        //         } else {
        //             output += 1.0 * w / objs[i].weight * objs[i].price;
        //             w = 0;
        //         }
        //     }
        // }
        // vector<int> result;
        // result = printDivisors(target);
        // cout << "target este " << target << "\n";
        // for (int i = 0; i < result.size(); i++)
        //     cout << result[i] << " ";
        // cout << "\n";
        // int result2;
        // result2 = minOperations(start, target);
        // cout << "Mi-a dat dzeu " << result2 << "\n";
        // return result2;
    }

    void print_output(int result) {
        ofstream fout("prinel.out");
        fout << result;
        // cout << result;
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
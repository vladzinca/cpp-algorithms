#include <bits/stdc++.h>
using namespace std;

/* structura in care se pastreaza perechile t - target[i],
    targetTime - numarul de operatii necesare pentru a ajunge
    din 1 in target[i], si price - p[i] */
struct Object {
    int t;
    int targetTime;
    int price;

    Object(int _t, int _targetTime, int _price)
        : t(_t), targetTime(_targetTime), price(_price) { }
};

/* compara perechile dupa raportul price / targetTime */
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
    vector<Object> objs;

    /* citeste n, k si vectorii target si p, adaugand in cele
        din urma valorile cu acelasi index in acelasi obiect */
    void read_input() {
        ifstream fin("prinel.in");
        fin >> n >> k;
        for (int i = 0, onetarget; i < n; i++) {
            fin >> onetarget;
            target.push_back(onetarget);
        }
        for (int i = 0, onep; i < n; i++) {
            fin >> onep;
            objs.push_back(Object(target[i],
                            minOperations(target[i]), onep));
        }
        fin.close();
    }

    /* calculeaza divizorii numarului n, inclusiv 1 si el insusi */
    vector<int> getDivisors(int n) {
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

    /* folosind o parcurgere BFS, determina numarul de
        transformari pentru a ajunge din 1 in target[i] */
    int minOperations(int a) {
        set<int> visit;
        queue<node> q;
        node n = {1, 0};
        q.push(n);
        while (!q.empty()) {
            node t = q.front();
            q.pop();
            if (t.val == a)
                return t.level;
            visit.insert(t.val);
            vector<int> divizori = getDivisors(t.val);
            for (int i = 0; i < divizori.size(); i++)
                if (t.val + divizori[i] == a)
                    return t.level + 1;
            for (int i = 0; i < divizori.size(); i++)
                if (visit.find(t.val + divizori[i]) == visit.end()) {
                    n.val = t.val + divizori[i];
                    n.level = t.level + 1;
                    q.push(n);
                }
        }
        return -1;
    }

    /* rezolva cerinta sortand vectorul de elemente si selectand
        convenabil primele elemente din vectorul sortat astfel incat
        rezultatul sa fie cat mai mare */
    int get_result() {
        sort(objs.begin(), objs.end(), comparator);
        int result = 0;
        for (int i = 0; i < n; i++)
            if (k - objs[i].targetTime < 0) {
                return result;
            } else {
                result += objs[i].price;
                k -= objs[i].targetTime;
            }
        return result;
    }

    /* scrie rezultatul in fisier */
    void print_output(int result) {
        ofstream fout("prinel.out");
        fout << result;
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

#include <bits/stdc++.h>
using namespace std;

struct Word {
    string letters;
    float ourLetterOccurence;

    Word(string _letters, float _ourLetterOccurence)
        : letters(_letters)
        , ourLetterOccurence(_ourLetterOccurence) { }
};

bool comparator(Word w1, Word w2) {
    if (w1.ourLetterOccurence == w2.ourLetterOccurence)
        return w1.letters.length() < w2.letters.length();
    else
        return w1.ourLetterOccurence > w2.ourLetterOccurence;
}

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    vector<Word> v;
    vector<int> nrAparitii;
    // vector<float> maximalOccurence;

    void read_input() {
        for (int i = 0; i < 26; i++)
        {
            nrAparitii.push_back(0);
            // maximalOccurence.push_back(0);
        }
        ifstream fin("statistics.in");
        fin >> n;
        string s;
        for (int i = 0; i < n; i++) {
            fin >> s;
            Word word(s, 0);
            v.push_back(word);
            for (int j = 0; j < s.length(); j++) {
                int nrLiterei = s[j] - 97;
                nrAparitii.at(nrLiterei)++;
            }
        }
        // for (int i = 0; i < 26; i++) {
        //     cout << nrAparitii[i] << "\n";
        // }
        // cout << (char)(max_element(nrAparitii.begin(), nrAparitii.end()) - nrAparitii.begin() + 97) << "\n";
        fin.close();
    }

    int countTheLetters(string s, char c) {
        int nr = 0;
        for (int i = 0; i < s.length(); i++)
            if (s[i] == c)
                nr++;
        return nr;
    }

    int get_result() {
        char searchedForLetter = (char)(max_element(nrAparitii.begin(), nrAparitii.end()) - nrAparitii.begin() + 97);
        for (int i = 0; i < n; i++) {
            v[i].ourLetterOccurence = (float) countTheLetters(v[i].letters, searchedForLetter) / v[i].letters.length();
        }
        sort(v.begin(), v.end(), comparator);
        int maxConcatCounter = 0, foundLetters = 0, totalLettersSearched = 0;
        foundLetters = countTheLetters(v[0].letters, searchedForLetter);
        totalLettersSearched = v[0].letters.length();
        float theOccurenceISeek = (float) foundLetters / totalLettersSearched;
        if (theOccurenceISeek <= 0.5)
            return -1;
        else
            maxConcatCounter++;
        for (int i = 1; i < n; i++) {
            // cout << v[i].letters << " si ourLetterOccurence este " << v[i].ourLetterOccurence << "\n";
            float potentialCoeff = (float) (foundLetters + countTheLetters(v[i].letters, searchedForLetter)) / (totalLettersSearched + v[i].letters.length());
            if (i == 24)
                cout << foundLetters << " se imparte la " << totalLettersSearched << "\n";
            if (potentialCoeff <= 0.5)
            {
                cout << "dam skip pentru ca avem \n";
                continue;
            }
            else
            {
                maxConcatCounter++;
                foundLetters += countTheLetters(v[i].letters, searchedForLetter);
                totalLettersSearched += v[i].letters.length();
            }
        }
        return maxConcatCounter;
    }

    void print_output(int result) {
        ofstream fout("statistics.out");
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

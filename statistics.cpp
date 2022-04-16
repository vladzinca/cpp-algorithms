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

bool comparatorSpecial(string s1, string s2) {
        return s1.length() < s2.length();
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
    vector<float> maximalOccurence;

    void read_input() {
        for (int i = 0; i < 26; i++)
        {
            nrAparitii.push_back(0);
            maximalOccurence.push_back(0);
        }
        ifstream fin("statistics.in");
        fin >> n;
        string s;
        for (int i = 0; i < n; i++) {
            fin >> s;
            Word word(s, 0);
            v.push_back(word);
            vector<int> buffer;
            for (int j = 0; j < 26; j++)
            {
                buffer.push_back(0);
            }
            for (int j = 0; j < s.length(); j++) {
                int nrLiterei = s[j] - 97;
                buffer[nrLiterei]++;
                nrAparitii.at(nrLiterei)++;
            }
            for (int j = 0; j < 26; j++) {
                if ((float) buffer[j] / s.length() > maximalOccurence[j])
                    maximalOccurence[j] = (float) buffer[j] / s.length();
            }
        }
        for (int i = 0; i < 26; i++) {
            cout << (char)(i + 97) << " apare de " << nrAparitii[i] << "si are maximalOccurence " << maximalOccurence[i] << "\n";
        }
        cout << (char)(max_element(nrAparitii.begin(), nrAparitii.end()) - nrAparitii.begin() + 97) << "\n";
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
        int ourFinalResult = 0;
        for (int k = 0; k < 26; k++)
        {
            if (maximalOccurence[k] <= 0.5)
                continue;
            else {
                char searchedForLetter = (char)(k + 97);
                cout << "======================\nPentru litera " << (char) searchedForLetter << "\n=================\n";
                vector<string> specialWords;
                int specialWordCount = 0;
                for (int i = 0; i < n; i++) {
                    v[i].ourLetterOccurence = (float) countTheLetters(v[i].letters, searchedForLetter) / v[i].letters.length();
                    //aici am adaugat acel 1+ si 2+
                    if (v[i].ourLetterOccurence == 0) {
                        specialWords.push_back(v[i].letters);
                        specialWordCount++;
                    }
                }
                sort(v.begin(), v.end(), comparator);
                sort(specialWords.begin(), specialWords.end(), comparatorSpecial);
                // sa scoti ultimele elemente din v cand le pui in specialWords?
                // for (int i = 0; i < specialWordCount; i++)
                //     cout << specialWords[i] << "\n";
                int maxConcatCounter = 0, foundLetters = 0, totalLettersSearched = 0;
                foundLetters = countTheLetters(v[0].letters, searchedForLetter);
                totalLettersSearched = v[0].letters.length();
                float theOccurenceISeek = (float) foundLetters / totalLettersSearched;
                if (theOccurenceISeek <= 0.5)
                {
                    maxConcatCounter = -1;
                    continue;
                }
                else
                    maxConcatCounter++;
                int i = 1, j = 0;
                while (i < n - specialWordCount && j < specialWordCount) {
                    float potentialCoeff1 = (float) (foundLetters + countTheLetters(v[i].letters, searchedForLetter)) / (totalLettersSearched + v[i].letters.length());
                    // if (i == 24)
                    //     cout << foundLetters << " se imparte la " << totalLettersSearched << "\n";
                    float potentialCoeff2 = (float) foundLetters / (totalLettersSearched + specialWords[j].length());
                    if (potentialCoeff1 <= 0.5 && potentialCoeff2 <= 0.5)
                    {
                        cout << "dam skip pentru ca avem \n";
                        break;
                    }
                    else
                    {
                        if (potentialCoeff1 >= potentialCoeff2)
                        {
                            cout << v[i].letters << " si ourLetterOccurence este " << v[i].ourLetterOccurence << ", iar coeficientul obtinut este " << potentialCoeff1 << "\n";
                            maxConcatCounter++;
                            foundLetters += countTheLetters(v[i].letters, searchedForLetter);
                            totalLettersSearched += v[i].letters.length();
                            i++;
                            if (i == n - specialWordCount)
                            {
                                while (j < specialWordCount)
                                {
                                    float potentialCoeff = (float) foundLetters / (totalLettersSearched + specialWords[j].length());
                                    if (potentialCoeff <= 0.5)
                                    {
                                        cout << "dam skip pentru ca avem \n";
                                        break;
                                    }
                                    else
                                    {
                                        cout << specialWords[j] << " si ourLetterOccurence este, bineinteles, " << 0 << ", iar coeficientul obtinut este " << potentialCoeff << "\n";
                                        maxConcatCounter++;
                                        totalLettersSearched += specialWords[j].length();
                                        j++;
                                    }
                                }
                            }
                        }
                        else
                        {
                            cout << specialWords[j] << " si ourLetterOccurence este, bineinteles, " << 0 << ", iar coeficientul obtinut este " << potentialCoeff2 << "\n";
                            maxConcatCounter++;
                            totalLettersSearched += specialWords[j].length();
                            j++;
                            if (j == specialWordCount) // poate sa implementezi o d-asta si pentru cazul celalalt, dar nu ar trb sa fie nevoie
                            {
                                while (i < n - specialWordCount) {
                                    float potentialCoeff = (float) (foundLetters + countTheLetters(v[i].letters, searchedForLetter)) / (totalLettersSearched + v[i].letters.length());
                                    // if (i == 24)
                                    //     cout << foundLetters << " se imparte la " << totalLettersSearched << "\n";
                                    // float potentialCoeff2 = (float) foundLetters / (totalLettersSearched + specialWords[j].length());
                                    if (potentialCoeff <= 0.5)
                                    {
                                        cout << "dam skip pentru ca avem \n";
                                        break;
                                    }
                                    else
                                    {
                                        cout << v[i].letters << " si ourLetterOccurence este " << v[i].ourLetterOccurence << ", iar coeficientul obtinut este " << potentialCoeff << "\n";
                                        maxConcatCounter++;
                                        foundLetters += countTheLetters(v[i].letters, searchedForLetter);
                                        totalLettersSearched += v[i].letters.length();
                                        i++;
                                    }
                                }
                            }
                        }
                    }
                }
                cout << "Pentru litera " << searchedForLetter << " avem maxConcactCounter " << maxConcatCounter << "\n";
                if (maxConcatCounter > ourFinalResult)
                    ourFinalResult = maxConcatCounter;
            }
        }
        return ourFinalResult;
    }

    void print_output(int result) {
        ofstream fout("statistics.out");
        fout << result;
        cout << result;
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

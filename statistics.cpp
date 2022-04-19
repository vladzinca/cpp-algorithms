#include <bits/stdc++.h>
using namespace std;

/* structura in care se pastreaza cuvintele */
struct Word {
    string letters;
    float ourLetterOccurence;

    Word(string _letters, float _ourLetterOccurence)
        : letters(_letters)
        , ourLetterOccurence(_ourLetterOccurence) { }
};

/* compara cuvintele dupa incidenta unei litere
    in cuvant, si apoi dupa lungime */
bool comparator(Word w1, Word w2) {
    if (w1.ourLetterOccurence == w2.ourLetterOccurence)
        return w1.letters.length() < w2.letters.length();
    else
        return w1.ourLetterOccurence > w2.ourLetterOccurence;
}

/* compara cuvintele dupa lungime */
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

    /* citeste datele de intrare, calculeaza numarul
        total de aparitii in text si incidenta maxima
        a unei litere intr-un cuvant */
    void read_input() {
        for (int i = 0; i < 26; i++) {
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
                buffer.push_back(0);
            for (int j = 0; j < s.length(); j++) {
                int nrLiterei = s[j] - 97;
                buffer[nrLiterei]++;
                nrAparitii.at(nrLiterei)++;
            }
            for (int j = 0; j < 26; j++) {
                if ((float)buffer[j] / s.length() > maximalOccurence[j])
                    maximalOccurence[j] = (float)buffer[j] / s.length();
            }
        }
        fin.close();
    }

    /* calculeaza numarul de aparitii al unei litere intr-un cuvant */
    int countTheLetters(string s, char c) {
        int nr = 0;
        for (int i = 0; i < s.length(); i++)
            if (s[i] == c)
                nr++;
        return nr;
    }

    /* rezolva cerinta folosind impartind cuvintele
        in doi vectori si sortandu-i */
    int get_result() {
        int ourFinalResult = 0;
        /* verifica doar literele pentru care exista
            un cuvant cu incidenta dominanta */
        for (int k = 0; k < 26; k++)
            if (maximalOccurence[k] <= 0.5) {
                continue;
            } else {
                /* pentru toate cuvintele, calculeaza incidenta
                    literei in cuvant si o salveaza in structura */
                char searchedForLetter = (char)(k + 97);
                vector<string> specialWords;
                int specialWordCount = 0;
                for (int i = 0; i < n; i++) {
                    v[i].ourLetterOccurence =
                        (float)countTheLetters(v[i].letters, searchedForLetter)
                        / v[i].letters.length();
                    /* salveaza separat cuvintele pentru care
                        incidenta literei este 0 */
                    if (v[i].ourLetterOccurence == 0) {
                        specialWords.push_back(v[i].letters);
                        specialWordCount++;
                    }
                }
                /* sorteaza vectorul cu cuvinte in care apare litera dupa
                    acelei litere in cuvant, si vectorul cu cuvinte in care
                    nu apare litera dupa lungime */
                sort(v.begin(), v.end(), comparator);
                sort(specialWords.begin(), specialWords.end(),
                    comparatorSpecial);
                /* considera primul cuvant din vectorul sortat, iar daca nu
                    are incidenta dominanta, trece mai departe */
                int maxConcatCounter = 0, foundLetters = 0;
                int totalLettersSearched = 0;
                foundLetters = countTheLetters(v[0].letters,
                                                searchedForLetter);
                totalLettersSearched = v[0].letters.length();
                float theOccurenceISeek = (float)foundLetters
                                            / totalLettersSearched;
                if (theOccurenceISeek <= 0.5) {
                    maxConcatCounter = -1;
                    continue;
                } else {
                    maxConcatCounter++;
                }
                /* pentru toate celelalte cuvinte, verifica care ar fi
                incidenta daca s-ar concatena atat primul cuvand din vectorul
                v, cat si din vectorul specialWords, si concateneaza pe cel
                care ar duce la incidenta mai mare */
                int i = 1, j = 0;
                while (i < n - specialWordCount && j < specialWordCount) {
                    float potentialCoeff1 = (float)(foundLetters +
                            countTheLetters(v[i].letters, searchedForLetter))
                            / (totalLettersSearched + v[i].letters.length());
                    float potentialCoeff2 = (float)foundLetters
                        / (totalLettersSearched + specialWords[j].length());
                    if (potentialCoeff1 <= 0.5 && potentialCoeff2 <= 0.5) {
                        break;
                    } else {
                        if (potentialCoeff1 >= potentialCoeff2) {
                            /* concateneaza v[i] */
                            maxConcatCounter++;
                            foundLetters += countTheLetters
                                            (v[i].letters, searchedForLetter);
                            totalLettersSearched += v[i].letters.length();
                            i++;
                            /* daca vectorul v se termina, adauga doar cuvinte din
                                vectorul specialWords */
                            if (i == n - specialWordCount) {
                                while (j < specialWordCount) {
                                    float potentialCoeff = (float)foundLetters
                                                / (totalLettersSearched
                                                + specialWords[j].length());
                                    if (potentialCoeff <= 0.5) {
                                        break;
                                    } else {
                                        maxConcatCounter++;
                                        totalLettersSearched +=
                                                    specialWords[j].length();
                                        j++;
                                    }
                                }
                            }
                        } else {
                            /* concateneaza specialWords[j] */
                            maxConcatCounter++;
                            totalLettersSearched += specialWords[j].length();
                            j++;
                            /* daca vectorul specialWords se termina, adauga doar
                                cuvinte din vectorul v */
                            if (j == specialWordCount) {
                                while (i < n - specialWordCount) {
                                    float potentialCoeff = (float)(foundLetters
                                            + countTheLetters(v[i].letters,
                                                            searchedForLetter))
                                            / (totalLettersSearched +
                                                        v[i].letters.length());
                                    if (potentialCoeff <= 0.5) {
                                        break;
                                    } else {
                                        maxConcatCounter++;
                                        foundLetters += countTheLetters
                                            (v[i].letters, searchedForLetter);
                                        totalLettersSearched +=
                                                        v[i].letters.length();
                                        i++;
                                    }
                                }
                            }
                        }
                    }
                }
                /* daca pentru litera asta s-au gasit mai multe cuvinte ce pot
                    fi concatenate decat pentru literele anterioare, salveaza
                    acest rezultat */
                if (maxConcatCounter > ourFinalResult)
                    ourFinalResult = maxConcatCounter;
            }
        return ourFinalResult;
    }

    /* scrie rezultatul in fisier */
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

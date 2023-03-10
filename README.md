# C++ Algorithms

## 👾 What is this?

This repository contains two C++ algorithms that I wrote back in April 2022.

They are called *Walsh* and *Statistics* and aim to solve real-world problems with ingenious algorithms.

The solutions I provided for them show a good understanding of algorithms and programming techniques, such as divide-and-conquer and greedy, as well as an adequate ability of deciding which one to pick for solving concrete problems.

## 💻 How to run it?

1.  Clone this repository.
2.  Run automatic tests found in `public_tests/` using `./check` (I did not write the checker myself).
3.  Enjoy!

## 🤓 What do they do exactly?

### 🟧 Walsh

The code for this is found in `walsh.cpp`.

What it does is, for `K` pairs of `(x, y)`, it computes what the element found on row `x` and column `y` will be in a [Walsh matrix](https://en.wikipedia.org/wiki/Walsh_matrix) of 0's and 1's.

A Walsh matrix is generated on the following rule:

![image](https://user-images.githubusercontent.com/74200913/224330062-46938a96-4715-4811-b768-83fdab76c0c5.png)

And these are some examples of Walsh matrices:

![image](https://user-images.githubusercontent.com/74200913/224330140-57e90f66-6dce-4e82-9e83-773034fb3331.png)

The program reads from an input file called `walsh.in`:

```
N K
x1 y1
...
xK yK
```

And prints `K` results of `0` or `1` to a file called `walsh.out`.

#### Example
##### Input:
```
4 5
1 3
4 2
3 3
1 2
2 1
```
##### Output:
```
0
1
1
0
0
```

The way it works is, in my opinion, pretty ingenious.

Instead of computing the whole walsh matrix, it uses a [Divide-and-conquer](https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm) approach, in that it determines in which quarter our element is, it negates it if it's the bottom-right one, and then does the same thing inside that quarter, until it reaches a 2x2 walsh matrix, in which case the solution is known.

The complexity for this problem is, then, `O(K * log(4, N))`, the 4 there coming from the fact that at every step of the recursivity, our problem gets 4 times smaller (we split the Walsh matrix in 4 quarters).

### 📈 Statistics

The code for this is found in `statistics.cpp`.

This program takes a list of `N` strings of lower-case letters and determines the maximum amount of strings that, if concatenated, would have a dominant letter.

By dominant letter, we mean one that has **more** than half appearences than the total amount of letters in the string.

The program reads from an input file called `statistics.in`:

```
N
string1
string2
...
stringN
```

And prints to `statistics.out` the maximum number of string that, if concatenated, would have a dominant letter.

#### Example
##### Input:
```
4
abbc
cbb
aa
ab
```
##### Output:
```
3
```
##### Explanation:
```
The strings abbc, cbb and ab, concatenated, would have b as a dominant letter,
since b appears 5 times and the total length of the concatenated string is 9.
```

The way I tried to solve this was by using a [Greedy](https://en.wikipedia.org/wiki/Greedy_algorithm) approach and attempting to sort strings by the incidence of the most prominent letter in the string and picking out the first strings such that the number of concatenated strings is as large as possible.

This approach improved greatly when I decided to calculate the number of strings concatenated for **every** letter, and pick out the letter with the largest string count, as well as when I decided to split the strings in two arrays, an array called `v` for the strings in which the letter appears at least once`, and another array `specialWords` where the letter does not appear at all, sort them both and then compare whether it would be beneficial to concatenate a string from the `v` array or from the `specialWords` array.

However, some extensive tests do not yield the correct output, and the little time I had was not enough for checking them by hand or building a tool to help me understand why.

Time complexity for this one is `O(max(N, L) * log(N))`, where `L` is the sum of the lengths of all given strings, because of the two sorting algorithms performed in `O(N * log(N))` time.

## 🎓 What did I learn?

Firstly, as I said earlier, programming techniques. By working on these algorithms, I familiarized myself greatly with divide-and-conquer, greedy, dynamic programming and other types of algorithms, and with choosing which one would be best suited for concrete problems one can come across as a software engineer.

Secondly, the fact that the data available for testing can be huge and hard to follow by hand made me employ creative techniques of debugging, and even though I did not solve the last problem for every possible case, I greatly improved the program's viability.

What is more, not finishing *Statistics* completely helped me improve my time management skills, and now I manage my time and development windows much better.

## 🤔 Did you know?

I learned this thing just a few days ago, so hear me out.

Divide-and-conquer and recursive programs are generally bad for embedded systems, because they add a lot of variables to the [stack](https://en.wikipedia.org/wiki/Stack-based_memory_allocation) at every recursive call and if the stack is not large enough, and for many embedded systems it isn't, this might literally lead to a stack overflow (and also lead to Stack Overflow in search of a solution). 🥁

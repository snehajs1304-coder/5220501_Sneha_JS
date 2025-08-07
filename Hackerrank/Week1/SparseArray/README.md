 Problem: Sparse Arrays
There is a collection of input strings and a collection of query strings.
For each query string, determine how many times it occurs in the list of input strings.
Return an array of the results.

 Example:

stringList = ['ab', 'ab', 'abc']
queries = ['ab', 'abc', 'bc']
There are:

2 instances of 'ab'

1 of 'abc'

0 of 'bc'

Output:
[2, 1, 0]

Function Description
Complete the function matchingStrings with the following parameters:

Parameters:
string stringList[n]: an array of strings to search

string queries[q]: an array of query strings

Returns:
int[q]: the results of each query

Input Format
The first line contains an integer n, the size of stringList[].

Each of the next n lines contains a string stringList[i].

The next line contains an integer q, the size of queries[].

Each of the next q lines contains a string queries[i].

Constraints
1 ≤ n ≤ 1000

1 ≤ q ≤ 1000

1 ≤ |stringList[i]|, |queries[i]| ≤ 20

Sample Input 1

4
aba
baba
aba
xzxb
3
aba
xzxb
ab

Explanation:
"aba" appears 2 times in stringList.

"xzxb" appears 1 time.

"ab" appears 0 times.

Sample Output 1
2
1
0
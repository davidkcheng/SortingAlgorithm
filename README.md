# SortingAlgorithm
Problem Description
You are asked to apply the Insertion Sort, Merge Sort, Heap Sort, Quicksort, and Bubble Sort (see page 40 of the textbook) to develop five word processors in the C or C++ programming language. Given is an article with words and numbers.
Input
The input consists of a sequence of words, numbers, and symbols, separated by blanks, punctuation marks, and/or line breakers (end of line).
Output
The first line of output contains a number indicating the total number of words, followed by a list of words. Please note that the word processors sort the words (i.e., ignore others, such as the numbers, symbols and blanks) in the order of their occurrences (from the largest to the smallest) and alphabetic order (from ‘a’ to ‘z’).
※For this problem, we consider that words are case sensitive, and a compound word or an abbreviation should be treated as a single word; for example, “on-chip” or “it’s” should be treated as a word ( without quotes ).
In addition, behind each word you should output its occurrences and a list of the positions (row order) they appear in the article as shown in the following table. For example, the occurrence of IC is 1 and it is the 3rd word of the line 2. Note that you don’t have to sort the list of the appearing-order numbers for each word so that we can see if the sorter is stable.

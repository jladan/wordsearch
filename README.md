# wordsearch
Markov chain generated wordsearches

A simple markov-chain program to create a wordsearch grid, which I wrote to learn/practice C++14. The problem is solved in two parts.

1. `markov-maker.cpp` loads a sample text, and generates Markov matrices (0th, 1st, and 2nd order).
2. `wordsearch.cpp` creates the wordsearch using the above matrices.

## Method

The wordsearch is generated using a 2nd order Markov-chain. That is, the probability of the next letter is determined by the previous letter.
Of course, the text used to generate the probability matrix is 1D (a stream of characters), but a wordsearch is 2D. My algorithm to determine each letter is simple:

1. Use the probability matrix to choose a next letter from:
 a. the 2 letters above; and
 b. the 2 letters to the left.
2. Check the probability of each option happening, given the two previous letters.
3. Choose the most likely letter (the one with the higher probability).

This leads to wordsearches that favour vertical and horizontal words, with much lower probability of diagonals.

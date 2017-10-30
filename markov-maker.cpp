/* Markov Chain wordsearch
 */

#include <vector>
#include <random>
#include <iostream>
#include <fstream>

#include "matrix.h"
#include "matrix.cpp"

using namespace std;


int main(int argc, char* argv[]) {

    vector<double> mark0(26,0);
    Matrix<double> mark1(26,26,0);
    Matrix<double> mark2(26,26*26,0);
    char x[3];

    // find first character as starting point
    while (cin >> x[2]) {
        if (isalpha(x[2])) {
            x[2] = toupper(x[2])-65;
            break;
        }
    }
    
    // and the second
    while (cin >> x[1]) {
        if (isalpha(x[1])) {
            x[1] = toupper(x[1])-65;
            break;
        }
    }

    // Now populate the markov matrix
    while ( cin >> x[0] ) {
        if ( isalpha(x[0]) ) {
            x[0] = toupper(x[0])-65;

            mark0[x[0]]++;
            mark1(x[0],x[1])++;
            mark2(x[0], x[1]+x[2]*26)++;
            x[2] = x[1];
            x[1] = x[0];
        }
    }

    // turn them into probability distributions
    double total = 0;
    for ( auto a : mark0)
        total += a;
    for ( auto &a : mark0)
        a = a/total;

    for (size_t j=0; j<26; j++) {
        total = 0;
        for (size_t i=0; i<26; i++)
            total += mark1(i,j);
        if (total > 0.5) 
        for (size_t i=0; i<26; i++)
            mark1(i,j) = mark1(i,j)/total;
    }
    for (size_t j=0; j<26*26; j++) {
        total = 0;
        for (size_t i=0; i<26; i++)
            total += mark2(i,j);
        if (total > 0.5) 
        for (size_t i=0; i<26; i++)
            mark2(i,j) = mark2(i,j)/total;
    }

    // Write them to file
    ofstream fout;
    fout.precision(15);

    fout.open("mark0.dat");
    fout << 26 <<" " << 1<< endl;
    for (size_t k=0; k<26; k++)
        fout << mark0[k] << "\t";
    fout << endl;
    fout.close();

    fout.open("mark1.dat");
    fout << 26 << " " <<26<< endl;
    for (size_t j=0; j<26; j++) {
        for (size_t i=0; i<26; i++)
            fout << mark1(i,j) << "\t";
        fout << endl;
    }
    fout.close();
    
    fout.open("mark2.dat");
    fout << 26 << " " <<26*26<< endl;
    for (size_t j=0; j<26*26; j++) {
        for (size_t i=0; i<26; i++)
            fout << mark2(i,j) << "\t";
        fout << endl;
    }
    fout.close();
    

}


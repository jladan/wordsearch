/* Markov Chain wordsearch
 */

#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "matrix.cpp"

using namespace std;

const size_t width  = 40;
const size_t height = 30;

size_t get_next(size_t prev, Matrix<double> mark) ;
Matrix<double> load_matrix(string filename) ;
void cumsum(vector<double> &v) ;


int main() {
  Matrix<double> mark = load_matrix("markov.dat");

  Matrix<char> wordgrid(height,width,0);

  for (size_t i=1; i<height; i++) {
      wordgrid(i,0) = get_next(wordgrid(i-1,0), mark);
  }
  for (size_t i=1; i<width; i++) {
      wordgrid(0,i) = get_next(wordgrid(0,i-1), mark);
  }

  for (size_t i=1; i<height; i++) {
      for (size_t j=1; j<width; j++) {
          char try1 = get_next(wordgrid(i-1,j), mark);
          char try2 = get_next(wordgrid(i,j-1), mark);
          if (mark(try1, wordgrid(i-1,j)) > mark(try2, wordgrid(i,j-1)))
              wordgrid(i,j) = try1;
          else
              wordgrid(i,j) = try2;
      }
  }

  for (size_t i=0; i<height; i++) {
      for (size_t j=0; j<width; j++)
          cout << (char)(wordgrid(i,j)+'A') << " ";
      cout << endl;
  }

}

size_t get_next(size_t prev, Matrix<double> mark) {
    static std::random_device rd;
    static std::mt19937 mt(rd()); 
    static std::uniform_real_distribution<double> dist(0, 1);

    vector<double> rates = mark.col(prev);
    
    cumsum(rates);
    double r = dist(mt);
    
    return distance(rates.cbegin(), lower_bound(rates.cbegin(), rates.cend(), r));
}

Matrix<double> load_matrix(string filename) {
    ifstream myfile;
    myfile.open(filename);

    Matrix<double> mark(26,26,0);

    for (size_t j=0; j<26; j++)
        for (size_t i=0; i<26; i++)
            myfile >> mark(i,j) ;

    return mark;
}
    

void cumsum(vector<double> &v) {
    for(auto it=v.begin()+1; it!=v.end(); ++it)
        *it += *(it-1);
}


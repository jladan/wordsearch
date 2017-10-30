/* Markov Chain wordsearch
 */

#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "matrix.cpp"

using namespace std;

const size_t width  = 50;
const size_t height = 50;

size_t get_next(vector<double> mark) ;
size_t get_next(Matrix<double>, size_t prev) ;
size_t get_next(Matrix<double>, size_t prev1, size_t prev2) ;

double get_prob(Matrix<double> mark, size_t target, size_t state);
double get_prob(Matrix<double> mark, size_t target, size_t state1, size_t state2);

Matrix<double> load_matrix(string filename) ;
void cumsum(vector<double> &v) ;

random_device rd;
mt19937 mt(rd()); 
uniform_real_distribution<double> dist(0, 1);


int main() {
  Matrix<double> mark0 = load_matrix("mark0.dat");
  Matrix<double> mark1 = load_matrix("mark1.dat");
  Matrix<double> mark2 = load_matrix("mark2.dat");

  Matrix<char> wordgrid(height,width, 0);

  // Starting character
  wordgrid(0,0) = get_next(mark0.col(0));

  // First row and column
  for (size_t i=1; i<height; i++) {
      wordgrid(i,0) = get_next(mark1, wordgrid(i-1,0));
  }
  for (size_t i=1; i<width; i++) {
      wordgrid(0,i) = get_next(mark1, wordgrid(0,i-1));
  }

  // Second row and column
  for (size_t i=1; i<height; i++) {
      char a1 = wordgrid(i-1,1);
      char b1 = wordgrid(i,0);
      char try1 = get_next(mark1, a1);
      char try2 = get_next(mark1, b1);
      if (get_prob(mark1, try1, a1) > get_prob(mark1, try2, b1))
          wordgrid(i,1) = try1;
      else
          wordgrid(i,1) = try2;
  }
  for (size_t i=1; i<height; i++) {
      char a1 = wordgrid(1,i-1);
      char b1 = wordgrid(0,i);
      char try1 = get_next(mark1, a1);
      char try2 = get_next(mark1, b1);
      if (get_prob(mark1, try1, a1) > get_prob(mark1, try2, b1))
          wordgrid(1,i) = try1;
      else
          wordgrid(1,i) = try2;
  }
  
  // The rest
  for (size_t i=2; i<height; i++) {
      for (size_t j=2; j<width; j++) {
          char a1 = wordgrid(i-1,j);
          char a2 = wordgrid(i-2,j);
          char b1 = wordgrid(i,j-1);
          char b2 = wordgrid(i,j-2);
          char try1 = get_next(mark2, a1, a2);
          char try2 = get_next(mark2, b1, b2);
          if (get_prob(mark2, try1, a1, a2) > get_prob(mark2, try2, b1, b2))
              wordgrid(i,j) = try1;
          else
              wordgrid(i,j) = try2;
      }
  }

  cout << "Content-type:text/text\r\n\r\n";
  for (size_t i=0; i<height; i++) {
      for (size_t j=0; j<width; j++)
          cout << (char)(wordgrid(i,j)+'A') << " ";
      cout << endl;
  }

}

size_t get_next(const vector<double> rates) {
    vector<double> tmp = rates;
    cumsum(tmp);
    double r = dist(mt);
    
    return distance(tmp.cbegin(), lower_bound(tmp.cbegin(), tmp.cend(), r));
}

size_t get_next(Matrix<double> mark, size_t prev) {
    return get_next(mark.col(prev));
}

size_t get_next(Matrix<double> mark, size_t prev1, size_t prev2) {
    return get_next(mark.col(prev1 + 26*prev2));
}

double get_prob(Matrix<double> mark, size_t target, size_t state) {
    return mark(target, state);
}

double get_prob(Matrix<double> mark, size_t target, size_t state1, size_t state2) {
    return mark(target, state1 + state2*26);
}

Matrix<double> load_matrix(string filename) {
    ifstream fin;
    fin.open(filename);

    size_t r,c;
    fin >> r >> c;

    Matrix<double> mark(r,c,0);

    for (size_t j=0; j<c; j++)
        for (size_t i=0; i<r; i++)
            fin >> mark(i,j) ;

    return mark;
}
    

void cumsum(vector<double> &v) {
    for(auto it=v.begin()+1; it!=v.end(); ++it)
        *it += *(it-1);
}


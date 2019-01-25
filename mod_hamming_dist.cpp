#include <Rcpp.h>
using namespace Rcpp;

// Modified hamming distance, allows different length strings
// but additional characters in one string over the other
// are counted as differences

// [[Rcpp::export]]
NumericVector mod_hamming_dist(CharacterVector a, CharacterVector b) {
  int size_a = a.size();
  int i;
  
  NumericVector ret_vect(size_a);
  
  for(i = 0; i < size_a; i++) {
    std::string a_str;
    a_str = a[i];
    std::string b_str;
    b_str = b[i];
    
    if(a_str.length() == 0 || b_str.length() == 0) {
      ret_vect[i] = 1.0;
    } else {
      int len_min = std::min(a_str.length(), b_str.length());
      int len_max = std::max(a_str.length(), b_str.length());
      int j, dist = len_max - len_min;
      
      for(j = 0; j < len_min; j++) {
        dist += a_str[j] != b_str[j];
      }
      ret_vect[i] = 1.0 * dist / len_max;
    }
  }
  
  return ret_vect;
}



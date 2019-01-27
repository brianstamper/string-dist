#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]

DataFrame cross_join(std::vector< std::string > col_a, std::vector< std::string > col_b) {
  int a_size = col_a.size();
  int b_size = col_b.size();
  int i, j, r;
  
  std::vector< std::string > out_a(a_size * b_size);
  std::vector< std::string > out_b(a_size * b_size);
  
  for(i = 0, r = 0; i < a_size; i++) {
    for(j = 0; j < b_size; j++, r++) {
      out_a[r] = col_a[i];
      out_b[r] = col_b[j];
    }
  }
  
  return DataFrame::create(_["a"] = out_a,
                           _["b"] = out_b,
                           _["stringsAsFactors"] = false );
}


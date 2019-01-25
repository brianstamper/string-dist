#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
DataFrame cross_join(NumericVector a, NumericVector b) {
    int size_a = a.size(),
        size_b = b.size();
    int i, j, r;

    NumericMatrix ret_mat(size_a * size_b, 2);

    for(i = 0, r = 0; i < size_a; i++) {
        for(j = 0; j < size_b; j++, r++) {
            ret_mat(r, 0) = a(i);
            ret_mat(r, 1) = b(j);
        }
    }
    colnames(ret_mat) = CharacterVector::create("set_a_row", "set_b_row");

    return ret_mat;
}


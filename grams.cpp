#include <Rcpp.h>
using namespace Rcpp;
// Enable C++11 via this plugin (Rcpp 0.10.3 or later)
// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]

NumericVector grams(DataFrame a) {
  int nrow_a = a.nrows();
  int i;
  std::vector< std::string > col_a = a[0];
  std::vector< std::string > col_b = a[1];
  
  // return vector
  //std::vector<float> li (nrow_a);
  NumericVector li(nrow_a);
  
  // token function takes a string and breaks it down into many 
  // substring tokens based on a set of patterns
  auto token = [&](std::string s) {
    int j;
    // init the return vector
    std::vector< std::string > ret_vec;
    
    // prepend ^ and append $ to give special weight to the
    // beginnings and ends of strings
    std::string t = "^";
    t.append(s);
    t.append("$");
    
    // Begin adding to the vector of substrings
    // First we push back a whole copy of the string to give
    // a bonus for full string match, and to make sure non-empty.
    ret_vec.push_back(t);
    
    // Need to use length of string in many safety checks
    int sl = s.length();
    
    // syntax for commenting the patterns is . = include, - = skip
    for(j = 0; j < sl; j++) {
      
      // length one, single characters  .  E
      ret_vec.push_back(t.substr(j, 1));

      // length two, 2-grams ..  I
      if(j < sl - 2) {
        ret_vec.push_back(t.substr(j, 2));
      }

      // length three
      if(j < sl - 3) {
        // 3-grams  ...  S
        ret_vec.push_back(t.substr(j, 3));
        // 1-skips  .-.  R
        std::string k = t.substr(j, 1);
        k.append(t.substr(j + 2, 1));
      }

      // length four
      if(j < sl - 4) {
        // 4-grams  ....  H
        ret_vec.push_back(t.substr(j, 4));
        // 1-skip left  .-..  L
        std::string k1 = t.substr(j, 1);
        k1.append(t.substr(j + 2, 2));
        ret_vec.push_back(k1);
        // 1-skip right  ..-.  F
        std::string k2 = t.substr(j, 2);
        k2.append(t.substr(j + 3, 1));
        ret_vec.push_back(k2);
        // 2-skip .--.  P
        std::string k3 = t.substr(j, 1);
        k3.append(t.substr(j + 3, 1));
        ret_vec.push_back(k3);
      }
    }
    
    return (ret_vec); 
  };
  
  for(i = 0; i < nrow_a; i++) {
    // get the individual strings from col_a and col_b
    // pass each to token()
    // count the set union of the results
    // come up with some formula for the size of the two token lists
    //   and the union of the two, this will be our measure of similarity
    
    // code adopted from https://en.cppreference.com/w/cpp/algorithm/set_intersection
    std::vector<std::string> v1 = token(col_a[i]);
    std::vector<std::string> v2 = token(col_b[i]);
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    
    std::vector<std::string> v_intersection;
    
    std::set_intersection(v1.begin(), v1.end(),
                          v2.begin(), v2.end(),
                          std::back_inserter(v_intersection));
    
    li[i] = 1.0f - v_intersection.size() / (1.0f * std::max(v1.size(), v2.size()));
  }
  
  return li;
}


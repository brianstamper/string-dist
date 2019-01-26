#include <Rcpp.h>
using namespace Rcpp;
// Enable C++11 via this plugin (Rcpp 0.10.3 or later)
// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]

DataFrame grams(DataFrame a) {
  int nrow_a = a.nrows();
  int i, r;
  std::vector< std::string > col_a = a[0];
  std::vector< std::string > col_b = a[1];
  
  // TODO old return type here, needs replaced
  std::list< std::vector<std::string> > li;
  
  // token function takes a string and breaks it down into many 
  // substring tokens based on a set of patterns
  auto token = [&](std::string s) {
    
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
    for(i = 0; i < sl; i++) {
      
      // length one, single characters  .  E
      ret_vec.push_back(t.substr(i, 1));
      
      // length two, 2-grams ..  I
      if(i < sl - 1) {
        ret_vec.push_back(t.substr(i, 2));
      }
      
      // length three      
      if(i < sl - 2) {
        // 3-grams  ...  S
        ret_vec.push_back(t.substr(i, 3));
        // 1-skips  .-.  R
        std::string k = t.substr(i, 1);
        k.append(t.substr(i + 2, 1));
      }
      
      // length four
      if(i < sl - 3) {
        // 4-grams  ....  H
        ret_vec.push_back(t.substr(i, 4));
        // 1-skip left  .-..  L  
        std::string k1 = t.substr(i, 1);
        k1.append(t.substr(i + 2, 2));
        ret_vec.push_back(k1);
        // 1-skip right  ..-.  F  
        std::string k2 = t.substr(i, 2);
        k2.append(t.substr(i + 3, 1));
        ret_vec.push_back(k2);
        // 2-skip .--.  P
        std::string k3 = t.substr(i, 1);
        k3.append(t.substr(i + 3, 1));
        ret_vec.push_back(k3);
      }
    }
    
    return (ret_vec); 
  };
  
  for(i = 0, r = 0; i < nrow_a; i++) {
    // get the individual strings from col_a and col_b
    // pass each to token()
    // count the set union of the results
    // come up with some formula for the size of the two token lists
    //   and the union of the two, this will be our measure of similarity
    
    // old code here..
    li.push_back({"test1", "test2", "test3"});
  }

  // TODO check type correctness of wrap() on our output object
  return wrap(li);
}


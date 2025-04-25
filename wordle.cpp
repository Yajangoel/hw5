#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
static void wordleHelper(string& cur, const string& pattern, string& floating, size_t idx, const set<string>& dict, set<string>& results){
  const size_t N = pattern.size();
  if(idx == N){
    if(floating.empty() && dict.find(cur) != dict.end()){
      results.insert(cur);
      return;
    }
    return;
  }
  if(pattern[idx] != '-'){
    cur[idx] = pattern[idx];
    wordleHelper(cur, pattern, floating, idx+1, dict, results);
    cur[idx] = '-';
    return;
  }
  int blanksLeft = 0;
  for(size_t j = idx; j < N; j++){
    if(pattern[j] == '-'){
      blanksLeft++;
    }
  }
  for(char c = 'a'; c <= 'z'; ++c){
    bool Flagfloating = false;
    size_t pos = floating.find(c);
    if(pos != string::npos){
      floating.erase(pos, 1);
      Flagfloating = true;
    }
    else{
      if(blanksLeft - 1 < static_cast<int>(floating.size())){
        continue;
      }
    }
      cur[idx] = c;
      wordleHelper(cur, pattern, floating, idx+1, dict, results);
      cur[idx] = '-';
      if(Flagfloating){
        floating.push_back(c);
      }
  }
  
}



// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    string cur = in;
    string floatcopy = floating;
    wordleHelper(cur, in, floatcopy, 0, dict, results);
    return results;

}

// Define any helper functions here

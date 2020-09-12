#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

bool simple_match(const string &txt, const string &pat, int offset) {
  for (int i = 0; i < pat.length(); ++i) {
    if (pat[i] != txt[offset + i]) {
      return false;
    }
  }
  return true;
}

// returns index of match or -1 for no match found
// txt is a long text that we are trying to find a pattern in
// pat is a short text
// d is the number of characters in our alphabet
// q is a prime number that we will do all calculations modulo q
int rabin_karp_matcher(const string &txt, const string &pat, int d = 256,
                       int q = 13) {
  int n = txt.length();
  int m = pat.length();
  if (m > n) {
    return -1;
  }
  // value of a character at the highest unit for pattern pow(ALLCHARS, m - 1)
  int unitValue = 1;
  for (int i = 0; i < m - 1; ++i) {
    unitValue = (unitValue * d) % q;
  }
  int tHash = 0;
  int pHash = 0;
  // preprocessing hash for pattern and first window
  for (int i = 0; i < m; ++i) {
    tHash = (d * tHash + txt[i]) % q;
    pHash = (d * pHash + pat[i]) % q;
  }
  for (int s = 0; s <= n - m; ++s) {
    if (pHash == tHash && simple_match(txt, pat, s)) {
      return s;
    }
    // recalculate new window, remove txt[s] add txt[s+m]
    if (s < n - m) {
      tHash = tHash - txt[s] * unitValue;
      tHash = (d * tHash + txt[s + m]) % q;
      // if hash is negative, add MODULONUM to make it positive
      if (tHash < 0) {
        tHash += q;
      }
    }
  }
  return -1;
}

int main() {
  string text = "abcbcab";
  string pattern = "ab";
  int result = rabin_karp_matcher(text, pattern);
  assert(result == 0);

  pattern = "bc";
  result = rabin_karp_matcher(text, pattern);
  assert(result == 1);

  pattern = "cab";
  result = rabin_karp_matcher(text, pattern);
  assert(result == 4);

  pattern = "aa";
  result = rabin_karp_matcher(text, pattern);
  assert(result == -1);

  cout << "Done." << endl;
  return 0;
}
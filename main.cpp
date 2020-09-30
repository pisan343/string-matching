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

int brute_force_matcher(const string &txt, const string &pat) {
  for (int offset = 0; offset <= txt.length() - pat.length(); offset++) {
    if (simple_match(txt, pat, offset))
      return offset;
  }
  return -1;
}

int simple_sum_matcher(const string &txt, const string &pat) {
  if (pat.length() > txt.length())
    return -1;
  int patsum = 0;
  int txtsum = 0;
  for (int i = 0; i < pat.length(); i++) {
    patsum += pat[i];
    txtsum += txt[i];
  }

  for (int offset = 0; offset <= txt.length() - pat.length(); offset++) {
    if (patsum == txtsum && simple_match(txt, pat, offset))
      return offset;
    if (offset + pat.length() + 1 < txt.length()) {
      txtsum -= txt[offset];
      txtsum += txt[offset + pat.length()];
    }
  }
  return -1;
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
  int r1 = rabin_karp_matcher(text, pattern);
  int r2 = simple_sum_matcher(text, pattern);
  int r3 = brute_force_matcher(text, pattern);
  assert(r1 == 0 && r2 == 0 && r3 == 0);

  pattern = "bc";
  r1 = rabin_karp_matcher(text, pattern);
  r2 = simple_sum_matcher(text, pattern);
  r3 = brute_force_matcher(text, pattern);
  assert(r1 == 1 && r2 == 1 && r3 == 1);

  pattern = "cab";
  r1 = rabin_karp_matcher(text, pattern);
  r2 = simple_sum_matcher(text, pattern);
  r3 = brute_force_matcher(text, pattern);
  assert(r1 == 4 && r2 == 4 && r3 == 4);

  pattern = "aa";
  r1 = rabin_karp_matcher(text, pattern);
  r2 = simple_sum_matcher(text, pattern);
  r3 = brute_force_matcher(text, pattern);
  assert(r1 == -1 && r2 == -1 && r3 == -1);

  cout << "Done." << endl;
  return 0;
}
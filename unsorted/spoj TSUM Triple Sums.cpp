#include <iostream>
#include <vector>
using namespace std;

typedef long long int lli;

lli powMod(lli n, lli p, lli m) {
  lli result = 1;
  for (lli i=0, nPow=n; 1<<i <= p; ++i, nPow = (nPow*nPow)%m)
    if (p & (1<<i))
      result = (result*nPow)%m;
  return result;
}

// invMod(a, b)*a + invMod(b, a)*b == 1
// WARNING: may be negative (but it's between -b and b)
// Also may use temporary values up to a*b
lli invMod(lli a, lli b) {
  if (a<=1)
    return a;
  return (1-invMod(b%a, a)*b)/a;
}

// requirements: v.size() is a power of 2, that divides mod-1, mod is a prime, pRoot is a primitive root
lli NTTMod[] = {(15<<27)+1, (27<<26)+1, (7<<26)+1};
lli NTTRoot[] = {31, 13, 3};
void NTT(vector<lli>& v, lli mod, lli pRoot) {
  lli w = powMod(pRoot, (mod-1)/v.size(), mod);
  vector<int> rev(v.size());
  for (int i=0; 1<<i < v.size(); ++i)
    for (int j=0; j < 1<<i; ++j) {
      rev[j] <<= 1;
      rev[j + (1<<i)] = rev[j]+1;
    }
  for (int i=0; i<v.size(); ++i)
    if (i < rev[i])
      swap(v[i], v[rev[i]]);
  for (lli& i : v)
    i = ((i%mod)+mod)%mod;
  vector<lli> powRoot(v.size());
  powRoot[0] = 1;
  for (int i=0; i+1 < v.size(); ++i)
    powRoot[i+1] = (powRoot[i]*w)%mod;
  for (int l=0; 1<<l < v.size(); ++l) {
    int pd = v.size()>>(l+1);
    for (int i=0; i < v.size(); i += 2<<l)
      for (int j=0, p=0; j < 1<<l; ++j, p+=pd) {
        int j2 = i + j + (1<<l);
        lli b = v[i+j], d = (v[j2]*powRoot[p])%mod;
        v[i+j] = (b+d)%mod;
        v[j2] = (b-d)%mod;
      }
  }
}

vector<lli> func(const vector<lli>& s, const vector<lli>& s2) {
  lli n = s.size()+s2.size()-1;
  while (n&(n-1))
    n += n&-n;
  vector<lli> result(n, 0);
  lli mod = 1;
  for (int mIndex=0; mIndex<2; ++mIndex) {
    lli m = NTTMod[mIndex];
    vector<lli> sFFT=s, s2FFT=s2;
    sFFT.resize(n, 0); s2FFT.resize(n, 0);
    NTT(sFFT, m, NTTRoot[mIndex]);
    NTT(s2FFT, m, NTTRoot[mIndex]);
    for (int i=0; i<n; ++i) {
      s2FFT[i] = (sFFT[i]*s2FFT[i])%m;
      sFFT[i] = (((sFFT[i]*sFFT[i])%m)*sFFT[i])%m;
    }
    NTT(sFFT, m, invMod(NTTRoot[mIndex], m));
    NTT(s2FFT, m, invMod(NTTRoot[mIndex], m));
    // result[i] = crt(result[i], mod, invMod(n, m)*aFFT[i], m)
    // WARNING: assumes that result[i] does not overflow.
    // If that's not a guarantee, take more care when performing CRT
    lli inv = invMod((n*(mod%m))%m, m);
    for (int i=0; i<n; ++i) {
      lli d = ((((sFFT[i]-3*s2FFT[i]-n*(result[i]%m))%m)*inv)%m+m)%m;
      result[i] += (d > m/2 ? mod*(d-m) : mod*d);  // just result[i] += mod*d if result cannot be negative
    }
    if (mIndex < 3)
      mod *= m;
      // now result is correct % mod, stop the loop if that's enough
  }
  result.resize(s.size()+s2.size()-1);
  return result;
}

const int MAX = 20000;

int main() {
  int n;
  cin >> n;
  vector<lli> s(2*MAX+1, 0), s2(4*MAX+1, 0), s3(6*MAX+1, 0);
  for (int i=0; i<n; ++i) {
    int x;
    cin >> x;
    s[x+MAX]++;
    s2[2*x+2*MAX]++;
    s3[3*x+3*MAX]++;
  }
  vector<lli> res = func(s, s2);
  for (int i=0; i<6*MAX+1; ++i)
    res[i] = (res[i]+2*s3[i])/6;
  for (int i=0; i<6*MAX+1; ++i)
    if (res[i] > 0)
      cout << i-3*MAX << " : " << res[i] << endl;
}
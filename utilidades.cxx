#include "utilidades.h"
#include <cctype>

// trim sin size_t ni npos: indices int y for manuales
string trim(const string& s) {
    if (s.empty()) return "";
    int i = 0;
    int j = (int)s.size() - 1;

    while (i <= j) {
        char c = s[i];
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') i++;
        else break;
    }
    while (j >= i) {
        char c = s[j];
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') j--;
        else break;
    }
    if (i > j) return "";
    return s.substr(i, j - i + 1);
}

string firstToken(const string& s) {
    if (s.empty()) return "";
    int n = (int)s.size();
    int i = 0;

    while (i < n && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r')) i++;
    if (i >= n) return "";

    int j = i;
    while (j < n && !(s[j] == ' ' || s[j] == '\t' || s[j] == '\n' || s[j] == '\r')) j++;

    return s.substr(i, j - i);
}

string restAfterFirst(const string& s) {
    if (s.empty()) return "";
    int n = (int)s.size();
    int i = 0;

    while (i < n && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r')) i++;
    if (i >= n) return "";

    int j = i;
    while (j < n && !(s[j] == ' ' || s[j] == '\t' || s[j] == '\n' || s[j] == '\r')) j++;

    int k = j;
    while (k < n && (s[k] == ' ' || s[k] == '\t' || s[k] == '\n' || s[k] == '\r')) k++;

    if (k >= n) return "";

    int t = n - 1;
    while (t >= k && (s[t] == ' ' || s[t] == '\t' || s[t] == '\n' || s[t] == '\r')) t--;

    if (k > t) return "";
    return s.substr(k, t - k + 1);
}

int countWords(const string& s) {
    int n = (int)s.size();
    bool dentro = false;
    int c = 0;
    for (int i = 0; i < n; ++i) {
        char ch = s[i];
        bool esBlanco = (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
        if (esBlanco) {
            dentro = false;
        } else if (!dentro) {
            dentro = true;
            ++c;
        }
    }
    return c;
}

bool startsWith(const string& s, const string& prefijo) {
    int ns = (int)s.size();
    int np = (int)prefijo.size();
    if (np > ns) return false;
    for (int i = 0; i < np; ++i) {
        if (s[i] != prefijo[i]) return false;
    }
    return true;
}

bool endsWith(const string& s, const string& sufijo) {
    int ns = (int)s.size();
    int nf = (int)sufijo.size();
    if (nf > ns) return false;
    int offset = ns - nf;
    for (int i = 0; i < nf; ++i) {
        if (s[offset + i] != sufijo[i]) return false;
    }
    return true;
}

bool esNumero(const string& s) {
    int n = (int)s.size();
    if (n == 0) return false;
    for (int i = 0; i < n; ++i) {
        unsigned char ch = (unsigned char)s[i];
        if (!isdigit(ch)) return false;
    }
    return true;
}

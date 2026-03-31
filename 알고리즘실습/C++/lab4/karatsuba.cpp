#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

#define BUF_SIZE 1000
using namespace std;

typedef vector<int> LargerInteger;
int cnt = 0;

bool iszero(LargerInteger A){
    bool flag = true;
    for(int i = 0; i < A.size(); i++)
        if (A[i] != 0)
            flag = false;
    return flag;
}
void remove_leading_zeros(LargerInteger &v) {
    while (v.size() > 1 && v.back() == 0) v.pop_back();
    if (v.size() == 1 && iszero(v)) v.clear();
}

LargerInteger roundup(LargerInteger A) {
    int carry = 0;
    for (int i = 0; i < A.size(); i++) {
        A[i] += carry;
        carry = A[i] / 10;
        A[i] %= 10;
    }
    while (carry > 0) {
        A.push_back(carry % 10);
        carry /= 10;
    }
    remove_leading_zeros(A);
    return A;
}

LargerInteger ladd(LargerInteger A, LargerInteger B) {
    LargerInteger result(max(A.size(), B.size()), 0);
    for (int i = 0; i < result.size(); i++) {
        if (i < A.size()) result[i] += A[i];
        if (i < B.size()) result[i] += B[i];
    }
    return roundup(result);
}

LargerInteger lmult(LargerInteger A, LargerInteger B) {
    if (A.empty() || B.empty()) return {};
    LargerInteger result(A.size() + B.size(), 0);
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++)
            result[i + j] += A[i] * B[j];
    }
    return roundup(result);
}

// 10^m 곱하기: 인덱스 0쪽에 0을 m개 삽입
void pow_by_exp(LargerInteger u, int m, LargerInteger &v) {
    if (u.empty()) v.clear();
    else {
        v.assign(m, 0); 
        v.insert(v.end(), u.begin(), u.end());
    }
}

void rem_by_exp(LargerInteger u, int m, LargerInteger &v) {
    int k = min((int)u.size(), m);
    v.assign(u.begin(), u.begin() + k);
    remove_leading_zeros(v);
}

void div_by_exp(LargerInteger u, int m, LargerInteger &d) {
    if (m >= u.size()) d.clear();
    else d.assign(u.begin() + m, u.end());
}


void prod(LargerInteger u, LargerInteger v, LargerInteger &r, int threshold) {
    cnt++;
    int n = max(u.size(), v.size());
    if (iszero(u) || iszero(v)) {
        r.clear();
    } else if (n <= threshold) {
        r = lmult(u, v);
    } else {
        int m = n / 2;
        LargerInteger x, y, w, z, t1, t2, t3, t4, t5, t6, t7, t8;
        div_by_exp(u, m, x); rem_by_exp(u, m, y);
        div_by_exp(v, m, w); rem_by_exp(v, m, z);

        prod(x, w, t1, threshold); pow_by_exp(t1, 2 * m, t2);
        prod(x, z, t3, threshold);
        prod(w, y, t4, threshold);
        t5 = ladd(t3, t4); pow_by_exp(t5, m, t6);
        prod(y, z, t7, threshold);
        t8 = ladd(t2, t6); 
        r = ladd(t8, t7);
    }
}

int main() {
    int threshold;
    string sA, sB;
    LargerInteger A, B, C;

    if (!(cin >> threshold)) return 0;
    cin >> sA >> sB; // fgets 대신 string 사용이 안전함

    for (int i = sA.length() - 1; i >= 0; i--) if (isdigit(sA[i])) A.push_back(sA[i] - '0');
    for (int i = sB.length() - 1; i >= 0; i--) if (isdigit(sB[i])) B.push_back(sB[i] - '0');

    prod(A, B, C, threshold);
    cout << cnt << endl;
    if (C.empty()) cout << 0;
    else for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
    cout << endl;

    return 0;
}
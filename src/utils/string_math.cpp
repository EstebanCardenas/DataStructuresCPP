#pragma once
#include <string>
#include <stack>

using namespace std;

struct StringMath {
    string add(string num1, string num2) {
        string a = num1.size() >= num2.size() ? num1 : num2;
        string b = a == num1 ? num2 : num1;
        int n = a.size(), m = b.size();
        string ans;
        int carry = 0;
        for (int i = 0; i < n; i++) {
            int numa = a[n - 1 - i] - '0';
            int numb = 0;
            if (i < m) {
                numb = b[m - 1 - i] - '0';
            }
            int sum = numa + numb + carry;
            char current = '0' + (sum % 10);
            carry = sum / 10;
            ans.insert(ans.begin(), current);
        }
        if (carry > 0) {
            ans.insert(ans.begin(), '0' + carry);
        }
        return ans;
    }

    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        string a = num1.size() >= num2.size() ? num1 : num2;
        string b = a == num1 ? num2 : num1;
        int n = a.size(), m = b.size();
        stack<string> sums;
        for (int i = m - 1; i >= 0; i--) {
            int sz = m - 1 - i;
            string currentSum(sz, '0');
            int carry = 0;
            int numi = b[i] - '0';
            for (int j = n - 1; j >= 0; j--) {
                int numj = a[j] - '0';
                int prod = (numi * numj + carry);
                char current = '0' + (prod % 10);
                carry = prod / 10;
                currentSum.insert(currentSum.begin(), current);
            }
            if (carry > 0) {
                currentSum.insert(currentSum.begin(), '0' + carry);
            }
            sums.push(currentSum);
        }

        string ans = sums.top(); sums.pop();
        while (!sums.empty()) {
            string current = sums.top(); sums.pop();
            ans = add(ans, current);
        }
        return ans;
    }
};

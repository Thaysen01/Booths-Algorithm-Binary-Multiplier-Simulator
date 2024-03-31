#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string addBinary(string a, string b) {
    string result = ""; // Initialize result
    int s = 0;          // Initialize digit sum

    // Traverse both strings starting from last characters
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0) {
        // Compute sum of last digits and carry
        s += ((i >= 0) ? a[i] - '0' : 0);
        s += ((j >= 0) ? b[j] - '0' : 0);

        // If current digit sum is 1 or 3, add '1' to result
        result = char(s % 2 + '0') + result;

        // Compute carry
        s /= 2;

        // Move to next digits
        i--; j--;
    }
    return result;
}

string findTwosComplement(string str) {
    int n = str.length();

    // Traverse the string to get first '1' from the last of string
    int i;
    for (i = n-1 ; i >= 0 ; i--)
        if (str[i] == '1')
            break;

    // If there exists no '1' concatenate 1 at the starting of string
    // This could be wrong! I think the 2s complement of 0 may be 0.
    // TODO: Test the above assumption.
    if (i == -1)
        return '1' + str;

    // Continue traversal after the position of first '1'
    for (int k = i-1 ; k >= 0; k--) {
        //Just flip the values
        if (str[k] == '1')
            str[k] = '0';
        else
            str[k] = '1';
    }

    // return the modified string
    return str;
}

string subtractBinary(string a, string b) {
    // Find two's complement of b and add it to a
    string twoComplement = findTwosComplement(b);
    return addBinary(a, twoComplement);
}

void boothsAlgorithm(string multiplicand, string multiplier) {
    int n = multiplicand.length();
    string Ac(n, '0');
    char E = '0';

    /**
     * for group of 2s booth:
     *  00, 11: do not add or subtract (nothing happens in this for loop)
     *  01: add the given value of the multiplier to the accumulator
     *  10: add the 2s complement of the given value of the multiplier to the accumulator
    */
    for (int i = 0; i < n; i++) {
        if (multiplier.back() == '1' && E == '0') {
            Ac = subtractBinary(Ac, multiplicand);
        } else if (multiplier.back() == '0' && E == '1') {
            Ac = addBinary(Ac, multiplicand);
        }

        // Arithmetic Right Shift AcQE
        E = multiplier.back();
        multiplier.pop_back();
        multiplier = Ac.back() + multiplier;
        Ac.pop_back();
        Ac = Ac.front() + Ac;
    }

    cout << "Product: " << Ac << multiplier << endl;
}

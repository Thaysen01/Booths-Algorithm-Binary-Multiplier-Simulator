#include <iostream>
#include <algorithm>
#include <chrono>

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
    // if no 1s, return string unmodified
    int i;
    for (i = n-1 ; i >= 0 ; i--) {
        if (str[i] == '1') {
            break;
        }
    }
    // Continue traversal after the position of first '1'
    for (int k = i-1 ; k >= 0; k--) {
        //Just flip the values
        if (str[k] == '1') {
            str[k] = '0';
        } else {
            str[k] = '1';
        }
    }

    // return the modified string
    return str;
}

string subtractBinary(string a, string b) {
    // Find two's complement of b and add it to a
    string twoComplement = findTwosComplement(b);
    return addBinary(a, twoComplement);
}

string boothsAlgorithm(string multiplicand, string multiplier) {
    int n = multiplicand.length();
    string Ac(n, '0'); // simulation of accumulator
    char E = '0'; // extended bit for Q
    
    int numSub = 0;
    int numAdd = 0;

    const auto start{chrono::steady_clock::now()};

    /**
     * for group of 2s booth:
     *  00, 11: do not add or subtract (nothing happens in this for loop)
     *  01: add the given value of the multiplier to the accumulator
     *  10: add the 2s complement of the given value of the multiplier to the accumulator
    */
    for (int i = 0; i < n; i++) {
        if (multiplier.back() == '1' && E == '0') {
            Ac = subtractBinary(Ac, multiplicand);
            numSub++;
        } else if (multiplier.back() == '0' && E == '1') {
            Ac = addBinary(Ac, multiplicand);
            numAdd++;
        }

        // Arithmetic Right Shift AcQE
        E = multiplier.back();
        multiplier.pop_back();
        multiplier = Ac.back() + multiplier;
        Ac.pop_back();
        Ac = Ac.front() + Ac;
    }

    string result = Ac + multiplier;

    const auto end{chrono::steady_clock::now()};
    const chrono::duration<double> elapsed_seconds{end - start};

    /*cout << "TOTAL CALCULATION TIME (MICROSECONDS): " << (elapsed_seconds.count())*1000000 << endl;
    cout << "TOTAL ITERATIONS: " << n << endl;
    cout << "TOTAL ADDITIONS: " << numAdd << endl;
    cout << "TOTAL SUBTRACTIONS: " << numSub << endl;
    cout << endl; */

    cout << (elapsed_seconds.count())*1000000 << endl;

    return result;
}

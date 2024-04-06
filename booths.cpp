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

string leftShift(string a) {
    int n = a.length();

    string result;

    // traverse the binary string, move all elements one spot to the left
    for (int i = 0; i < n-1; i++) {
       result.push_back(a[i+1]);
    }
    result.push_back('0'); // 0 is always the additional digit in logic shifts
    return result;
}

string boothsAlgorithm(string multiplier, string multiplicand) {
    int n = multiplicand.length();
    int numIterations = 0;
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
        numIterations++;
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

   cout << "PRODUCT: " << result << endl;
   cout << "TOTAL CALCULATION TIME (MICROSECONDS): " << (elapsed_seconds.count())*1000000 << endl;
   cout << "TOTAL ITERATIONS: " << numIterations << endl;
   cout << "TOTAL ADDITIONS: " << numAdd << endl;
   cout << "TOTAL SUBTRACTIONS: " << numSub << endl;
   cout << endl;

    return result;
}

string widenNumber(string a) {
    string result;
    if (a.front() == '0')
    {
        result.push_back('0');
    } else {
        result.push_back('1');
    }

    for (int i = 0; i < a.length(); i++) {
        result.push_back(a[i]);
    }
    
    return result;
}

string modifiedBoothsAlgorithm(string multiplier, string multiplicand) {
    string wideMultiplicand = widenNumber(multiplicand);
    int n = multiplier.length();
    int numIterations = 0;
    string Ac(n, '0'); // simulation of accumulator
    char E = '0'; // extended bit for Q
    
    int numSub = 0;
    int numAdd = 0;

    const auto start{chrono::steady_clock::now()};

   for (int i = 0; i < n; i+=2) {
    numIterations++;
    if (multiplier[multiplier.length() - 2] == '0') {
        /*  000 no action shift right twice
            001 add multiplicand shift right twice
            010 add multiplicand shift right twice
            011 add 2*multiplicand shift right twice
        */
       if (multiplier.back() == '1' && E == '0') {
        Ac = addBinary(Ac, wideMultiplicand);
        numAdd++;
       } else if (multiplier.back() == '0' && E == '1') {
        Ac = addBinary(Ac, wideMultiplicand);
        numAdd++;
       } else if (multiplier.back() == '1' && E == '1') {
        string multiplicand_2 = leftShift(wideMultiplicand); // left shift and one add is faster than two adds
        Ac = addBinary(Ac, multiplicand_2);
        numAdd ++;
       }
    } else {
        /*  100 sub 2*multiplicand shift right twice
            101 sub multiplicand shift right twice
            110 sub multiplicand shift right twice
            111 no action shift right twice 
        */
       if (multiplier.back() == '1' && E == '0') {
        Ac = subtractBinary(Ac, wideMultiplicand);
        numSub++;
       } else if (multiplier.back() == '0' && E == '1') {
        Ac = subtractBinary(Ac, wideMultiplicand);
        numSub++;
       } else if (multiplier.back() == '0' && E == '0') {
        string multiplicand_2 = leftShift(wideMultiplicand); // left shift and one sub is faster than two subs
        Ac = subtractBinary(Ac, multiplicand_2);
        numSub ++;
       }
    }
    
        // Arithmetic Right Shift AcQE
        E = multiplier.back(); // this is effectively unneeded, but is included to fully simulate multiple multiple rigth shifts
        multiplier.pop_back();
        multiplier = Ac.back() + multiplier;
        Ac.pop_back();
        Ac = Ac.front() + Ac;

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

  cout << "PRODUCT: " << result << endl;
   cout << "TOTAL CALCULATION TIME (MICROSECONDS): " << (elapsed_seconds.count())*1000000 << endl;
   cout << "TOTAL ITERATIONS: " << numIterations << endl;
   cout << "TOTAL ADDITIONS: " << numAdd << endl;
   cout << "TOTAL SUBTRACTIONS: " << numSub << endl;
   cout << endl;

    return result;
}

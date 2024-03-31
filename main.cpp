#include "booths.h"
#include "assert.h"

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {

    string multiplicand, multiplier;

    cout << "Enter multiplicand (binary): ";
    cin >> multiplicand;
    cout << "Enter multiplier (binary): ";
    cin >> multiplier;

    // Ensure both strings are of equal length
    // This should make results accurate for different lengths
    int length = max(multiplicand.length(), multiplier.length());
    multiplicand = string(length - multiplicand.length(), '0') + multiplicand;
    multiplier = string(length - multiplier.length(), '0') + multiplier;

    boothsAlgorithm(multiplicand, multiplier);

    return 0;
}

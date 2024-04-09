#include "booths.h"
#include <iostream>

using namespace std;

int main() {

    string multiplicand, multiplier;

    while (true) {
    cout << "Enter multiplier (binary): ";
    cin >> multiplier;
    cout << "Enter multiplicand (binary): ";
    cin >> multiplicand;

    // Ensure both strings are of equal length
    // This should make results accurate for different lengths
    int length = max(multiplicand.length(), multiplier.length());
    multiplicand = string(length - multiplicand.length(), '0') + multiplicand;
    multiplier = string(length - multiplier.length(), '0') + multiplier;

    boothsAlgorithm(multiplier, multiplicand);
    modifiedBoothsAlgorithm(multiplier, multiplicand);

    }

    return 0;
}

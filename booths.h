#include <string>

using namespace std;

/**
 * @brief Adds two binary numbers that are stored as strings.
 * 
 * From least significant bit to most significant bit, traverse the string.
 * The sum of the digit and the carry is calculated for each step.
 * 
 * @return A string holding the result of the binary addition.
*/
string addBinary(string a, string b);

/**
 * @brief Finds the 2s complement of a binary number stored as a string.
 * 
 * The string is traveresed from least significant bit to most significant bit until
 * the fist 1 is found. After the fist one, every value is flipped up to and including
 * the most significant bit.
 * 
 * @return A string holding the 2s complement of the passed str.
*/
string findTwosComplement(string str);

/**
 * @brief Subtracts two binary numbers that are stored as stings.
 * 
 * Just calls the 2s complement function on parameter b, then calls the add function
 * with parameter a and the newly found 2s complement.
 * 
 * @return A string holding the result of subtracting a from b.
*/
string subtractBinary(string a, string b);

/**
 * @brief Performs a logic shift left (doubling) on a binary number stored as a string.
 * 
 * The string is traversed with all characters shifted one spot to the left. The first character falls off.
 * The new digit is always a zero.
 * 
 * @return A string holding the doubled value of the binary number that was passed in.
*/
string leftShift(string a);

/**
 * @brief Increases the number of bits in a binary number by one.
 * 
 *  The first digit of the number passed into the the function is duplicated and prepended to the string.
 * 
 * @return A binary number stored as a string that is one bit wider than what was passed in.
*/
string widenNumber(string a);

/**
 * @brief Performs group of two Booth's algorithm on two binary numbers stored as strings.
 * 
 * The accumulator and E are initialized to 0. Then, for the number of bits in the multiplier,
 * the least significant bit of the multiplier and the E are are viewed. If Q[LSB]E is 00 or
 * 11, an arithmetic right shift through AcQE is performed. If Q[LSB]E is 01, the multiplicand
 * is added to Ac, then an arithmetic right shift through AcQE is performed. If Q[LSB]E is 10,
 * the 2s complement of the multiplier is added to Ac, then an arithmetic right shift through 
 * AcQE is performed.
 * 
 * @return A string containing the binary result of multiplying the multiplicand by the multiplier.
*/
string boothsAlgorithm(string multiplicand, string multiplier);

/**
 * @brief Performs group of three Booth's algorithm on two binary numbers stored as strings.
 * 
 * The accumulator and E are initialized to 0. Then, for half the number of bits in the multiplier,
 * the formula for group of three booth's algorithm is performed. When the multipliand is addded or subtracted,
 * a widened version of it is used to account for possible overflow.
 * 
 * @return A string containing the binary result of multiplying the multiplicand by the multiplier.
*/
string modifiedBoothsAlgorithm(string multiplicand, string multiplier);
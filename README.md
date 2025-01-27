### Read the Technical Report for a more detailed analysis of this project. 

This is an efficient simulator and comparison tool for Booth's (Group of Two/Radix-4) and Modified Booth's (Group of Three/Radix-8) algorithms for binary multiplication, implemented in C++. Binary numbers are stored internally as strings as this was found to be the easiest way to work with them. This simulator provides an educational and practical tool to understand and compare these two versions of Booth's Algorithm.

# Usage

When prompted, enter a multiplier and multiplicand as binary numbers. They need not be the same length, the simulator will handle that internally. The results will be calculated and returned using both algorithms, as will additional stats from each run of the algorithm. These statistics are: the total number of iterations needed to complete the calculation, the total number of additions, the total number of subtractions, and total calculation time in microseconds.

# What is Booth's Algorithm?
Booth's Algorithm is a multiplication algorithm, commonly used in ALUs, that multiplies two signed binary numbers in two's complement notation.

The key idea behind Booth's Algorithm is to encode the multiplier in such a way that it minimizes the number of additions and subtractions. This is achieved by examining pairs of adjacent bits of the multiplier, which leads to more efficient handling of consecutive bits.

### Booth's Algorithm (Radix-4)
In the Radix-4 version of Booth's Algorithm, the multiplier is divided into groups of two bits. This method simplifies the process by reducing the number of partial products that need to be added. Here are the steps:

- Initialization: Set up the multiplicand, the multiplier, and an accumulator initialized to zero.
- Grouping: Group the bits of the multiplier in pairs, starting from the least significant bit.
- Operation: For each pair of bits, determine the operation to be performed on the multiplicand (add, subtract, or no operation) based on the pair and its previous adjacent bit.
- Shifting: Shift the multiplicand and the accumulator appropriately after each operation.
- Iteration: Repeat the process until all pairs of bits have been processed.

### Modified Booth's Algorithm (Radix-8)
The Radix-8 version extends the grouping to three bits, further reducing the number of operations required for large numbers with more significant runs of 1's or 0's. The steps are similar but involve groups of three bits:

- Initialization: Similar to Radix-4, but with an additional bit considered for grouping.
- Grouping: Divide the multiplier into groups of three bits.
- Operation: Each group of three bits, along with the preceding bit, determines the operation (such as doubling or tripling the multiplicand, adding, subtracting, or no operation).
- Shifting: Shift operations are carried out as in Radix-4 but adjusted for the larger grouping.
- Iteration: Continue until all bits are processed.

Both versions aim to optimize binary multiplication by reducing the number of necessary operations, making Booth's Algorithm particularly useful in hardware implementations where efficiency is crucial.

Caesar Cipher Breaker
This program is designed to break the Caesar cipher by analyzing the distribution of characters in the English language. It reads the distribution of the English alphabet from a file, calculates the expected occurrences of each character in the text, and then performs a Chi-Square analysis to find the most likely shift used in the Caesar cipher. Finally, it decodes the text using the determined shift.

Functions:
readDistribution: Reads the distribution of the English alphabet from a file and stores it in an array.

occurrencesOfCharacters: Counts the occurrences of each character in the text and stores them in an array.

expectedOccurrences: Calculates the expected occurrences of each character in the text based on the English alphabet distribution.

histogram: Calculates the histogram for a character based on its actual and expected occurrences.

ChiSquareDist: Calculates the Chi-Square distance for the text based on the histogram values.

permuteToLeft: Permutes the elements of an array to the left.

decodedText: Decodes the text using the specified number of positions.

breakCesarCipherTest: Breaks the Caesar cipher by testing all possible permutations and choosing the one with the minimum Chi-Square distance.

How to Use:
Ensure that the distribution.txt file containing the distribution of the English alphabet is present in the specified location.

Compile the program using a C compiler.

Run the compiled executable.

Enter the text you want to decode when prompted.

The program will output the decoded message.

Note:
The program assumes that the input text is encoded using the Caesar cipher with an unknown shift value.

It uses statistical analysis to determine the most likely shift value and decode the text accordingly.

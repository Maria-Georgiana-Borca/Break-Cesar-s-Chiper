#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void readDistribution(float distribution[]) {
    /*
     * Description: This function reads the distribution of the English alphabet from a file and stores it in an array.
     * Pre: distribution - an array of floats
     * Post: the distribution of the English alphabet is stored in the array
     */
    FILE *file_pointer;
    file_pointer = fopen("/Users/mariaborca/Documents/GitHub/Break-Cesar-s-Chiper/distribution.txt", "r");

    if (file_pointer == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char buffer[27];
    int index = 0;

    while (fgets(buffer, sizeof(buffer), file_pointer) != NULL && index < 27) {
        distribution[index] = atof(buffer);
        index += 1;
    }

    fclose(file_pointer);
}

void occurrencesOfCharacters(char text[], int noOccurrences[]) {
    /*
     * Description: This function counts the occurrences of each character in the text and stores them in an array.
     * Pre: text - a string, noOccurrences - an array of integers
     * Post: the occurrences of each character in the text are stored in the array
     */
    for (char i = 'a'; i <= 'z'; i++) {
        int cont = 0;
        for (int j = 0; j < strlen(text); j++)
            if (text[j] == i || text[j] == toupper(i))
                cont++;
        noOccurrences[i - 'a'] = cont;
    }
}

void expectedOccurrences(float distribution[], float expected[], int noOfCharacters) {
    /*
     * Description: This function calculates the expected occurrences of each character in the text and stores them in an array.
     * Pre: distribution - an array of floats, expected - an array of floats, noOfCharacters - an integer
     * Post: the expected occurrences of each character in the text are stored in the array
     */
    for (char i = 'a'; i <= 'z'; i++)
        expected[i - 'a'] = noOfCharacters * (distribution[i - 'a'] / 100);
}

float histogram(float noOccurrences, float expected) {
    /*
     * Description: This function calculates the histogram for a character.
     * Pre: noOccurrences - a float, expected - a float
     * Post: the histogram for the character is returned
     */
    float histogram = (noOccurrences - expected) * (noOccurrences - expected) / expected;
    return histogram;
}

float ChiSquareDist(int noOccurrences[], float expected[]) {
    /*
     * Description: This function calculates the Chi-Square distance for the text.
     * Pre: noOccurrences - an array of integers, expected - an array of floats
     * Post: the Chi-Square distance for the text is returned
     */
    float sum = 0;
    for (int i = 0; i < 26; i++)
        sum += histogram(noOccurrences[i], expected[i]);

    return sum;
}

void permuteToLeft(void *array, size_t typeSize, size_t arraySize) {
    /*
     * Description: This function permutes the elements of an array to the left.
     * Pre: array - an array of any type, typeSize - the size of the type of the elements in the array, arraySize - the size of the array
     * Post: the elements of the array are permuted to the left
     */
    unsigned char temp[typeSize];

    memcpy(temp, array, typeSize);

    for (int i = 0; i < arraySize; i++) {
        memcpy(&array[i * typeSize], &array[(i + 1) * typeSize], typeSize);
    }

    memcpy(&array[(arraySize - 1) * typeSize], temp, typeSize);
}

void decodedText(char *text, int noPositions){
    /*
     * Description: This function decodes the text using the number of positions.
     * Pre: text - a string, noPositions - an integer
     * Post: the text is decoded
     */
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            if ((isupper(text[i]) && text[i] - noPositions < 65) || (islower(text[i]) && text[i] - noPositions < 97))
                text[i] = text[i] - noPositions + 26;
            else text[i] = text[i] - noPositions;
        }
    }
}

void breakCesarCipherTest(int noOccurrences[], float expected[], char text[], float distribution[]) {
    /*
     * Description: This function breaks the Cesar cipher by testing all the possible permutations and choosing the one with the minimum Chi-Square distance.
     * Pre: noOccurrences - an array of integers, expected - an array of floats, text - a string, distribution - an array of floats
     * Post: the Cesar cipher is broken and the text is decoded
     */
    float chiDist;
    float minChiDist = INFINITY;
    int noOfPerm;
    int i = 0;
    while (i < 25) {
        chiDist = ChiSquareDist(noOccurrences, expected);
        if (chiDist < minChiDist) {
            minChiDist = chiDist;
            noOfPerm = i;
        }
        i++;
        permuteToLeft(noOccurrences, sizeof(int), 26);
    }
    decodedText(text, noOfPerm);
}

int main(){
    float distribution[28];
    float expected[28];
    int noOccurrences[28];
    char text[10000];
    readDistribution(distribution);
    printf("Please enter the text you want to decode: ");
    fgets(text, 10000, stdin);
    occurrencesOfCharacters(text, noOccurrences);
    expectedOccurrences(distribution, expected, strlen(text));
    breakCesarCipherTest(noOccurrences, expected, text, distribution);
    printf("The decoded message: %s", text);
    return 0;
}
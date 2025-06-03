#include <stdio.h>
#include <string.h> // For strcpy, strcat
#include <stdlib.h> // For atoi, sprintf

// Function to find the larger number by concatenation logic
int find_larger(int a, int b) {
    char s_a[50], s_b[50];
    char s_ab[100], s_ba[100]; // Buffers for concatenated strings

    // Convert integers to strings
    sprintf(s_a, "%d", a);
    sprintf(s_b, "%d", b);

    // Concatenate a then b
    strcpy(s_ab, s_a);
    strcat(s_ab, s_b);

    // Concatenate b then a
    strcpy(s_ba, s_b);
    strcat(s_ba, s_a);

    // Convert concatenated strings back to integers
    int val_ab = atoi(s_ab);
    int val_ba = atoi(s_ba);

    // Return the larger of the two concatenated integers
    if (val_ab > val_ba) {
        return val_ab;
    } else {
        return val_ba;
    }
}

int main() {
  int num1, num2, result;

  // Example 1
  num1 = 10;
  num2 = 9;
  result = find_larger(num1, num2);
  printf("For inputs %d and %d, the larger concatenated number is %d\n", num1, num2, result); // Expected: 910

  // Example 2
  num1 = 15;
  num2 = 7;
  result = find_larger(num1, num2);
  printf("For inputs %d and %d, the larger concatenated number is %d\n", num1, num2, result); // Expected: 715

  // Example 3
  num1 = 6;
  num2 = 65;
  result = find_larger(num1, num2);
  printf("For inputs %d and %d, the larger concatenated number is %d\n", num1, num2, result); // Expected: 665

  // Additional test case: Equal numbers (e.g., 8, 8)
  num1 = 8;
  num2 = 8;
  result = find_larger(num1, num2);
  printf("For inputs %d and %d, the larger concatenated number is %d\n", num1, num2, result); // Expected: 88

  // Additional test case: (e.g., 121, 12)
  num1 = 121;
  num2 = 12;
  result = find_larger(num1, num2);
  printf("For inputs %d and %d, the larger concatenated number is %d\n", num1, num2, result); // Expected: 12121


  return 0;
}

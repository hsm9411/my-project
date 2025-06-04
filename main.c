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

int** allocate_2d_array(size_t rows, size_t cols) {
    int** arr = (int**)malloc(rows * sizeof(int*));
    if (arr == NULL) {
        // perror("Failed to allocate memory for row pointers"); // Optional error message
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        arr[i] = (int*)malloc(cols * sizeof(int));
        if (arr[i] == NULL) {
            // perror("Failed to allocate memory for a row"); // Optional error message
            // Free previously allocated rows
            for (size_t j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr); // Free the row pointers array
            return NULL;
        }
    }
    return arr;
}

void free_2d_array(int** arr, size_t rows) {
    if (arr == NULL) {
        return;
    }
    for (size_t i = 0; i < rows; i++) {
        free(arr[i]); // arr[i] can be NULL if a row allocation failed and wasn't fully cleaned up,
                      // but free(NULL) is safe.
    }
    free(arr);
}

// int** make_square_array(int** original_arr, size_t arr_row, size_t arr_col) { // OLD
int** newArr(int** oldArr, size_t row, size_t col) { // NEW
    // REMOVE: if (new_dim_ptr == NULL) { return NULL; }

    size_t N = (row > col) ? row : col; // NEW internal

    // Handle N=0 case: if oldArr is also NULL or dimensions are zero.
    // If row and col are both 0, then N will be 0.
    if (N == 0) {
        // REMOVE: if (new_dim_ptr != NULL) *new_dim_ptr = 0;
        return NULL; // Still return NULL for a 0x0 target array as per previous logic
    }

    // REMOVE: if (new_dim_ptr != NULL) *new_dim_ptr = N;

    int** square_arr = allocate_2d_array(N, N);
    if (square_arr == NULL) {
        // REMOVE: if (new_dim_ptr != NULL) *new_dim_ptr = 0; // Or just leave N as is.
        return NULL;
    }

    // Initialize square_arr with zeros
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            square_arr[i][j] = 0;
        }
    }

    // Copy elements from oldArr if it's not NULL and dimensions are valid
    if (oldArr != NULL) {
        for (size_t i = 0; i < row; i++) { // NEW internal
            // Ensure oldArr[i] is not NULL if col > 0.
            if (oldArr[i] == NULL && col > 0) { // NEW internal
                free_2d_array(square_arr, N);
                return NULL; // Malformed oldArr
            }
            // Ensure we don't write past the bounds of square_arr,
            // though N >= row and N >= col should prevent this.
            // The explicit checks i < N and j < N are good practice.
            if (i < N) {
                 for (size_t j = 0; j < col; j++) { // NEW internal
                    if (j < N) {
                        square_arr[i][j] = oldArr[i][j]; // NEW internal
                    }
                }
            }
        }
    }

    return square_arr;
}

void print_2d_array(int** arr, size_t rows, size_t cols, const char* label) {
    if (label != NULL) {
        printf("%s:\n", label);
    }
    if (arr == NULL || rows == 0 || cols == 0) {
        printf("(empty or NULL array)\n");
        return;
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%4d ", arr[i][j]); // Print with some padding
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // --- Test Case 1: 3x2 Array ---
    printf("--- Test Case 1: 3x2 Array ---\n");
    size_t orig_rows1 = 3, orig_cols1 = 2;
    int** arr1 = allocate_2d_array(orig_rows1, orig_cols1);
    if (arr1 == NULL) {
        printf("Failed to allocate arr1\n");
        return 1;
    }
    for (size_t i = 0; i < orig_rows1; i++) {
        for (size_t j = 0; j < orig_cols1; j++) {
            arr1[i][j] = (int)((i + 1) * 10 + (j + 1));
        }
    }
    print_2d_array(arr1, orig_rows1, orig_cols1, "Original Array 1 (3x2)");

    size_t n1 = (orig_rows1 > orig_cols1) ? orig_rows1 : orig_cols1;
    int** square_arr1 = newArr(arr1, orig_rows1, orig_cols1);
    if (square_arr1 == NULL) {
        printf("Failed to create square_arr1 or target dimension was 0 (calculated N: %zu)\n", n1);
    } else {
        print_2d_array(square_arr1, n1, n1, "Squared Array 1");
    }

    free_2d_array(arr1, orig_rows1); // Free original
    free_2d_array(square_arr1, n1); // Free new one
    printf("\n");

    // --- Test Case 2: 2x4 Array ---
    printf("--- Test Case 2: 2x4 Array ---\n");
    size_t orig_rows2 = 2, orig_cols2 = 4;
    int** arr2 = allocate_2d_array(orig_rows2, orig_cols2);
    if (arr2 == NULL) {
        printf("Failed to allocate arr2\n");
        return 1;
    }
    for (size_t i = 0; i < orig_rows2; i++) {
        for (size_t j = 0; j < orig_cols2; j++) {
            arr2[i][j] = (int)((i + 1) * 100 + (j + 1));
        }
    }
    print_2d_array(arr2, orig_rows2, orig_cols2, "Original Array 2 (2x4)");
    size_t n2 = (orig_rows2 > orig_cols2) ? orig_rows2 : orig_cols2;
    int** square_arr2 = newArr(arr2, orig_rows2, orig_cols2);
    if (square_arr2 == NULL) {
        printf("Failed to create square_arr2 or target dimension was 0 (calculated N: %zu)\n", n2);
    } else {
        print_2d_array(square_arr2, n2, n2, "Squared Array 2");
    }
    free_2d_array(arr2, orig_rows2);
    free_2d_array(square_arr2, n2);
    printf("\n");

    // --- Test Case 3: Already Square (e.g., 2x2) ---
    printf("--- Test Case 3: Already Square (2x2) ---\n");
    size_t orig_rows3 = 2, orig_cols3 = 2;
    int** arr3 = allocate_2d_array(orig_rows3, orig_cols3);
    if (arr3 == NULL) {
        printf("Failed to allocate arr3\n");
        return 1;
    }
    for (size_t i = 0; i < orig_rows3; i++) {
      for (size_t j = 0; j < orig_cols3; j++) {
        arr3[i][j] = (int)(i * 10 + j + 70); // Simple population
      }
    }
    print_2d_array(arr3, orig_rows3, orig_cols3, "Original Array 3 (2x2)");
    size_t n3 = (orig_rows3 > orig_cols3) ? orig_rows3 : orig_cols3;
    int** square_arr3 = newArr(arr3, orig_rows3, orig_cols3);
    if (square_arr3 == NULL) {
         printf("Failed to create square_arr3 or target dimension was 0 (calculated N: %zu)\n", n3);
    } else {
        print_2d_array(square_arr3, n3, n3, "Squared Array 3");
    }
    free_2d_array(arr3, orig_rows3);
    free_2d_array(square_arr3, n3);
    printf("\n");

    // --- Test Case 4: Empty Array (0x0 input) ---
    printf("--- Test Case 4: Empty Array (0x0 input) ---\n");
    size_t orig_rows_empty = 0, orig_cols_empty = 0;
    size_t n_empty = (orig_rows_empty > orig_cols_empty) ? orig_rows_empty : orig_cols_empty; // Will be 0

    int** square_empty = newArr(NULL, orig_rows_empty, orig_cols_empty);
    if (square_empty == NULL && n_empty == 0) {
        printf("Correctly handled empty array: returned NULL, calculated N is 0.\n");
    } else {
        printf("Incorrectly handled empty array. square_empty: %p, calculated N: %zu\n", (void*)square_empty, n_empty);
    }
    // Attempt to print, should show (empty or NULL array)
    print_2d_array(square_empty, n_empty, n_empty, "Attempted Squared Empty Array");
    free_2d_array(square_empty, n_empty); // Safe to call with NULL / 0
    printf("\n");

    // --- Test Case 5: NULL input array with non-zero dimensions (e.g. target 2x2)
    printf("--- Test Case 5: NULL input array with non-zero dimensions (target 2x2) ---\n");
    size_t orig_rows_null_input = 2, orig_cols_null_input = 2; // Example target dimensions
    size_t n_null_input = (orig_rows_null_input > orig_cols_null_input) ? orig_rows_null_input : orig_cols_null_input;

    // Pass NULL as the original array, but with non-zero row/col for newArr to determine N
    int** square_null_input = newArr(NULL, orig_rows_null_input, orig_cols_null_input);
    if (square_null_input != NULL && n_null_input == 2) { // Check against calculated N
        printf("Created a %zux%zu zeroed array as expected.\n", n_null_input, n_null_input);
        print_2d_array(square_null_input, n_null_input, n_null_input, "Squared NULL Input Array (should be all zeros)");
    } else {
        printf("Failed to handle NULL input array appropriately. square_null_input: %p, calculated N: %zu\n", (void*)square_null_input, n_null_input);
    }
    free_2d_array(square_null_input, n_null_input);
    printf("\n");

    return 0;
}

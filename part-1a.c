#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TIMESTAMP_LEN 20 // 19 bytes for the visible timestamp data plus one for \0

typedef struct {
    char timestamp[MAX_TIMESTAMP_LEN];
    float value;
} Measurement;

typedef struct {
    Measurement* data;
    int count;
} MeasurementsArray;

void add_measurement(MeasurementsArray* arrayPtr, char* timestamp, float value);
void print_measurements(MeasurementsArray array);
void read_from_file(MeasurementsArray* arrayPtr, char* filename);

MeasurementsArray doMergeSort(MeasurementsArray originalArray);
void mergeSort(Measurement data[], int leftIdx, int rightIdx);
void merge(Measurement data[], int leftIdx, int midIdx, int rightIdx);

MeasurementsArray doQuickSort(MeasurementsArray originalArray);
void quickSort(Measurement* arr, int low, int high);
int partition(Measurement data[], int low, int high);
void swap(Measurement* a, Measurement* b);

double compute_sorting_time(clock_t start, clock_t end);

int main(void) {
    MeasurementsArray array = { NULL, 0 };
    MeasurementsArray array_mergesort = { NULL, 0 };
    MeasurementsArray array_quicksort = { NULL, 0 };

    read_from_file(&array, "data/tempm.txt");
    //print_measurements(array);

    array_mergesort = doMergeSort(array);
    //print_measurements(array_mergesort);

    array_quicksort = doQuickSort(array);
    //print_measurements(array_quicksort);

    return 0;
}

// Merge sort functions
MeasurementsArray doMergeSort(MeasurementsArray originalArray) {
    MeasurementsArray result = {NULL, 0};
    clock_t start, end;

    // Check for invalid input
    if (originalArray.data == NULL || originalArray.count <= 0) {
        printf("doMergeSort: Invalid input array\n");
        return result;
    }

    // Allocate memory for a new sorted array
    result.data = malloc(originalArray.count * sizeof(Measurement));
    if (result.data == NULL) {
        printf("doMergeSort: Memory allocation failed for result data.\n");
        return result;
    }
    
    // Copy all data from the original array to the sorted one
    memcpy(result.data, originalArray.data, originalArray.count * sizeof(Measurement));
    result.count = originalArray.count;

    // Call mergeSort to do the sorting recursively
    printf("\nRunning Merge Sort...\n");
    start = clock();
    mergeSort(result.data, 0, result.count - 1);
    end = clock();
    printf("Merge Sort completed in %.6f seconds.\n", compute_sorting_time(start, end));

    return result;
}

void mergeSort(Measurement data[], int leftIdx, int rightIdx) {
    if (leftIdx < rightIdx) {
        int midIdx = leftIdx + (rightIdx - leftIdx) / 2;
        mergeSort(data, leftIdx, midIdx);
        mergeSort(data, midIdx + 1, rightIdx);
        merge(data, leftIdx, midIdx, rightIdx);
    }
}

void merge(Measurement data[], int leftIdx, int midIdx, int rightIdx) {
    int leftSize = midIdx - leftIdx + 1;
    int rightSize = rightIdx - midIdx;

    // Allocate temporary data arrays
    Measurement* leftArray = malloc(leftSize * sizeof(Measurement));
    if (leftArray == NULL) {
        printf("merge: Memory allocation failed for leftArray.\n");
        return;
    }
    Measurement* rightArray = malloc(rightSize * sizeof(Measurement));
    if (rightArray == NULL) {
        printf("merge: Memory allocation failed for rightArray.\n");
        return;
    }

    // Fill them up with data from the original data array
    for (int i = 0; i < leftSize; i++) 
        leftArray[i] = data[leftIdx + i];

    for (int j = 0; j < rightSize; j++)
        rightArray[j] = data[midIdx + 1 + j];

    int i = 0, j = 0, k = leftIdx;
    while (i < leftSize && j < rightSize) {
        if (leftArray[i].value <= rightArray[j].value)
            data[k++] = leftArray[i++];
        else
            data[k++] = rightArray[j++];
    }

    // Insert the remaining data
    while (i < leftSize) {
        data[k++] = leftArray[i++];
    }

    while (j < rightSize) {
        data[k++] = rightArray[j++];
    }

    // Free temporary arrays
    free(leftArray);
    free(rightArray);
}

// Quick Sort functions
MeasurementsArray doQuickSort(MeasurementsArray originalArray) {
    MeasurementsArray result = {NULL, 0};
    clock_t start, end;

    // Check for invalid input
    if (originalArray.data == NULL || originalArray.count <= 0) {
        printf("doQuickSort: Invalid input array\n");
        return result;
    }

    // Allocate memory for a new sorted array
    result.data = malloc(originalArray.count * sizeof(Measurement));
    if (result.data == NULL) {
        printf("doQuickSort: Memory allocation failed for result data.\n");
        return result;
    }

    // Copy all data from the original array to the sorted one
    memcpy(result.data, originalArray.data, originalArray.count * sizeof(Measurement));
    result.count = originalArray.count;

    // Call quickSort to do the sorting recursively
    printf("\nRunning Quick Sort...\n");
    start = clock();
    quickSort(result.data, 0, result.count - 1);
    end = clock();
    printf("Quick Sort completed in %.6f seconds.\n", compute_sorting_time(start, end));

    return result;
}

void quickSort(Measurement* arr, int low, int high) {
    if (low < high) {
        // pi is the partitioning index
        int pi = partition(arr, low, high);

        // Sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(Measurement data[], int low, int high) {
    float pivot = data[high].value;  // Use the last element as pivot
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        // Check if the current element is smaller than the pivot
        if (data[j].value < pivot) {
            i++;
            swap(&data[i], &data[j]);
        }
    }

    // Swap pivot to the correct position
    swap(&data[i + 1], &data[high]);
    return (i + 1);
}

void swap(Measurement* a, Measurement* b) {
    Measurement temp = *a;
    *a = *b;
    *b = temp;
}

// Sorting time function
double compute_sorting_time(clock_t start, clock_t end) {
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// General functions
void add_measurement(MeasurementsArray* arrayPtr, char* timestamp, float value) {
    int newCount = arrayPtr->count + 1;

    // Allocate new measurements array
    Measurement* temp = realloc(arrayPtr->data, newCount * sizeof(Measurement));
    if (temp == NULL) {
        printf("add_measurement: Memory allocation failed.\n");
        return;
    }
    arrayPtr->data = temp;

    // Fill the new measurement entry with its data
    strncpy(arrayPtr->data[newCount - 1].timestamp, timestamp, sizeof(arrayPtr->data[0].timestamp) - 1);
    arrayPtr->data[newCount - 1].timestamp[sizeof(arrayPtr->data[0].timestamp) - 1] = '\0';
    arrayPtr->data[newCount - 1].value = value;

    // Update the count
    arrayPtr->count = newCount;
}

void print_measurements(MeasurementsArray array) {
    int i;

    if (array.count <= 0) {
        printf("print_measurements: Array is empty.\n");
        return;
    }

    printf("\nSaved measurement data:\n");
    for (i = 0; i < array.count; i++) {
        printf("%s: %.2f\n", array.data[i].timestamp, array.data[i].value);
    }
}

void read_from_file(MeasurementsArray* arrayPtr, char* filename) {
    if (filename == NULL) {
        printf("read_from_file: Filename is invalid.\n");
        return;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int c;
    unsigned int i = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c == '"') {
            // Parse timestamp
            char timestamp[MAX_TIMESTAMP_LEN] = { 0 };
            i = 0;
            while ((c = fgetc(file)) != '"' && c != EOF && i < MAX_TIMESTAMP_LEN - 1) {
                timestamp[i++] = c;
            }
            timestamp[i] = '\0';

            // Skip to value
            while ((c = fgetc(file)) != '"' && c != EOF);
            if (c == EOF) break;

            // Parse value as a string
            char valueStr[32] = { 0 };
            i = 0;
            while ((c = fgetc(file)) != '"' && c != EOF && i < sizeof(valueStr) - 1) {
                valueStr[i++] = c;
            }
            valueStr[i] = '\0';

            // Convert value to float
            float value = atof(valueStr);

            // Add measurement to array
            add_measurement(arrayPtr, timestamp, value);
        }
    }
    printf("Read %d measurement entries from file %s\n", arrayPtr->count, filename);
}

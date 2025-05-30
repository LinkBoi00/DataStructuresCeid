#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_TIMESTAMP_LEN 20                // 19 bytes for the visible timestamp data plus one for \0
#define CUSTOM_EPOCH_OFFSET 1356904800      // 1356904800 corresponds to 2013-01-00T00:00:00 - timestamp_to_epoch("2013-01-00T00:00:00")

typedef struct {
    char timestamp[MAX_TIMESTAMP_LEN];
    int64_t time_epoch;                     // with custom epoch offset applied to make values smaller
    float value;
} Measurement;

typedef struct {
    Measurement* data;
    int count;
} MeasurementsArray;

void add_measurement(MeasurementsArray* arrayPtr, char* timestamp, float value);
void print_measurements(MeasurementsArray array);
void read_from_file(MeasurementsArray* arrayPtr, char* filename);
int64_t timestamp_to_epoch(char* timestamp);

void mergeSort(Measurement data[], int leftIdx, int rightIdx);
void merge(Measurement data[], int leftIdx, int midIdx, int rightIdx);

int64_t get_user_input(void);
void clear_stdin(void);

int BIS(MeasurementsArray arr, int left, int right, int64_t target_epoch);
int BIS_star(MeasurementsArray arr, int left, int right, int64_t target_epoch);
int linear_search(MeasurementsArray arr, int left, int right, int64_t target_epoch);
void print_searching_time(clock_t start, clock_t end);

int main(void) {
    MeasurementsArray array = { NULL, 0 };
    clock_t start, end;

    read_from_file(&array, "data/tempm.txt");
    //print_measurements(array);

    // Sort the array (Needed for BIS)
    mergeSort(array.data, 0, array.count - 1);
    //print_measurements(array);

    // Get the timestamp from the user (and convert it to epoch)
    int64_t target_epoch = get_user_input();

    // Do BIS and print the results
    printf("Running search with BIS\n");
    start = clock();
    int result_bis = BIS(array, 0, array.count - 1, target_epoch);
    (result_bis == -1) ?
        printf("Measurement data for the specified timestamp does not exist.\n") :
        printf("Found measurement data for timestamp %s: %.2f\n", array.data[result_bis].timestamp, array.data[result_bis].value);
    end = clock();
    print_searching_time(start, end);

    // Do BIS_star and print the results
    printf("Running search with BIS*\n");
    start = clock();
    int result_bis_star = BIS_star(array, 0, array.count - 1, target_epoch);
    (result_bis_star == -1) ?
        printf("Measurement data for the specified timestamp does not exist.\n") :
        printf("Found measurement data for timestamp %s: %.2f\n", array.data[result_bis_star].timestamp, array.data[result_bis_star].value);
    end = clock();
    print_searching_time(start, end);

    return 0;
}

// Binary interpolation search functions
int BIS(MeasurementsArray arr, int left, int right, int64_t target_epoch) {
    // Check if the target date is within array bounds
    if (target_epoch > arr.data[right].time_epoch || target_epoch < arr.data[left].time_epoch)
        return -1;

    // Division by zero check
    if (arr.data[right].time_epoch == arr.data[left].time_epoch)
        return linear_search(arr, left, right, target_epoch);

    // Initial interpolation step
    int size = right - left;
    int next = (int)((size * (target_epoch - arr.data[left].time_epoch)) /
                (arr.data[right].time_epoch - arr.data[left].time_epoch)) + left;

    // Interpolation search
    while (target_epoch != arr.data[next].time_epoch) {
        int i = 0;
        size = right - left;
        
        // If the field of search is small enough, do linear search for simplicity
        if (size <= 3) {
            return linear_search(arr, left, right, target_epoch);
        }

        int step = (int)sqrt(size);
        if (target_epoch >= arr.data[next].time_epoch) {
            while (next + i * step < right && target_epoch > arr.data[next + i * step].time_epoch) {
                i++;
            }
            left = next + (i - 1) * step;
            right = next + i * step;
        } else {
            while (next - i * step > left && target_epoch < arr.data[next - i * step].time_epoch) {
                i++;
            }
            right = next - (i - 1) * step;
            left = next - i * step;
        }
        
        // Out of bounds checks for left and right
        if (left < 0) left = 0;
        if (right > arr.count - 1) right = arr.count - 1;

        // Division by zero check
        if (arr.data[right].time_epoch == arr.data[left].time_epoch)
            return linear_search(arr, left, right, target_epoch);

        // Interpolation step
        next = left + (int)(((right - left) * (target_epoch - arr.data[left].time_epoch)) /
                    (arr.data[right].time_epoch - arr.data[left].time_epoch));
        
        // Out of bounds checks for next
        if (next < left) next = left;
        if (next > right) next = right;
        
    }

    // Return the index if the timestamp was found
    if (target_epoch == arr.data[next].time_epoch)
        return next;

    return -1;
}

int BIS_star(MeasurementsArray arr, int left, int right, int64_t target_epoch) {
    // Check if the target date is within array bounds
    if (target_epoch > arr.data[right].time_epoch || target_epoch < arr.data[left].time_epoch)
        return -1;

    // Division by zero check
    if (arr.data[right].time_epoch == arr.data[left].time_epoch)
        return linear_search(arr, left, right, target_epoch);

    // Initial interpolation step
    int size = right - left;
    int next = (int)((size * (target_epoch - arr.data[left].time_epoch)) /
                (arr.data[right].time_epoch - arr.data[left].time_epoch)) + left;

    // Interpolation search
    while (target_epoch != arr.data[next].time_epoch) {
        int i = 1;
        size = right - left;
        
        // If the field of search is small enough, do linear search for simplicity
        if (size <= 3) {
            return linear_search(arr, left, right, target_epoch);
        }

        int step = (int)sqrt(size);
        if (target_epoch >= arr.data[next].time_epoch) {
            while (next + i * step < right && target_epoch > arr.data[next + i * step].time_epoch) {
                i *= 2;
            }
            left = next + (i / 2) * step;
            right = next + i * step;
        } else {
            while (next - i * step > left && target_epoch < arr.data[next - i * step].time_epoch) {
                i *= 2;
            }
            right = next - (i / 2) * step;
            left = next - i * step;
        }
        
        // Out of bounds checks for left and right
        if (left < 0) left = 0;
        if (right > arr.count - 1) right = arr.count - 1;

        // Division by zero check
        if (arr.data[right].time_epoch == arr.data[left].time_epoch)
            return linear_search(arr, left, right, target_epoch);

        // Interpolation step
        next = left + (int)(((right - left) * (target_epoch - arr.data[left].time_epoch)) /
                    (arr.data[right].time_epoch - arr.data[left].time_epoch));
        
        // Out of bounds checks for next
        if (next < left) next = left;
        if (next > right) next = right;
        
    }

    // Return the index if the timestamp was found
    if (target_epoch == arr.data[next].time_epoch)
        return next;

    return -1;
}

int linear_search(MeasurementsArray arr, int left, int right, int64_t target_epoch) {
    for (int i = left; i < right; ++i) {
        if (arr.data[i].time_epoch == target_epoch) {
            return i;
        }
    }
    return -1;
}

void print_searching_time(clock_t start, clock_t end) {
    printf("Search completed in %.6f seconds.\n", ((double)(end - start)) / CLOCKS_PER_SEC);
}

// User input functions
int64_t get_user_input(void) {    
    char timestamp[MAX_TIMESTAMP_LEN] = { 0 };

    // Read the timestamp from the user
    printf("Please input the timestamp to search for (YYYY-MM-DDTHH:MM:SS): ");
    if (scanf("%19s", timestamp) != 1) {
        printf("get_user_input: Error reading user input.\n");
        clear_stdin();
        return -1;
    }

    // Clear stdin
    clear_stdin();
    
    // Convert timestamp to epoch
    return timestamp_to_epoch(timestamp);

}

void clear_stdin(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Merge sort functions (Based on epoch time)
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
        if (leftArray[i].time_epoch <= rightArray[j].time_epoch)
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
    arrayPtr->data[newCount - 1].time_epoch = timestamp_to_epoch(timestamp);
    arrayPtr->data[newCount - 1].value = value;

    // Update the count
    arrayPtr->count = newCount;
}

int64_t timestamp_to_epoch(char* timestamp) {
    struct tm tm = { 0 };
    int year, mon, mday, hour, min, sec;
    
    if (sscanf(timestamp, "%4d-%2d-%2dT%2d:%2d:%2d",
               &year, &mon, &mday, &hour, &min, &sec) != 6) {
        return -1;
    }

    tm.tm_year = year - 1900;   // Year in tm structs start from 1900 (arbitrarily)
    tm.tm_mon = mon - 1;        // Month in tm structs needs to be 0-indexed 
    tm.tm_mday = mday;          // Fill up the day field
    tm.tm_hour = hour;          // Fill up the hour field
    tm.tm_min = min;            // Fill up the minutes field
    tm.tm_sec = sec;            // Fill up the seconds field
    tm.tm_isdst = -1;           // Let mktime() figure DST out based on system timezone configuration
    
    return (int64_t)mktime(&tm) - CUSTOM_EPOCH_OFFSET;
}

void print_measurements(MeasurementsArray array) {
    int i;

    if (array.count <= 0) {
        printf("print_measurements: Array is empty.\n");
        return;
    }

    printf("\nSaved measurement data:\n");
    for (i = 0; i < array.count; i++) {
        printf("%s (%lld): %.2f\n", array.data[i].timestamp, (long long)array.data[i].time_epoch, array.data[i].value);
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

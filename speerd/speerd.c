#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BILLION 1000000000L

int main() {
    const size_t bufferSize = 104857600; // 100 MB -- might consider increasing further for higher res
    volatile char* buffer; // Make volatile to prevent optimization
    struct timespec start, end;
    double write_time, read_time;
    volatile long sum = 0; // prevent optimization

    buffer = (volatile char*)malloc(bufferSize);
    if (buffer == NULL) {
        perror("Error allocating memory");
        return 1;
    }

    // Write to memory
    clock_gettime(CLOCK_MONOTONIC, &start);
    // Consider using a loop for buffer writing -- mimic actual usage
    for (size_t i = 0; i < bufferSize; i++) {
        buffer[i] = i % 256; // write pattern
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

     write_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / (double)BILLION;
    printf("Write time: %f seconds\n", write_time);
    printf("Write speed: %f MB/s\n", (bufferSize / (1024.0 * 1024.0)) / write_time);

    // Read from memory in blocks
    size_t blockSize = 4096; // 4 KB blocks
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (size_t i = 0; i < bufferSize; i += blockSize) {
        sum += buffer[i]; // Simple operation to prevent optimization
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    read_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / (double)BILLION;
    printf("Read time: %f seconds\n", read_time);
    printf("Read speed: %f MB/s\n", (bufferSize / (1024.0 * 1024.0)) / read_time);

    free((char*)buffer); // cast back to non-volatile
    printf("Sum: %ld\n", sum);
    return 0;
}
    

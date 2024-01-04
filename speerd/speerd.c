// this version works with gcc
// compile with -lrt

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BILLION 1000000000L

int main() {
    const size_t bufferSize = 104857600; // 100 MB
    char* buffer;
    struct timespec start, end;
    double write_time, read_time;
    long sum = 0; // Used to prevent read loop optimization

    buffer = (char*)malloc(bufferSize);
    if (buffer == NULL) {
        perror("Error allocating memory");
        return 1;
    }

    // Write to memory
    clock_gettime(CLOCK_MONOTONIC, &start);
    memset(buffer, 0, bufferSize);
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

    free(buffer);
    printf("Sum: %ld\n", sum); // Print sum to ensure the read loop is not optimized out
    return 0;
}

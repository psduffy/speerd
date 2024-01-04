// this version works with gcc
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main()
{
    char response; // not called in this version
    const int bufferSize = 104857600; // 100 MB
    char* buffer;
    clock_t start, end;
    double cpu_time_used;

    buffer = malloc(bufferSize);
    if (buffer == NULL)
    {
        perror("Error allocating memory");
        return 1;
    }

    // Write to mem

    start = clock();
    memset(buffer, 0, bufferSize); // zero out buffer (fill buffer with zeros)
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Write time: %f seconds\n", cpu_time_used);
    printf("Write speed: %f MB/s\n", bufferSize / (cpu_time_used * 1048576));

    // Simulate reading from mem

    volatile char temp; // volatile to prevent compiler optimizations
    start = clock();
    for (int i = 0; i < bufferSize; i++)
    {
        temp = buffer[i];
    }
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Read time: %f seconds\n", cpu_time_used);
    printf("Read speed: %f MB/s\n", bufferSize / (cpu_time_used * 1048576));

    free(buffer);
    return 0;

}

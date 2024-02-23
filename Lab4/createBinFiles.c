#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int main() {
    srand(time(NULL)); // Seed the random number generator

    // 1. Big File 
    FILE *fp_big = fopen("big_bin.bin", "wb"); 
    if (fp_big == NULL) {
        perror("Error creating big_binary.bin");
        return 1;
    }

    const int big_size = 1000000; // 1 million bytes (about 1MB)
    for (int i = 0; i < big_size; i++) {
        unsigned char random_byte = rand() % 256;  // Random value 0-255
        fwrite(&random_byte, sizeof(unsigned char), 1, fp_big);
    }
    fclose(fp_big); 

    // 2. Average File 
    FILE *fp_average = fopen("avg_bin.bin", "wb");
    if (fp_average == NULL) {
        perror("Error creating average_binary.bin");
        return 1;
    }

    const int average_size = 100000; // 100,000 bytes (about 100KB)
    for (int i = 0; i < average_size; i++) {
        unsigned char random_byte = rand() % 256;  
        fwrite(&random_byte, sizeof(unsigned char), 1, fp_average);
    }
    fclose(fp_average); 

    // 3. Small File
    FILE *fp_small = fopen("sm_bin.bin", "wb");
    if (fp_small == NULL) {
        perror("Error creating small_binary.bin");
        return 1;
    }

    const int small_size = 5000; // 5,000 bytes (about 5KB) 
    for (int i = 0; i < small_size; i++) {
        unsigned char random_byte = rand() % 256; 
        fwrite(&random_byte, sizeof(unsigned char), 1, fp_small);
    }
    fclose(fp_small); 

    printf("Binary files created successfully!\n");
    return 0;
}

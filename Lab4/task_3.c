#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h> 

#define BUF_SIZE 64

static char read_buffer[BUF_SIZE];
unsigned int bytesInReadBuffer = 0;
unsigned int readBufIndex = 0; 
int src_file;

static char write_buffer[BUF_SIZE];
unsigned int writeBufIndex = 0; 
int dest_file;

long fileSize = 0;

int buf_in() {

    // If buffer is empty, refill it
    if (bytesInReadBuffer == 0) {
        bytesInReadBuffer = read(src_file, read_buffer, BUF_SIZE);
        if (bytesInReadBuffer == 0) {
            return EOF;
        }
        readBufIndex = 0; 
    }

    bytesInReadBuffer--; // Decrement since we're consuming a byte
    return (unsigned char) read_buffer[readBufIndex++];  // Return and increment index
}

void buf_flush() {
    write(dest_file, write_buffer, writeBufIndex);
    writeBufIndex = 0;
}

void buf_out(char byte) {
    write_buffer[writeBufIndex++] = byte; 

    if (writeBufIndex == BUF_SIZE) {  // Buffer is full
        buf_flush(); // flush it
    }
}

void copyWithBuffer() {
    int byte;
    while ((byte = buf_in()) != EOF) {
        buf_out(byte);
        fileSize++;
    }   
    buf_flush();
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s \n", argv[0]);
        return 1;
    }
    
    src_file = open(argv[1], O_RDONLY);
    dest_file = open(argv[2], O_WRONLY);

    if (src_file == -1 || dest_file == -1) {
        perror("Error opening files");
        return 1;
    }

        clock_t start_time = clock();

        copyWithBuffer();

        float end_time = (float) clock() - (float) start_time;
        float result = ((end_time) / (float) CLOCKS_PER_SEC) * 1000; 
        printf("Buffer Excution \n");
        printf("Executed in: %f ms, average time excution per byte: %f ms \n", result, result / (float) fileSize);

    close(src_file);
    close(dest_file);
    
    return 0;
}
#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>

#define BUF_SIZE 16
static char buffer[BUF_SIZE];
unsigned int bufIndex = 0; 
int filename;

void buf_flush() {
    write(filename, buffer, bufIndex);
    bufIndex = 0;
}

void buf_out(char byte) {
    buffer[bufIndex++] = byte; 

    if (bufIndex == BUF_SIZE) {  // Buffer is full
        write(filename, buffer, BUF_SIZE); 
        bufIndex = 0; // Reset buffer index
    }
}

void setFileContent(char *string) {
    for (int i = 0; string[i] != 0; i++) {
        buf_out(string[i]);
    }
    buf_flush(); // Flushing anything left in the array
}


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s \n", argv[0]);
        return 1;
    }

    filename = open(argv[1], O_WRONLY);
    if (filename == -1) {
        perror("Error opening file");
        return 1;
    }

    setFileContent("Testing to copy from src");
    close(filename);
    
    return 0;
}
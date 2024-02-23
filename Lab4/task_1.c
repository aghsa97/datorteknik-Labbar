#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>

#define BUF_SIZE 16
static char buffer[BUF_SIZE];
unsigned int bytesInBuffer = 0;

int buf_in(int filename) {
    static int bufIndex = 0;      

    // If buffer is empty, refill it
    if (bytesInBuffer == 0) {
        bytesInBuffer = read(filename, buffer, BUF_SIZE);
        if (bytesInBuffer == 0) {
            return EOF;
        }
        bufIndex = 0; 
    }

    bytesInBuffer--; // Decrement since we're consuming a byte
    return buffer[bufIndex++];  // Return and increment index
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \n", argv[0]);
        return 1;
    }


    int filename = open(argv[1], O_RDONLY);
    if (filename == -1) {
        perror("Error opening file");
        return 1;
    }

    int byte;
    while ((byte = buf_in(filename)) != EOF) {
        printf("%c", byte); 
    }  

    close(filename);

    printf("\n"); 

    return 0;
}

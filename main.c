#include <stdio.h>    // For standard I/O operations like printf, fopen, fclose, perror
#include <stdlib.h>   // For malloc, free, exit
#include <fcntl.h>    // For open (file control options)
#include <unistd.h>   // For close, read

// This is the prototype for your get_next_line function.
// You will need to ensure your get_next_line.h header (or similar)
// is correctly included and linked during compilation.
// For simplicity here, we're declaring it directly.
char *get_next_line(int fd);

int main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     line_count = 0;

    // Check if a file name was provided as a command-line argument
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        fprintf(stderr, "Example: %s test.txt\n", argv[0]);
        return (1); // Exit with an error code
    }

    // Open the file specified by the first command-line argument
    // O_RDONLY: Open for reading only
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file"); // Print an error message if file opening fails
        return (1); // Exit with an error code
    }

    printf("--- Reading from file: %s ---\n", argv[1]);

    // Loop to read lines until get_next_line returns NULL (end of file or error)
    while ((line = get_next_line(fd)) != NULL)
    {
        line_count++;
        // Print the line along with its line number
        printf("[%03d] %s", line_count, line);
        // Important: Free the memory allocated by get_next_line for the line
        free(line);
        line = NULL; // Set to NULL after freeing to prevent use-after-free
    }

    // Close the file descriptor
    if (close(fd) == -1)
    {
        perror("Error closing file"); // Print an error if closing fails
        return (1); // Exit with an error code
    }

    printf("--- End of file ---\n");
    return (0); // Exit successfully
}

/*
// Dummy get_next_line for compilation if you don't have it yet.
// REMOVE THIS AND LINK YOUR ACTUAL get_next_line.o WHEN COMPILING.
// This dummy function will only return NULL.
char *get_next_line(int fd)
{
    (void)fd; // Suppress unused parameter warning
    return (NULL);
}
*/


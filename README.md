# get_next_line
*This project has been created as part of the 42 curriculum by ssaghate.*

---

## Description

**get_next_line** is a function that reads a file descriptor line by line.

The objective of this project is to implement a function that returns one line at a time from a file descriptor, regardless of the chosen `BUFFER_SIZE`. A line is defined as a sequence of characters ending with a newline character (`\n`) or by the end of file (EOF).

This project strengthens understanding of:

- Static variables
- File descriptors and the `read` system call
- Dynamic memory allocation
- Buffer management
- String manipulation
- Edge case handling

Function prototype:

```c
char *get_next_line(int fd);
```

Each call to `get_next_line()` returns:

- The next line including the newline (`\n`) if present
- `NULL` when there is nothing more to read or if an error occurs

---

## Project Goal

- Read and return one line at a time from a file descriptor.
- Handle any valid `BUFFER_SIZE`.
- Work correctly with files, standard input, and pipes.
- Prevent memory leaks.
- Respect 42 Norm and compilation rules.

---

## Instructions

### Usage Example:

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

### Compilation:
Compile manually without a Makefile:

```
cc -Wall -Wextra -Werror main.c get_next_line.c get_next_line_utils.c -o gnl_test
```

## Algorithm Explanation & Justification

### Selected Algorithm: Persistent Static Buffer

The implementation relies on a **static variable** that stores unread data between function calls.

### How It Works

1. A static pointer keeps leftover data from previous reads.
2. The function reads from the file descriptor into a temporary buffer of size `BUFFER_SIZE`.
3. The read content is appended to the static storage.
4. Reading continues until a newline (`\n`) is found or EOF is reached.
5. The first complete line is extracted and returned.
6. The remaining data is kept in the static storage for the next call.

### Why This Approach?

- Prevents data loss between function calls.
- Handles partial reads correctly.
- Works for any `BUFFER_SIZE`.
- Minimizes unnecessary system calls.
- Ensures efficient memory usage.

Each byte is processed only once, making the solution efficient in both time and space complexity.

---

## Edge Cases Handled

- `fd < 0`
- `BUFFER_SIZE <= 0`
- Empty files
- Files without newline at EOF
- Large files
- Very small `BUFFER_SIZE`
- Read errors

---

## Allowed Functions

- `read`
- `malloc`
- `free`

---

## Resources

- `man 2 read`
- GNU C Library documentation
- 42 intranet Libft subject
- google search resources
- peer on the right peer on the left and someone smart in the building
- AI tools were used only for reviewing code for potential issues.
- AI was used to fix the files that had too much norminette errors also for README

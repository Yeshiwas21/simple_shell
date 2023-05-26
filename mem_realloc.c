#include "shell.h"

/**
 * reassign_lineptr - Reassigns the lineptr variable for _getline.
 * @lineptr: A buffer to store an input string.
 * @n: The size of lineptr.
 * @buffer: The string to assign to lineptr.
 * @bufferSize: The size of buffer.
 */
void reassign_lineptr(char **lineptr, size_t *n, char *buffer, size_t bufferSize)
{
    if (*lineptr == NULL || *n < bufferSize)
    {
        if (bufferSize > 120)
            *n = bufferSize;
        else
            *n = 120;
        *lineptr = buffer;
    }
    else
    {
        _strcpy(*lineptr, buffer);
        free(buffer);
    }
}

/**
 * mem_realloc - Reallocates a memory block using malloc and free.
 * @ptr: A pointer to the memory previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new memory block.
 *
 * Return: ptr - if new_size == old_size - .
 *         NULL - if new_size == 0 and ptr is not NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *mem_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *mem;
    char *ptr_copy, *filler;
    unsigned int i = 0;

    if (new_size == old_size)
        return ptr;

    if (ptr == NULL)
    {
        mem = malloc(new_size);
        if (mem == NULL)
            return NULL;

        return mem;
    }

    if (new_size == 0 && ptr != NULL)
    {
        free(ptr);
        return NULL;
    }

    ptr_copy = ptr;
    mem = malloc(new_size);
    if (mem == NULL)
    {
        free(ptr);
        return NULL;
    }

    filler = mem;
    while (i < old_size && i < new_size)
    {
        filler[i] = ptr_copy[i];
        i++;
    }

    free(ptr);
    return mem;
}
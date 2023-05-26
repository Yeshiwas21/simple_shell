#include "shell.h"

/**
 * read_input - Reads user's input from a stream
 * @input_buff: A buffer to store input
 * @size: The size of input_buff
 * @strm: The stream to be read from
 *
 * Return: The number of bytes read.
 */
ssize_t read_input(char **output_buffer, size_t *output_size, FILE *stream)
{
    static ssize_t input_counter = 0;
    ssize_t ret_value = -1;
    char current_char = 'x';
    char *buffer = NULL;
    size_t buffer_size = 120;
    size_t new_buffer_size;
    ssize_t read_result;

    if (input_counter == 0)
        fflush(stream);
    else
        return -1;

    buffer = malloc(sizeof(char) * buffer_size);
    if (!buffer)
        return -1;

    while (current_char != '\n')
    {
        read_result = read(STDIN_FILENO, &current_char, 1);
        if (read_result == -1 || (read_result == 0 && input_counter == 0))
        {
            free(buffer);
            return -1;
        }
        if (read_result == 0 && input_counter != 0)
        {
            input_counter++;
            break;
        }

        if ((size_t)input_counter >= buffer_size)
        {
            char *new_buffer;
            new_buffer_size = buffer_size + 1;
            new_buffer = mem_realloc(buffer, buffer_size, new_buffer_size);
            if (new_buffer == NULL)
            {
                free(buffer);
                return -1;
            }
            buffer = new_buffer;
            buffer_size = new_buffer_size;
        }

        buffer[input_counter] = current_char;
        input_counter++;
    }
    buffer[input_counter] = '\0';

    reassign_lineptr(output_buffer, output_size, buffer, input_counter);

    ret_value = input_counter;
    if (read_result != 0)
        input_counter = 0;
    return ret_value;
}
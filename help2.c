#include "shell.h"

/**
 * handles_line - Partitions a line read from standard input.
 * @line_read: A pointer to a line read from standard input.
 * @read_length: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handles_line(char **line_read, ssize_t read_length)
{
	char *old_line, *new_line;
	char curr, prev, next;
	size_t i, j;
	ssize_t new_length;

	new_length = get_new_length(*line_read);
	if (new_length == read_length - 1)
		return;
	new_line = malloc(new_length + 1);
	if (!new_line)
		return;
	j = 0;
	old_line = *line_read;
	for (i = 0; old_line[i]; i++)
	{
		curr = old_line[i];
		next = old_line[i + 1];
		if (i != 0)
		{
			prev = old_line[i - 1];
			if (curr == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (prev != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (curr == '&')
			{
				if (next == '&' && prev != ' ')
					new_line[j++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (curr == '|')
			{
				if (next == '|' && prev != ' ')
					new_line[j++] = ' ';
				else if (prev == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (curr == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next != ' ' && next != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';

	free(*line_read);
	*line_read = new_line;
}

/**
 * get_new_length - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_length(char *line)
{
	size_t i;
	ssize_t new_length = 0;
	char curr, next;

	for (i = 0; line[i]; i++)
	{
		curr = line[i];
		next = line[i + 1];
		if (curr == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (curr == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_length += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					new_length += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_length++;
				if (next != ' ')
					new_length++;
			}
			else
				update_logical_ops(&line[i], &new_length);
		}
		else if (curr == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_length++;
			if (next != ' ' && next != ';')
				new_length++;
		}
		new_length++;
	}
	return new_length;
}
/**
 * update_logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_length: Pointer to new_len in get_new_len function.
 */
void update_logical_ops(char *line, ssize_t *new_length)
{
	char prev, curr, next;

	prev = *(line - 1);
	curr = *line;
	next = *(line + 1);

	if (curr == '&')
	{
		if (next == '&' && prev != ' ')
			(*new_length)++;
		else if (prev == '&' && next != ' ')
			(*new_length)++;
	}
	else if (curr == '|')
	{
		if (next == '|' && prev != ' ')
			(*new_length)++;
		else if (prev == '|' && next != ' ')
			(*new_length)++;
	}
}

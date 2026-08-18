#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * file_error - prints a file error and exits
 * @code: exit code
 * @filename: name of the file
 */
static void file_error(int code, const char *filename)
{
	if (code == 98)
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", filename);
	else
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", filename);

	exit(code);
}

/**
 * close_file - closes a file descriptor
 * @fd: file descriptor to close
 */
static void close_file(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * copy_content - copies data between two file descriptors
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @file_from: source filename
 * @file_to: destination filename
 */
static void copy_content(int fd_from, int fd_to,
	const char *file_from, const char *file_to)
{
	char buffer[1024];
	ssize_t bytes_read;
	ssize_t bytes_written;

	while ((bytes_read = read(fd_from, buffer, 1024)) > 0)
	{
		bytes_written = write(fd_to, buffer, bytes_read);
		if (bytes_written != bytes_read)
			file_error(99, file_to);
	}

	if (bytes_read == -1)
		file_error(98, file_from);
}

/**
 * main - copies the content of one file to another
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: Always 0 on success
 */
int main(int argc, char **argv)
{
	int fd_from;
	int fd_to;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		file_error(98, argv[1]);

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
		file_error(99, argv[2]);

	copy_content(fd_from, fd_to, argv[1], argv[2]);
	close_file(fd_from);
	close_file(fd_to);

	return (0);
}

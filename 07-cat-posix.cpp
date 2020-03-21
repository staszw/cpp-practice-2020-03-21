#include <cstdlib>
#include <iostream>
#include <iterator>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "usage: " << argv[0] << " <filename>\n";
		return EXIT_FAILURE;
	}
	
	int fd = open(argv[1], O_RDONLY | O_CLOEXEC);
	if (fd < 0)
	{
		perror("open failed");
		return EXIT_FAILURE;
	}

	for (;;)
	{
		char buffer[8192];
		ssize_t bytes_read = read(fd, buffer, std::size(buffer));

		if (bytes_read < 0)
		{
			perror("read failed");
			close(fd);
			return EXIT_FAILURE;
		}

		if (bytes_read == 0)
			break;

		ssize_t bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
		if (bytes_written < 0)
		{
			perror("write failed");
			close(fd);
			return EXIT_FAILURE;
		}
	}

	close(fd);
	return EXIT_SUCCESS;
}

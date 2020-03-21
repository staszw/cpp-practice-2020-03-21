#include <cstdlib>
#include <iostream>
#include <iterator>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "usage: " << argv[0] << " <filename>\n";
		return EXIT_FAILURE;
	}
	
	FILE* f = fopen(argv[1], "r");
	if (!f)
	{
		perror("fopen failed");
		return EXIT_FAILURE;
	}

	for (;;)
	{
		char buffer[8192];
		size_t bytes_read = fread(buffer, sizeof(char), std::size(buffer), f);

		if (bytes_read == 0)
		{
			if (ferror(f))
			{
				perror("fread failed");
				fclose(f);
				return EXIT_FAILURE;
			}

			break;
		}

		size_t bytes_written = fwrite(buffer, sizeof(char), bytes_read, stdout);
		if (bytes_written == 0)
		{
			perror("fwrite failed");
			fclose(f);
			return EXIT_FAILURE;
		}
	}

	fclose(f);
	return EXIT_SUCCESS;
}

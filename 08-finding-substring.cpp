#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "usage: " << argv[0] << " <substring> <filename>\n";
		return EXIT_FAILURE;
	}
	const char* s = argv[1];
	const char* file_name = argv[2];
	FILE* f = fopen(file_name, "r");
	if (!f) {
		perror("fopen failed");
		return EXIT_FAILURE;
	}
	const int size = strlen(s);


	std::vector<int> prefix_function(size);
	prefix_function[0] = 0;
	for (int i = 1; i < size; i++) {
		int res = prefix_function[i - 1];
		while (res > 0 && s[i] != s[res]) {
			res = prefix_function[res - 1];
		}
		if (s[i] == s[res]) {
			res++;
		}
		prefix_function[i] = res;
	}


	char c;
	int current_length = 0;
	while (fscanf(f, "%c", &c) != EOF) {
		while (current_length > 0 && s[current_length] != c) {
			current_length = prefix_function[current_length - 1];
		}
		if (s[current_length] == c) {
			current_length++;
		}
		if (current_length == size) {
			printf("true\n");
			return 0;
		}
	}
	printf("false\n");
	return 0;
}

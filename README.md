# huffman-coding
ASCII Text Compression Using Huffman Coding

# Features
- Fast Text Compression Using Huffman 

# Installation
No Installation Is Needed. Just Clone And Compile.

# Compilation
Open Solution And Build.

# Usage
```C++
#include "Huffman.h"

int main() {
	
	using namespace huffman;
	Huffman huffman;

	std::string filename;
	std::cout << "Enter File Name: ";
	std::cin >> filename; 

	if (!huffman.Input(filename))
		return -1;

	huffman.Encode("Encoded.bin");
	huffman.Decode("Decoded.txt");

	return 0;
}
```

# Dependencies
No Dependencies

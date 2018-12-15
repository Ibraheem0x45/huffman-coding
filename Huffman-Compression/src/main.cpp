#include <iostream>
#include <chrono>

#include "Huffman.h"

int main() {
	
	using namespace huffman;
	Huffman huffman;

	std::string filename;
	std::cout << "Enter File Name: ";
	std::cin >> filename; 

	auto start = std::chrono::steady_clock::now();

	std::cout << "\n----- Building Huffman Tree -----" << std::endl << std::endl;
	if (!huffman.Input(filename))
		return -1;

	std::cout << "----- Encoding -----" << std::endl << std::endl;
	huffman.Encode("Encoded.bin");

	std::cout << "----- Decoding -----" << std::endl << std::endl;
	huffman.Decode("Decoded.txt");

	auto end = std::chrono::steady_clock::now();
	auto time = end - start;
	std::cout << "Time Taken: "
			  << std::chrono::duration <double, std::milli>(time).count() << " ms: "
			  << std::chrono::duration <double, std::milli>(time).count() / 1000.0f << " s" << std::endl;

	std::cin.ignore();
	std::cin.get();
	return 0;
}
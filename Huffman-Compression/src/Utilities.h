#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include "Types.h"

namespace huffman { namespace util {

#define BYTE_SIZE		8
#define HUFFMAN_EOF		3
#define DUMMY_SYMBOL	0

	struct Compare {

	public:
		bool operator()(Node<uint, byte>* A, Node<uint, byte>* B) const { return (*A) > (*B); }
	};

	static bool LoadFile(const std::string& filename, std::vector<byte>& buffer) {

		FILE* file;

		fopen_s(&file, filename.c_str(), "rb");

		if (!file)
			return false;

		fseek(file, 0, SEEK_END);

		std::size_t length = ftell(file);
		buffer.resize(length + 1);

		fseek(file, 0, SEEK_SET);
		fread(&(buffer[0]), sizeof(byte), length, file);
		buffer[buffer.size() - 1] = HUFFMAN_EOF;
		fclose(file);

		return true;
	}

	static bool WriteFile(const std::string& filename, const std::vector<byte>& buffer) {

		FILE* file;

		fopen_s(&file, filename.c_str(), "wb");

		if(!file)
			return false;

		fwrite(&buffer[0], sizeof(byte), buffer.size(), file);
		fclose(file);

		return true;
	}
} }
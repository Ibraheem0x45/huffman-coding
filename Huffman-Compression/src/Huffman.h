#pragma once

#include "HuffmanTree.h"

namespace huffman {

	class Huffman {

	private:
		std::vector<byte> m_Buffer;
		std::string	m_EncodedFile;
		HuffmanTree	m_Tree;

	public:
		Huffman() = default;
		~Huffman() = default;

		bool Input(const std::string& filename);

		void Encode(const std::string& filename);
		void Decode(const std::string& filename);

	};
}
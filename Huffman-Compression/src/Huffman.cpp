#include "Huffman.h"

namespace huffman {

	bool Huffman::Input(const std::string& filename) {

		std::unordered_map<byte, uint> cache;
		
		if (!util::LoadFile(filename, m_Buffer))
			return false;

		for (std::size_t i = 0; i < m_Buffer.size(); i++) {

			if (cache.find(m_Buffer[i]) != cache.end())
				cache[m_Buffer[i]] += 1;
			else
				cache[m_Buffer[i]] = 1;
		}

		for (auto it = cache.cbegin(); it != cache.cend(); it++) {

			auto& data = *it;
			m_Tree.Insert(new Node<uint, byte>(data.second, data.first));
		}

		m_Tree.BuildTree();
		return true;
	}

	void Huffman::Encode(const std::string& filename) {
		
		m_Tree.PushCode();

		auto cache = m_Tree.GetCodes();

		byte chunk = 0;

		std::vector<byte> packed;
		packed.reserve(m_Buffer.size());

		for (std::size_t i = 0, count = 0; i < m_Buffer.size(); i++) {

			byte character = m_Buffer[i];

			const std::string& code = cache[character];

			for (std::size_t j = 0; j < code.length(); j++) {

				if (count >= BYTE_SIZE) {

					packed.push_back(chunk);
					count = 0;
					chunk = 0;
				}

				if (code[j] - 0x30)
					chunk |= (0x80 >> count);
				count++;
			}
		}

		packed.push_back(chunk);
		util::WriteFile(m_EncodedFile = filename, packed);
	}

	void Huffman::Decode(const std::string& filename) {

		byte chunk;
		std::vector<byte> packed;

		if (!util::LoadFile(m_EncodedFile, packed))
			return;

		std::vector<byte> unPacked;
		unPacked.reserve(packed.size());

		std::size_t count = 0;
		std::size_t i = 0;

		chunk = packed[i];

		while (i < packed.size()) {

			HuffmanNode* root = m_Tree.GetRoot();

			while (root->left && root->right) {

				if (count >= BYTE_SIZE) {

					chunk = packed[++i];
					count = 0;
				}

				byte bit = chunk & (0x80 >> count++);

				if (bit)
					root = root->right;
				else
					root = root->left;
			}

			if (root->key == HUFFMAN_EOF)
				break;
			unPacked.push_back(root->key);
		}

		util::WriteFile(filename, unPacked);
	}
}
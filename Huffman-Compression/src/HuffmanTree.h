#pragma once
#include <unordered_map>
#include <vector>
#include <queue>

#include "Node.h"
#include "Utilities.h"

namespace huffman {

	typedef Node<uint, byte> HuffmanNode;

	class HuffmanTree {

	private:
		std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, util::Compare> m_Tree;
		std::unordered_map<byte, std::string> m_Cache;

	public:
		HuffmanTree() = default;
		~HuffmanTree();

		void BuildTree();
		void Insert(HuffmanNode* node);

		void Decode(const std::string& filename, const std::string& encodedFile);

		void PushCode();

		inline HuffmanNode* GetRoot() const { return m_Tree.top(); }
		inline const std::unordered_map<byte, std::string>& GetCodes() const { return m_Cache; }

	private:
		void DeleteTree(HuffmanNode* root);

		void PushCode(HuffmanNode* root, std::string code);
	};
}
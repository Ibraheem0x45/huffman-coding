#include "HuffmanTree.h"

namespace huffman {

	HuffmanTree::~HuffmanTree() {
		
		if(!m_Tree.empty())
			DeleteTree(m_Tree.top());
	}

	void HuffmanTree::BuildTree() {

		while (m_Tree.size() > 1) { 

			HuffmanNode* rightChild = m_Tree.top(); 
			m_Tree.pop();

			HuffmanNode* leftChild = m_Tree.top();
			m_Tree.pop();
	
			m_Tree.push(new HuffmanNode(*(*rightChild) + *(*leftChild), DUMMY_SYMBOL, leftChild, rightChild));
		}
	}

	void HuffmanTree::Insert(HuffmanNode* node) {
		
		m_Tree.push(node);
	}

	void HuffmanTree::Decode(const std::string& filename, const std::string& encodedFile) {

		byte chunk;
		std::vector<byte> packed;

		if (!util::LoadFile(encodedFile, packed))
			return;

		std::vector<byte> unPacked;
		unPacked.reserve(packed.size());

		std::size_t count = 0;
		std::size_t i = 0;

		chunk = packed[i];

		while (i < packed.size()) {

			HuffmanNode* root = m_Tree.top();

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

	void HuffmanTree::DeleteTree(HuffmanNode* root) {

		if (!root)
			return;

		DeleteTree(root->left);
		DeleteTree(root->right);

		delete root;
	}

	void HuffmanTree::PushCode() {

		std::string code;
		PushCode(m_Tree.top(), code);
	}

	void HuffmanTree::PushCode(HuffmanNode* root, std::string code) { 
		
		if (!root)
			return;

		if (!root->left && !root->right)
			m_Cache[root->key] = code;
		
		PushCode(root->left,  code + "0");
		PushCode(root->right, code + "1");
	}
}
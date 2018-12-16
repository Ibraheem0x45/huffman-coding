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

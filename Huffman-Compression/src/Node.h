#pragma once

namespace huffman {

	template <typename T, typename K>
	struct Node {

		T data;
		K key;

		Node<T, K>* left;
		Node<T, K>* right;

		Node();
		Node(T data, K key);
		Node(T data, K key, Node* left, Node* right);

		T operator*() const { return data; }

		inline bool operator<(const Node& right) const { return data < right.data; }
		inline bool operator>(const Node& right) const { return data > right.data; }
	};

	template <typename T, typename K>
	Node<T, K>::Node()
		: left(nullptr), right(nullptr) {}

	template <typename T, typename K>
	Node<T, K>::Node(T data, K key)
		: data(data), key(key), left(nullptr), right(nullptr) {}

	template <typename T, typename K>
	Node<T, K>::Node(T data, K key, Node* left, Node* right)
		: data(data), key(key), left(left), right(right) {}
}

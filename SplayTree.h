#include<iostream>
using namespace std;
#ifndef SPLAY_TREE
#define SPLAY_TREE
template<class T>
class SplayTree {
private:
	int size;
	class Node
	{
	private:
		T data;
		int key;
		Node* leftChild;
		Node* rightChild;
	public:
		Node(T data, Node* leftChild = NULL, Node* rightChild = NULL)
		{
			this->key = size + 1;
			this->data = data;
			this->leftChild = leftChild;
			this->rightChild = rightChild;
		}
		friend class Splaytree;
	};
	//Root for the tree
	Node* root;
	Node* rightRotation(Node* root)
	{
		Node* y = root->leftChild;
		root->leftChild = y->rightChild;
		y->rightChild = root;
		return y;
	}
	Node* leftRotation(Node* root)
	{
		Node* y = root->rightChild;
		root->rightChild = y->leftChild;
		y->leftChild = root;
		return y;
	}
	void splay(Node* &root, int key)
	{
		this->key = key;
		if (!root || root->key == this->key)
			return;
		if (root->key > this->key)
		{
			if (!root->leftChild)
				this->key = root->key;
			splay(root->leftChild, this->key);
		}
		else if (root->key < this->key)
		{
			if (!root->rightChild)
				this->key = root->key;
			splay(root->rightChild, this->key);
		}
		if (root == this->root)
		{
			if (root->leftChild && root->leftChild->key == this->key)
				root = rightRotation(root);
			else if (root->rightChild && root->rightChild->key == this->key)
				root = leftRotation(root);
		}
		if (root->leftChild !=NULL && root->leftChild->leftChild !=NULL && root->leftChild->leftChild->key == this->key)
		{
			root = rightRotation(root);
			root = rightRotation(root);
		}
		else if (root->leftChild!=NULL && root->leftChild->rightChild!=NULL && root->leftChild->rightChild->key == this->key)
		{
			root->leftChild = leftRotation(root->leftChild);
			root = rightRotation(root);
		}
		else if (root->rightChild!=NULL && root->rightChild->leftChild!=NULL && root->rightChild->leftChild->key == this->key)
		{
			root->rightChild = rightRotation(root->rightChild);
			root = leftRotation(root);
		}
		else if (root->rightChild!=NULL && root->rightChild->rightChild!=NULL &&root->rightChild->rightChild->key == this->key)
		{
			root = leftRotation(root);
			root = leftRotation(root);
		}
	}
	void Add(T data ,int key,Node* &root)
	{
		if (!root)
		{
			root = new Node(data);
			splay(this->root, root->key);
			return;
		}
		if (root->key > key)
			Add(data, key, root->leftChild);
		else
			Add(data ,key, root->rightChild);
	}
	void Print(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		cout << root->key << " ";
		Print(root->leftChild);
		Print(root->rightChild);
	}
public:
	Splaytree()
	{
		size = 0;
		root = NULL;
	}
	int key(T data, Node* a = this->root)
	{
		if(!a) return -1;
		if(a->data == data) return a->key;
		key(data, a->leftChild) >= 0 ? return key(data, a->leftChild) : return key(data, a -> rightChild);
	}
	void add(T data, int key = this->size + 1)
	{
		Add(data,this->root);
		this->size++;
	}
	int size()
	{
		return this->size;
	}
	void remove(int key)
	{
		this->splay(this->root, key);
		if (this->root->key != key)
		{
			cout << "Not found" << endl;
			return;
		}
		Node* left = this->root->leftChild;
		Node* right = this->root->rightChild;
		delete(this->root);
		if (!left) root = right;
		else
		{
			this->root = left;
			Node* a = left;
			while (a->rightChild)
			{
				a = a->rightChild;
			}
			splay(root, a->key);
			root->rightChild = right;
		}
		this->size--;
	}
	void print()
	{
		Print(root);
	}
};
#endif
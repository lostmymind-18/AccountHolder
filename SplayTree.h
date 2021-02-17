#ifndef SPLAY_TREE
#define SPLAY_TREE
template<class T>
class SplayTree {
private:
	int count;
	class Node
	{
	private:
		T data;
		int key;
		Node* leftChild;
		Node* rightChild;
	public:
		//Constructor
		Node(){}
		Node(T data, SplayTree* tree , Node* leftChild = NULL, Node* rightChild = NULL)
		{
			this->key = tree->count + 1;
			this->data = data;
			this->leftChild = leftChild;
			this->rightChild = rightChild;
		}
	};
	//Root for the tree
private:
	Node* root;
	int recentKey = 0;
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
		this->recentKey = key;
		if (!root || root->key == this->recentKey)
			return;
		if (root->key > this->recentKey)
		{
			if (!root->leftChild)
				this->recentKey = root->key;
			splay(root->leftChild, this->recentKey);
		}
		else if (root->key < this->recentKey)
		{
			if (!root->rightChild)
				this->recentKey = root->key;
			splay(root->rightChild, this->recentKey);
		}
		if (root == this->root)
		{
			if (root->leftChild && root->leftChild->key == this->recentKey)
				root = rightRotation(root);
			else if (root->rightChild && root->rightChild->key == this->recentKey)
				root = leftRotation(root);
		}
		if (root->leftChild !=NULL && root->leftChild->leftChild !=NULL && root->leftChild->leftChild->key == this->recentKey)
		{
			root = rightRotation(root);
			root = rightRotation(root);
		}
		else if (root->leftChild!=NULL && root->leftChild->rightChild!=NULL && root->leftChild->rightChild->key == this->recentKey)
		{
			root->leftChild = leftRotation(root->leftChild);
			root = rightRotation(root);
		}
		else if (root->rightChild!=NULL && root->rightChild->leftChild!=NULL && root->rightChild->leftChild->key == this->recentKey)
		{
			root->rightChild = rightRotation(root->rightChild);
			root = leftRotation(root);
		}
		else if (root->rightChild!=NULL && root->rightChild->rightChild!=NULL &&root->rightChild->rightChild->key == this->recentKey)
		{
			root = leftRotation(root);
			root = leftRotation(root);
		}
	}
	void Add(T data ,int key,Node* &root)
	{
		if (!root)
		{
			root = new Node(data, this);
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
	//check if data's already exist or not
public:
	SplayTree()
	{
		count = 0;
		root = NULL;
	}
	int key(T data, Node* a = NULL)
	{
		if(!a) a = this->root;
		if(!a) return -1;
		if(a->data == data) return a->key;
		if (key(data, a->leftChild) >= 0) return key(data, a->leftChild);
		else return key(data, a -> rightChild);
	}
	void add(T data)
	{
		int key = this->count + 1;
		Add(data, key, this->root);
		this->count++;
	}
	int size()
	{
		return this->count;
	}
	T* search(int key, Node* root = NULL)
	{
		if(!root) throw"Not found";
		if(root->key == key)
		{
			splay(this->root, key);
			return &root->data;
		}
		if(key > root->key) return search(key, root->rightChild);
		if(key < root->key) return search(key, root->leftChild);
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
		this->count--;
	}
	void print()
	{
		Print(root);
	}
};
#endif
#include <iostream>
#include <windows.h>
using namespace std;

struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;

	int key = {};
};

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

class BinarySearchTree
{
public:
	void Print() { Print(_root, 10, 0); };
	void Print(Node* node, int x, int y)
	{
		if (node == nullptr)
			return;

		SetCursorPosition(x, y);

		cout << node->key << endl;
		Print(node->left, x - (5 / (y + 1)), y + 1);
		Print(node->right, x + (5 / (y + 1)), y + 1);
	}

	void Insert(int key)
	{
		Node* newNode = new Node;
		newNode->key = key;

		if (_root == nullptr)
		{
			_root = newNode;
			return;
		}

		Node* node = _root;
		Node* parent = nullptr;

		while (node)
		{
			parent = node;

			if (key < node->key)
				node = node->left;
			else
				node = node->right;
		}

		newNode->parent = parent;

		if (key < parent->key)
			parent->left = newNode;
		else
			parent->right = newNode;

	}

	void Delete(int key)
	{
		Node* deleteNode = Search(_root, key);
		Delete(deleteNode);
	}
	void Delete(Node* node)
	{
		if (node == nullptr)
			return;

		if (node->left == nullptr)
			Replace(node, node->right);
		else if (node->right == nullptr)
			Replace(node, node->left);
		else
		{
			// 다음 데이터 찾기
			Node* next = Next(node);
			node->key = next->key;
			Delete(next);
		}
	}
	// u서브트리를 v서브트리로 교체
	// 그리고 delete u
	void Replace(Node* u, Node* v)
	{
		if (u->parent == nullptr)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;

		if (v)
			v->parent = u->parent;

		delete u;
	}

	void Print_Inorder() { Print_Inorder(_root); }
	void Print_Inorder(Node* node)
	{
		// 저위 순회 (preorder traverse)
		// 중위 순회 (inorder traverse)
		// 후위 순회 (postorder traverse)

		// 전위 : [중]이 앞에 온다
		// 중위 : [중]이 중간에 온다
		// 후위 : [중]이 마지막에 온다
		if (node == nullptr) return;
		cout << node->key << endl;
		Print_Inorder(node->left);
		Print_Inorder(node->right);
	}

	Node* Search(Node* node, int key) 
	{
		while (node && key != node->key)
		{
			if (key < node->key)
				node = node->left;
			else
				node = node->right;
		}
		return node;
	}

	Node* Min(Node* node)
	{
		while (node->left)
			node = node->left;
		return node;
	}
	Node* Max(Node* node)
	{
		while (node->right)
			node = node->right;
		return node;
	}
	Node* Next(Node* node)
	{
		if (node->right)
			return Min(node->right);

		Node* parent = node->parent;

		while (parent && node == parent->right)
		{
			node = parent;
			parent = parent->parent;
		}

		return parent;
	}

	Node* GetRoot() { return _root; };
private:
	Node* _root = nullptr;
};

int main()
{
	BinarySearchTree bst;

	bst.Insert(20);
	bst.Insert(10);
	bst.Insert(18);
	bst.Insert(8);
	bst.Insert(19);

	
	cout << bst.Next(bst.GetRoot())->key << endl;

	//bst.Delete(20);
	//bst.Delete(40);

	bst.Print();
}
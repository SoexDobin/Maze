#include <iostream>
#include <windows.h>
#include <thread>
using namespace std;

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

enum class Color
{
	Red = 0,
	Black = 1,
};

struct Node
{
	Color color = Color::Black;
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
void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}

void ShowConsoleCursor(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorInfo);
}


// Red-Black Tree
// 1) 모든 노드는 Red or Black
// 2) Root는 Black
// 3) Leaf(NIL)는 블랙
// 4) Red 노드의 자식은 Black (연속 Red X)
// 5) 각 노드로부터 - 리프까지 가는 경로들은 모두 같은 수의 Black 노드를 만남

class BinarySearchTree
{
public:
	BinarySearchTree()
	{
		_nil = new Node();
		_root = _nil;
	};
	~BinarySearchTree() 
	{
		delete _nil;
	};
	void Print()
	{
		::system("cls");
		ShowConsoleCursor(false);
		Print(_root, 10, 0);
	}
	void Print(Node* node, int x, int y)
	{
		if (node == _nil)
			return;

		SetCursorPosition(x, y);

		if (node->color == Color::Black)
			SetCursorColor(ConsoleColor::BLUE);
		else 
			SetCursorColor(ConsoleColor::RED);

		cout << node->key << endl;
		Print(node->left, x - (5 / (y + 1)), y + 1);
		Print(node->right, x + (5 / (y + 1)), y + 1);

		SetCursorColor(ConsoleColor::WHITE);
	}

	void Insert(int key)
	{
		Node* newNode = new Node;
		newNode->key = key;

		Node* node = _root;
		Node* parent = _nil;

		while (node != _nil)
		{
			parent = node;

			if (key < node->key)
				node = node->left;
			else
				node = node->right;
		}

		newNode->parent = parent;
		if (parent == _nil)
			_root = newNode;
		if (key < parent->key)
			parent->left = newNode;
		else
			parent->right = newNode;

		// 검사
		newNode->left = _nil;
		newNode->right = _nil;
		newNode->color = Color::Red;

		InsertFixUp(newNode);
	}
	void InsertFixUp(Node* node)
	{
		// 1) p = red, uncle = red;
		// -> p = black, uncle = black, pp = red로 바꿈
		// 2) p = red, uncle = black (triangle)
		// -> 회전을 통해 case 3으로 바꿈
		// 3) p = red, uncle = black (list)
		// -> 색상 변경 + 회전

		//	[p(Black)]
		//		[n(Red)]
		while (node->parent->color == Color::Red)
		{
			if (node->parent == node->parent->parent->left)
			{
				//       [pp[R]]
				//    [p(B)]  [u(B)]
				// [n(R)]
				Node* uncle = node->parent->parent->right;
				if (uncle->color == Color::Red)
				{
					node->parent->color = Color::Black;
					uncle->color = Color::Black;
					node->parent->parent->color = Color::Red;
					node = node->parent->parent;
				}
				else // uncle이 Red가 아닌 Black 일때
				{
					// Triangle 타입

					//      [pp[B]]
					//  [p(R)]    [u(R)]
					//     [n(R)]
					// ----------------
					//      [pp[R]]
					//   [p(B)]  [u(B)]
					// [n(R)]

					if (node == node->parent->right)
					{
						node = node->parent;
						LeftRotate(node);
					}

					// List 타입

					//      [pp[R]]
					//   [p(B)]  [u(B)]
					// [n(R)]
					// ----------------
					//       [p[R]]
					//   [n(B)]  [pp(B)]
					//              [u(R)]

					node->parent->color = Color::Black;
					node->parent->parent->color = Color::Red;
					RightRotate(node->parent->parent);
				}
			}
			else
			{
				Node* uncle = node->parent->parent->left;
				if (uncle->color == Color::Red)
				{
					node->parent->color = Color::Black; // p
					uncle->color = Color::Black; // u
					node->parent->parent->color = Color::Red; // pp
					node = node->parent->parent;
				}
				else // uncle이 Red가 아닌 Black 일때
				{
					// Triangle 타입

					//      [pp[B]]
					//  [u(B)]    [p(R)]
					//          [n(R)]
					// ----------------
					//      [pp[R]]
					//   [u(B)]   [n(B)]
					//               [p(R)]

					if (node == node->parent->left)
					{
						node = node->parent;
						RightRotate(node);
					}

					// List 타입

					//      [pp[R]]
					//   [u(B)]  [p(B)]
					//              [n(R)]
					// ----------------
					//       [p[R]]
					//   [pp(B)]  [n(B)]
					// [u(R)]

					node->parent->color = Color::Black;
					node->parent->parent->color = Color::Red;
					RightRotate(node->parent->parent);
				}
			}
		}
		_root->color = Color::Black;
	}
	//		[y]
	//	[x]		[3]
	// [1][2]
	// ------------------
	//		[x]
	//	[1]		[y]
	//   	   [2][3]
	void LeftRotate(Node* x) // y노드를 내 부모로 
	{
		Node* y = x->right;

		x->right = y->left; // [2]

		if (y->left != _nil)
			y->left->parent = x;

		y->parent = x->parent;

		if (x->parent == _nil)
			_root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;

		y->left = x;
		x->parent = y;
	};
	void RightRotate(Node* y) // x노드를 내 부모로 
	{
		Node* x = y->left;

		y->left = x->right; // [2]

		if (x->right != _nil)
			x->right->parent = y;

		x->parent = y->parent;

		if (x->parent == _nil)
			_root = x;
		else if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;

		x->right = y;
		y->parent = x;
	};
	

	void Delete(int key)
	{
		Node* deleteNode = Search(_root, key);
		Delete(deleteNode);
	}
	// 먼저 BST 삭제 실행
	//          [20]
	//   [10(B)]    [30]
	//     [15(R)] [25][40]
	// 10 삭제 ----------------------
	//          [20]
	//   [15(B)]    [30]
	//             [25][40]
	void Delete(Node* node)
	{
		if (node == _nil)
			return;

		if (node->left == _nil)
		{
			Color color = node->color;
			Node* right = node->right;
			Replace(node, node->right);

			if (color == Color::Black)
				DeleteFixUp(right);
		}
		else if (node->right == _nil)
		{
			Color color = node->color;
			Node* left = node->left;
			Replace(node, node->left);

			if (color == Color::Black)
				DeleteFixUp(left);
		}
		else
		{
			// 다음 데이터 찾기
			Node* next = Next(node);
			node->key = next->key;
			Delete(next);
		}
	}

	void DeleteFixUp(Node* node)
	{
		// 삭제할 노드 x
		Node* x = node;

		// [Case1][Case2]
		while (x != _root && x->color == Color::Black)
		{
			//       [p(B)]
			// [x(DB)]   [s(R)]
			//          [1]
			// -----------------
			//          [s(B)]
			//      [p(R)]
			// [x(DB)]   [1] 
			if (x == x->parent->left)
			{
				// [Case3]
				Node* s = x->parent->right;
				if (x->color == Color::Red)
				{
					s->color = Color::Black;
					x->parent->color = Color::Red;

					LeftRotate(x->parent);
					s = x->parent->right; // [1]
				}

				// [Case4]
				if (s->left->color == Color::Black && s->right->color == Color::Black)
				{
					s->color = Color::Red;
					x = x->parent;
				}
				// [Case5] case 6로 만드는 과정
				else
				{
					//        [p(B)]
					// [x(DB)]      [s(B)]
					//        [near[R]][far[B]]
					// -------------------------
					//         [p(B)]  
					//  [x(DB)]     [near[B]]
					//                   [s(R)]
					//                      [far[B]] 
					if (s->right->color == Color::Black)
					{
						s->left->color = Color::Black;
						s->color == Color::Red;
						RightRotate(s);
						s = x->parent->right;
					}
					           //[pp]
					//         [p(B)]  
					//  [x(DB)]     [s[B]]
					//                   [far(R)]
					// ---------------------------
					//           [s[B]]
					//       [p(B)]   [far(B)] 
					//  [x(B)]         
					// [Case6]
					s->color = x->parent->color;
					x->parent->color = Color::Black;
					s->right->color = Color::Black;
					LeftRotate(x->parent);
					x = _root;
				}
			}
			else
			{
				// [Case1][Case2]
				while (x != _root && x->color == Color::Black)
				{
					if (x == x->parent->right)
					{
						// [Case3]
						Node* s = x->parent->left;
						if (x->color == Color::Red)
						{
							s->color = Color::Black;
							x->parent->color = Color::Red;

							RightRotate(x->parent);
							s = x->parent->left; // [1]
						}

						// [Case4]
						if (s->right->color == Color::Black && s->left->color == Color::Black)
						{
							s->color = Color::Red;
							x = x->parent;
						}
						// [Case5] 
						else
						{
							if (s->left->color == Color::Black)
							{
								s->right->color = Color::Black;
								s->color == Color::Red;
								LeftRotate(s);
								s = x->parent->left;
							}

							// [Case6]
							s->color = x->parent->color;
							x->parent->color = Color::Black;
							s->right->color = Color::Black;
							RightRotate(x->parent);
							x = _root;
						}
					}
				}
			}
		}
		x->color = Color::Black;
	}

	// u서브트리를 v서브트리로 교체
	// 그리고 delete u
	void Replace(Node* u, Node* v)
	{
		if (u->parent == _nil)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;

		if (v)
			v->parent = u->parent;

		delete u;
	}

	Node* Search(Node* node, int key) 
	{
		if (node == _nil || key == node->key)
			return node;

		if (key < node->key)
			return Search(node->left, key);
		else 
			return Search(node->right, key);
	}

	Node* Min(Node* node)
	{
		while (node->left != _nil)
			node = node->left;
		return node;
	}
	Node* Max(Node* node)
	{
		while (node->right != _nil)
			node = node->right;
		return node;
	}
	Node* Next(Node* node)
	{
		if (node->right)
			return Min(node->right);

		Node* parent = node->parent;

		while (parent != _nil && node == parent->right)
		{
			node = parent;
			parent = parent->parent;
		}

		return parent;
	}

	Node* GetRoot() { return _root; };
private:
	Node* _root = nullptr;
	Node* _nil = nullptr;
};

int main()
{
	BinarySearchTree bst;

	bst.Insert(30);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(10);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(20);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(25);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(10);
	bst.Print();
	this_thread::sleep_for(1s);
}
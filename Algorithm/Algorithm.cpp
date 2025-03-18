#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;


template<typename T, typename Container = vector<T>>
class Stack
{
public:
	Stack() {};
	~Stack() {};

	void push(const T& data)
	{
		_container.push_back(data);
	};

	void pop()
	{
		_container.pop_back();
	};

	T& top()
	{
		return _container.back();
	};

	bool empty() { return _container.empty(); }
	bool size() { return _container.size(); }

private:
	//vector<T> _container;
	//list<T> _container;
	Container _container;
};

// Stack (LIFO Last-In-First-Out 후입선출)
int main()
{
	Stack<int, list<int>> s;

	s.push(1);
	s.push(2);
	s.push(3);

	while (s.empty() == false)
	{
		int data = s.top();

		s.pop();

		cout << data << "\n";
	}
}

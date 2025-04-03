#include <iostream>
#include <string>

using namespace std;

template<typename T>
class Stack
{
public:
	Stack() {};
	~Stack() { delete[] arr; };

	void push(const T& value)
	{
		arr[_size] = value;
		_size++;
	}
	void pop()
	{
		int t = top();
		cout << t << endl;

		if (t < 0) return;

		_size--;
	}
	int size() { return _size; }
	int top()
	{
		int t = arr[_size - 1];
		if (_size == 0) return -1;
	    else return t;
	}
	int empty()
	{
		if (_size == 0) return 1;
		else return 0;
	}
	void resize() { arr = new T[10000]; }

private:
	int _size = 0;
	T* arr;
};


int main() {
	int size;
	string keyword;
	Stack<int> s;
	s.resize();

	cin >> size;
	
	for (int i = 0; i < size; i++)
	{
		cin >> keyword;
		
		if (keyword == "push")
		{
			int x;
			cin >> x;
			s.push(x);
		}
		else if (keyword == "pop")
		{
			s.pop();
		}
		else if (keyword == "top")
		{
			cout << s.top() << endl;
		}
		else if (keyword == "empty")
		{
			cout << s.empty() << endl;
		}
		else if (keyword == "size")
		{
			cout << s.size() << endl;
		}
	}
}

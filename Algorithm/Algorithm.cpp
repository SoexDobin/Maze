#include <iostream>
#include <vector>
#include <queue>
using namespace std;


template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class Priority_queue
{
public:

	void push(const T& data)
	{
		_heap.push_back(data);
		int now = _heap.size() - 1;
		
		while (true)
		{
			int parentIndex = static_cast<int>((now - 1)) / 2;

			if (now == 0)
				break;
			if (_predicate(_heap[now], _heap[parentIndex]))
				break;
			
			::swap(_heap[now], _heap[parentIndex]);
			now = parentIndex;
		}
	}

	void pop()
	{
		// 배열 사이즈 맞추기
		// 가중치 높은 놈이 맨위로
		_heap.front() = _heap.back();
		_heap.pop_back();

		int now = 0;
		while (true)
		{
			int left = now * 2 + 1;
			int right = now * 2 + 2;

			if (left >= _heap.size())
				break;

			int next = now;
			if (_predicate(_heap[next], _heap[left]))
				next = left;

			if (right < _heap.size() && _predicate(_heap[next], _heap[right])) 
				next = right;

			if (next == now) break;

			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	T& top() { return _heap[0]; }
	bool empty() { return _heap.empty(); }

private:
	vector<T> _heap;
	Predicate _predicate;
};

int main()
{
	Priority_queue<int, vector<int>, less<int>> pq;

	pq.push(100);
	pq.push(300);
	pq.push(200);
	pq.push(500);
	pq.push(400);

	while (pq.empty() == false)
	{
		int value = pq.top();
		
		pq.pop();

		cout << value << endl;
	}
}
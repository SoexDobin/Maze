#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template<typename T, typename Container = vector<int>, typename Predicate = less<T>>
class Priority_queue
{
public:
	void push(const T& data)
	{
		// 우선 힙 구조부터 맞춰 준다.
		_heap.push_back(data);

		// 도장깨기 시작
		int now = static_cast<int>(_heap.size()) - 1;

		// 루트 노드 까지 시도
		while (now > 0)
		{
			int parentIndex = (now - 1) / 2;

			/*if (_heap[now] < _heap[parentIndex])*/
			if (_predicate(_heap[now], _heap[parentIndex]))
				break;

			// 데이터 교체
			::swap(_heap[now], _heap[parentIndex]);
			now = parentIndex;
		}
	}

	void pop()
	{
		_heap[0] = _heap.back();
		_heap.pop_back();

		int now = 0;

		while (true)
		{
			int leftChild = now * 2 + 1;
			int rightChild = now * 2 + 2;

			// 좌측에 left만큼의 사이즈 노드가 없는 경우
			if (leftChild >= _heap.size())
				break;

			int next = now;
			// 왼쪽과 비교
			/*if (_heap[next] < _heap[leftChild])*/
			if (_predicate(_heap[next], _heap[leftChild]))
				next = leftChild;

			// 우측에 right만큼의 사이즈 노드가 없는 경우
			// 위 조건을 통과해온 now or left보다 값이 작은 경우
			/*if (rightChild < _heap.size() && _heap[next] < _heap[rightChild])*/
			if (rightChild < _heap.size() && _predicate(_heap[next], _heap[rightChild]))
				next = rightChild;

			// 위 if문 다 안걸리면 왼쪽/오른쪽 둘 다 현재 값보다 작으니 종료
			if (next == now)
				break;

			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	T& top()
	{
		return _heap[0];
	}
	bool empty() { return _heap.empty(); }

private:
	Container		_heap = { };
	Predicate		_predicate = { };
};

//template<typename T, typename Container = vector<int>, typename Predicate = less<int>>
//class Priority_queue
//{
//public:
//
//	void push(const T& value)
//	{
//		_heap.push_back(value);
//		
//		int now = static_cast<int>(_heap.size()) - 1;
//		int parentIndex;
//		while (true)
//		{
//			parentIndex = (now - 1) / 2;
//
//			if (now == 0)
//				break;
//			if (_predicate(_heap[parentIndex], _heap[now]))
//				break;
//
//			::swap(_heap[now], _heap[parentIndex]);
//			now = parentIndex;
//		}
//	}
//
//	void pop()
//	{
//		// 1. 힙 사이즈 맞출 것
//		// 2. 부모는 항상 자식 보다 큰 가중치를 가진다.
//
//		_heap.front() = _heap.back();
//		_heap.pop_back();
//
//		int now = 0;
//		while (true)
//		{
//			int left = now * 2 + 1;
//			int right = now * 2 + 2;
//
//			if (left >= _heap.size()) break;
//			int next = now;
//			if (_predicate(_heap[left], _heap[next]))
//				next = left;
//			
//			if (right < _heap.size() && _predicate(_heap[right], _heap[next]))
//			{
//				next = right;
//			}
//
//			if (now == next) break;
//
//			::swap(_heap[now], _heap[next]);
//			now = next;
//		}
//	}
//
//	T& top() { return _heap[0]; };
//	bool empty() { return _heap.empty(); };
//
//private:
//	vector<int> _heap = { };
//	Predicate _predicate = { };
//};

int main()
{
	Priority_queue<int, vector<int>, greater<int>> pq;

	pq.push(100);
	pq.push(300);
	pq.push(200);
	pq.push(500);
	pq.push(500);
	pq.push(400);

	while (pq.empty() == false)
	{
		int value = pq.top();
		
		pq.pop();

		cout << value << endl;
	}
}
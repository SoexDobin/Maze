#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BubbleSort(vector<int>& v)
{
	const int size = static_cast<int>(v.size());

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < (size - 1 - i); j++)
		{
			if (v[j] > v[j + 1])
				::swap(v[j], v[j + 1]);
		}
	}
}

void SelectionSort(vector<int>& v)
{
	const int size = static_cast<int>(v.size());

	for (int i = 0; i < size - 1; i++) 
	{
		int leastIndex = i;
		for (int j = i + 1; j < size; j++)
		{
			if (v[j] < v[leastIndex])
				leastIndex = j;
		}
		::swap(v[i], v[leastIndex]);
	}
}

void InsertionSort(vector<int>& v)
{
	const int size = static_cast<int>(v.size());
	
	for (int i = 1; i < size; i++)
	{
		int insertData = v[i];

		int j;
		for (j = i - 1; j >= 0; j--)
		{
			if (v[j] > insertData)
				v[j + 1] = v[j];
			else
				break;
		}
		v[j + 1] = insertData;
	}
}

void HeapSort(vector<int>& v)
{
	priority_queue<int, vector<int>, greater<int>> pq;
	
	for (int n : v)
		pq.push(n);

	v.clear();

	while(pq.empty() == false)
	{
		v.push_back(pq.top());
		pq.pop();
	}
}

// [3][k][7][2][j][4][8][9]
// 분할 [3][k][7][2] : [j][4][8][9]
// 정복 [2][3][7][k] : [4][8][9][j]
// 결합 [2][3][4][7][8][9][j][k]

// void Merge(vector<int>& a, vector<int>& b)
// {
//		vector<int> temp;
//      //????
//		return temp;
// }
void MergeResult(vector<int>& v, int left, int mid, int right)
{

	int leftIdx = left;
	int rightIdx = mid + 1;
	vector<int> temp;
	while (leftIdx <= mid && rightIdx <= right)
	{
		if (v[leftIdx] <= v[rightIdx])
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
		else
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}

	// 왼쪽이 먼저 끝났으면 , 오른쪽 나머지 데이터 복사
	if (leftIdx > mid)
	{
		while (rightIdx <= right)
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	// 오른쪽이 먼저 끝났으면 , 왼쪽 나머지 데이터 복사
	else
	{
		while (leftIdx <= mid) 
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
	}

	for (int i = 0; i < temp.size(); i++)
		v[left + i] = temp[i];
};

void MergeSort(vector<int>& v, int left, int right)
{
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	MergeResult(v, left, mid, right);
}

int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;
	// O(NlogN)
	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
			low++;

		while (high >= left + 1 && pivot <= v[high])
			high--;

		if (low < high)
			::swap(v[low], v[high]);
	}

	::swap(v[left], v[high]);
	return high;
}
void QuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
		return;
	int pivot = Partition(v, left, right);
	QuickSort(v, left, pivot - 1);
	QuickSort(v, pivot + 1, right);
}

void TestTable()
{
	struct User
	{
		int userID = 0; // 1~999
		string username;
	};

	vector<User> users;
	users.resize(1000);

	// write
	users[777] = User{ 777, "Rookiss" };
	// read
	string name = users[777].username;
	cout << name << endl;

	// 테이블
	// 키를 알면, 데이터를 단번에 찾을 수 있다
}

void TestHash()
{
	struct User
	{
		int userID = 0; // 1~int32_max
		string username;
	};

	vector<User> users;
	users.resize(1000);

	const int userID = 123456789;
	int key = (userID % 1000);
	users[key] = User{ userID, "Rookiss" };
	
	User& user = users[key];
	if (user.userID == userID) 
	{
		string name = users[key].username;
		cout << name << endl;
	}
		

	// 테이블
	// 키를 알면, 데이터를 단번에 찾을 수 있다
}

// 충돌 문제
// 충돌이 발생한 자리를 대신해서 다른 빈자리를 찾아나서면 된다
// - 선형 조사법 (linear probing)
// 이미 키값이 존재하면 다음 자리에 저장한다.
// - 이차 조사법 (quadratic probing)
// 이미 키값이 존재하면 n^2 만큼 자리에 저장한다.

// 충돌이 나거나 배열 테이블 자체에 자리가 없을때
// 채이닝 
// 각 테이블 배열자체가 또한 배열, 연결 리스트 형식으로 되어서 다른 데이터를 가지는 것

void TestHashTableChaining()
{
	struct User
	{
		int userID = 0; // 1~int32_max
		string username;
	};

	vector<vector<User>> users;
	users.resize(1000);

	const int userID = 123456789;
	int key = (userID % 1000);
	// 채이닝
	users[key].push_back(User{ userID, "Rookiss" });
	users[key].push_back(User{ userID, "Faker" });

	vector <User>& bucket = users[key];
	for (User& user : bucket)
	{
		if (user.userID == userID)
		{
			string name = user.username;
			cout << name << endl;
		}
	}
}

void LineageBattleground()
{
	struct User {
		int teamID;

	};

	vector<User> users;
	for (int i = 0; i < 1000; i++)
	{
		users.push_back(User{ i });
	}

	users[5].teamID = users[1].teamID;

	for (User& user : users)
	{
		if (user.teamID == 1)
			user.teamID = 2;
	}
}
// 트리 구조를 이용한 상호 베타적 집합의 표현
// [0] [1] [2] [3] [4]

struct Node
{
	Node* leader;

};

class NaiveDisjointSet
{
public:
	NaiveDisjointSet(int n) : _parent(n)
	{
		for (int i = 0; i < n; i++)
			_parent[i] = i;
	};

	// 팀 리더 서치
	int Find(int u)
	{
		if (u == _parent[u])
			return u;

		return Find(_parent[u]);
	}

	// u가 v 밑으로
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		// 같은 팀 이면
		if (u == v) 
			return;

		_parent[u] = v;
	}

private:
	vector<int> _parent;
};



// 트리가 한쪽으로 기우는 문제를 해결
// 트리를 합칠 때, 항상 [높이가 낮은 트리를] [높이가 높은 트리] 밑으로
// (Union-By-Rank) 랭크에 의한 합치기 최적화
class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; i++)
			_parent[i] = i;
	};

	// 팀 리더 서치
	int Find(int u)
	{
		if (u == _parent[u])
			return u;

		return _parent[u] = Find(_parent[u]);
	}

	// u가 v 밑으로
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		// 같은 팀 이면
		if (u == v)
			return;

		if (_rank[u] > _rank[v])
			::swap(u, v);

		// rank[u] <= rank[v]가 보장됨??
		_parent[u] = v;
		if (_rank[u] == _rank[v])
			_rank[v]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};


int main()
{
	DisjointSet teams(1000);

	teams.Merge(10, 1);
	int teamID = teams.Find(1);
	int teamID2 = teams.Find(10);

	teams.Merge(3, 2);
	int teamID3 = teams.Find(3);
	int teamID4 = teams.Find(2);

	teams.Merge(1, 3);
	int teamID5 = teams.Find(1);
	int teamID6 = teams.Find(3);
}
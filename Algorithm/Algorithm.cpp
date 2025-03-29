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

int main()
{
	vector<int> v;
	srand(time(0));

	for (int i = 0; i < 50; i++)
	{
		int randValue = rand() % 100;
		v.push_back(randValue);
	}

	//BubbleSort(v);
	//SelectionSort(v);
	//InsertionSort(v);
	//HeapSort(v);
	MergeSort(v, 0, v.size() - 1);
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
}
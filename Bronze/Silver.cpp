#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	string str_buffer;
	getline(cin, str_buffer);
	while (str_buffer[0] != '.')
	{
		bool is = true;
		vector<char> v;
		for (int i = 0; str_buffer[i] != '\0'; i++)
		{
			switch (str_buffer[i])
			{
			case '[':
				v.push_back('[');
				break;
			case '(':
				v.push_back('(');
				break;
			case ']':
				{
					if (v.empty())
					{
						is = false;
						break;
					}
					char last = v.back();
					if (last != '[')
					{
						is = false;
						break;
					}
					v.pop_back();
					break;
				}
			case ')':
				{
					if (v.empty())
					{
						is = false;
						break;
					}
					char last = v.back();
					if (last != '(')
					{
						is = false;
						break;
					}
					v.pop_back();
					break;
				}
			}
			if (is == false)
				break;
		}
		if (v.empty() != true)
			is = false;

		if (is)
			cout << "yes" << "\n";
		else
			cout << "no" << "\n";
		getline(cin, str_buffer);
	}
}


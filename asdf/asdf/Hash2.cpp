#include <iostream>
#include <vector>
using namespace std;

//class HashSet
//{
//public:
//	HashSet(int n) : m_size(n), m_data(m_size - 1) {};
//
//	int Hash(int key)
//	{
//		return key % m_size;
//	}
//	void Insert(int value)
//	{
//		m_data[Hash(value)] = value;
//	}
//	bool Find(int value)
//	{
//		return m_data[Hash(value)] == value;
//	}
//	void Erase(int value)
//	{
//		m_data[Hash(value)] = -1;
//	}
//
//private:
//	int m_size;
//	std::vector<int> m_data;
//};


class HashSet
{
public:
	HashSet(int n) : m_size(n), m_data(m_size - 1) {};

	int Hash(std::string str)
	{
		int key = 0;
		for (auto c : str)
		{
			key += c;
		}
		return key % m_size;
	}

	unsigned long hash(unsigned char* str)
	{
		unsigned long hash = 5381;
		int c;
		while (c = *str++)
		{
			hash = (33 * hash) ^ c;
		}
		return hash;
	}

	void Insert(std::string value)
	{
		if (m_data[Hash(value)].size() == 0)
		{
			m_data[Hash(value)].push_back(value);
		}
		else {
			for (auto str : m_data[Hash(value)])
			{
				if (str == value)
				{
					return;
				}
			}
			m_data[Hash(value)].push_back(value);
		}
	}
	bool Find(std::string value)
	{
		for (auto str : m_data[Hash(value)])
		{
			if (str == value)
			{
				return true;
			}
		}
		return false;
	}
	void Erase(std::string value)
	{
		for (int i = 0; i < m_data[Hash(value)].size(); i++)
		{
			if (m_data[Hash(value)][i] == value)
			{
				m_data[Hash(value)].erase(m_data[Hash(value)].begin() + i);
				break;
			}
		}
	}

private:
	int m_size;
	std::vector<std::vector<std::string>> m_data;
};




int main()
{

	HashSet num_set(10);

	num_set.Insert("AAA");
	num_set.Insert("BBB");
	num_set.Insert("CCC");
	num_set.Insert("ABC");
	num_set.Insert("BAC");
	num_set.Insert("CBA");
	/*num_set.Insert(30);
	num_set.Insert(40);
	num_set.Insert(50);*/

	std::string str = "ABC";

	const char* a = str.c_str();
	char c[] = "ABC";

	cout << num_set.hash((unsigned char*)str.c_str()) << endl;

	if (num_set.Find(str))
	{
		cout << str << "is Found!" << endl;
	}
	else {
		cout << str << "is Not Found!" << endl;
	}

	str = "XYZ";

	if (num_set.Find(str))
	{
		cout << str << "is Found!" << endl;
	}
	else {
		cout << str << "is Not Found!" << endl;
	}


	return 0;
}
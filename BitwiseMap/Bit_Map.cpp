#include<iostream>
#include<fstream>
#include<ctime>
using namespace std;

class Byte
{
	friend class Bitmap;

private:
	unsigned char bit8;
	static const unsigned char mask[9];

public:
	Byte()
	{
		bit8 = 0;
	}

	void set(unsigned int at)
	{
		bit8 |= mask[at];
	}

	bool get(unsigned int at)
	{
		return bit8 & mask[at];
	}
};

class Bitmap
{
public:
	Bitmap(unsigned int _size)
	{
		m_bytes = new Byte[(_size + 7) / 8];
		m_size = _size;
	}
	virtual ~Bitmap()
	{
		delete m_bytes;
		m_size = 0;
	}

	bool push(unsigned int data)
	{
		if (data >= m_size)
		{
			return false;
		}
		m_bytes[data / 8].set(data % 8);
		return true;
	}

	bool find(unsigned int data)
	{
		return data >= m_size ? 0 : m_bytes[data / 8].get(data % 8);
	}

	unsigned int Size()
	{
		return m_size;
	}

	bool operator<<(unsigned int data)
	{
		return push(data);
	}

	Byte& operator[](unsigned int i)
	{
		if (i >= m_size / 8)
		{
			throw "index out of range";
		}
		return m_bytes[i];
	}

private:
	Byte* m_bytes;
	unsigned int m_size;
};

const unsigned char Byte::mask[9] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

int main(void)
{
	cout << "Input size:";
	int SIZE;
	cin >> SIZE;
	if (SIZE < 10000 || SIZE>10000000)
	{
		SIZE = 1000000;
		cout << "Changed SIZE = " << SIZE << endl;
	}

	ofstream ofs("data.txt");
	for (int k = 0; k < SIZE; ++k)
	{
		ofs << rand() << endl;
	}
	ofs.close();

	cout << "File saved." << endl;

	Bitmap bmp(8 * SIZE);

	unsigned int i = 0,u;
	unsigned int t0 = clock();

	ifstream ifs("data.txt");
	while (!ifs.eof()&&i<SIZE)
	{
		ifs >> u;
		bmp << u;
		++i;
	}
	ifs.close();

	unsigned int elapse = clock() - t0;

	cout << "Stored " << i << " data, Elapsed " << elapse << "ms" << endl;

	t0 = clock();
	i = 0;
	int c = 0;
	for (i = 0; i < SIZE; ++i)
	{
		if (bmp.find(i))
		{
			++c;
		}
	}
	elapse = clock() - t0;

	cout << "Found " << c << " mathe(s), Elapsed " << elapse << "ms" << endl;
	cout << "Please input the number you want to search:" << endl;

	while (cin >> u)
	{
		if (bmp.find(u))
		{
			cout << "Found "<< endl;
		}
		else
		{
			cout << "Not found "<< endl;
		}
	}
	return 0;
}
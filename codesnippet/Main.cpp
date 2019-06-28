#include <iostream>
#include <string>
#include <vector>
using namespace std;

extern int func(int x, int y);

void main()
{
	cout << func(100, 200) << endl;
	system("pause");
}

void test1()
{
	int i = 0;

	printf("%d,%d\n", i, i++);
	printf("%d,%d\n", i, ++i);
	printf("%d,%d\n", i++, ++i);
	printf("%d,%d,%d\n", i, i++, ++i);

	cout << i << "," << i++ << endl;
	cout << i << "," << ++i << endl;
	cout << i++ << "," << ++i << endl;
	cout << i << "," << i++ << "," << ++i << endl;
}

struct S1
{
	int a;  // 4
	char c[10];  // 12
	float f;  // 4
};

struct S2
{
	double a;  // 8
	int x;  // 4
	int y;  // 4
	char c;  // 8
};

#define S_OFFSET(s,v)  (size_t)(&(((s*)0)->v))

void test2(void)
{
	int ao = S_OFFSET(S1, a);
	int co = S_OFFSET(S1, c);
	int fo = S_OFFSET(S1, f);
	cout << ao << "," << co << "," << fo << endl;
	cout << sizeof(S1) << "," << sizeof(S2) << endl;
}

struct Node
{
	int val;
	Node* next;
};

Node* createList(int length)
{
	if (length <= 0)
	{
		return NULL;
	}
	Node* head = NULL;
	Node* cur = NULL;
	for (int i = 1; i <= length; ++i)
	{
		if (head == NULL)
		{
			head = new Node;
			head->val = i;
			head->next = NULL;
			cur = head;
			continue;
		}
		Node* p = new Node;
		p->val = i;
		p->next = NULL;
		cur->next = p;
		cur = p;
	}

	return head;
}

void printList(Node* head)
{
	Node* p = head;
	while (p != NULL)
	{
		cout << p->val << " ";
		p = p->next;
	}
	cout << endl;
}

void freeList(Node* head)
{
	Node* p = head;
	Node* q = p;
	while (p != NULL)
	{
		q = p->next;
		delete p;
		p = q;
	}
}

// 递归方法:找到链表倒数第k个节点
Node* rtK(Node* head, int k, int& i)
{
	if (head == NULL) return NULL;
	Node* nd = rtK(head->next, k, i);
	if (++i == k) return head;
	return nd;
}

void test3(void)
{
	int len = 10, k, i;
	Node* head = createList(len);
	Node* p = head;
	printList(head);

	for (int j = 1; j <= len; ++j)
	{
		i = 0;
		Node* node = rtK(head, j, i);
		if (node != NULL)
		{
			cout << node->val << endl;
		}
		else
		{
			cout << "Not found" << endl;
		}
	}

	freeList(head);
}

bool isPalindrome(int x)
{
	if (x < 0) return false;
	if (x < 10) return true;
	int base = 1;
	while (x / base >= 10)
	{
		base *= 10;
	}

	int left, right;
	while (x)
	{
		left = x / base;
		right = x % 10;
		if (left != right) return false;
		x -= base*left;
		x /= 10;
		base /= 100;
	}

	return true;
}

void test4(void)
{
	for (int i = -10; i < 12345; ++i)
	{
		if (isPalindrome(i))
			cout << i << endl;
	}
}

class Shape
{
public:
	Shape()
	{
		cout << "Shape::ctor()\n";
	}
	void print()
	{
		cout << "Shape::print()\n";
	}
	~Shape()
	{
		cout << "Shape::dtor()\n";
	}
};

class Circle : public virtual Shape
{
public:
	Circle()
	{
		cout << "Circle::ctor()\n";
	}
	~Circle()
	{
		cout << "Circle::dtor()\n";
	}
};

class Rectangle :virtual public Shape
{
public:
	Rectangle()
	{
		cout << "Rectangle::ctor()\n";
	}
	~Rectangle()
	{
		cout << "Rectangle::dtor()\n";
	}
};

class MyShape :public Circle, public Rectangle
{
public:
	MyShape()
	{
		cout << "MyShape::ctor()\n";
	}
	~MyShape()
	{
		cout << "MyShape::dtor()\n";
	}
};

void test5(void)
{
	MyShape shape;
	shape.print();
}

class CA
{
public:
	void Func1() { cout << "CA::Func1()" << endl; }
	virtual void Func2() { cout << "CA::Func2()" << endl; }
};

class CB :public CA
{
public:
	void Func1() { printf("CB::Func1()\n"); }
	void Func2() { printf("CB::Func2()\n"); }
};

void test6(void)
{
	CA* a = new CA;
	CA* b = new CB;
	a->Func1();
	a->Func2();
	b->Func1();
	b->Func2();
}

template<int n>
class Fibonacci
{
public:
	enum
	{
		result = Fibonacci<n - 1>::result + Fibonacci<n - 2>::result,
	};
};

template<>
class Fibonacci < 0 >
{
public:
	enum
	{
		result = 1,
	};
};

template<>
class Fibonacci < 1 >
{
public:
	enum
	{
		result = 1,
	};
};

void test7(void)
{
	const int n = 30;
	cout << "Fib(" << n << ") = " << Fibonacci<n>::result << endl;
}

class Test
{
public:
	void display()
	{
		cout << a << "," << b << endl;
	}

private:
	int a;
	int b;
};

void test8(void)
{
	Test* p1 = new Test;
	Test* p2 = new Test();

	p1->display();
	p2->display();
}

template<typename T>
class Base
{
	friend T;
private:
	Base()
	{
		cout << "Base.ctor()" << endl;
	}
	~Base()
	{
		cout << "Base.dtor()" << endl;
	}
};

class AX :virtual public Base < AX >
{
public:
	AX()
	{
		cout << "AX.ctor()" << endl;
	}
	~AX()
	{
		cout << "AX.dtor()" << endl;
	}
};

class BX :AX
{
	//
};

void test9(void)
{
	AX* pa = new AX;
	delete pa;

	//BX b;
}

class C1
{
public:
	C1() { cout << "C1.ctor()" << endl; }
	C1(int x){ cout << "C1.ctor(x)=" << x << endl; }
	~C1() { cout << "C1.dtor()" << endl; }
};

class C2
{
public:
	C2() { cout << "C2.ctor()" << endl; }
	C2(int x){ cout << "C2.ctor(x)=" << x << endl; }
	~C2() { cout << "C2.dtor()" << endl; }
};

class C3
{
public:
	C3() { cout << "C3.ctor()" << endl; }
	C3(int x){ cout << "C3.ctor(x)=" << x << endl; }
	~C3() { cout << "C3.dtor()" << endl; }
};

class D1 :public C1, public C3, public C2
{
public:
	D1() { cout << "D1.ctor()" << endl; }
	D1(int x1, int x2, int x3) :C3(x3), C2(x2), C1(x1) {}
	~D1() { cout << "D1.dtor()" << endl; }
};

class D2
{
public:
	D2() { cout << "D2.ctor()" << endl; }
	D2(int x1, int x2, int x3)	{}
	~D2() { cout << "D2.dtor()" << endl; }
private:
	C3 c3;
	C1 c1;
	C2 c2;
};

void test10(void)
{
	D1* p1 = new D1(1, 2, 3);
	delete p1;

	cout << endl;

	D2* p2 = new D2(1, 2, 3);
	delete p2;

	cout << endl;
}

class NoDefault
{
public:
	NoDefault(string& s) { str = s; }
private:
	string str;
};

void test11(void)
{
	//vector<NoDefault> vnd(10);
	//cout << vnd.size() << endl;
}

template<typename Ty, int size>
Ty min(Ty* arr)
{
	Ty m = arr[0];
	for (int i = 1; i < size; ++i)
	{
		if (m>arr[i]) m = arr[i];
	}

	return m;
}

void test12(void)
{
	int nums[] = { 10, 21, 6, 9, 2, 7, 19 };
	int a = min<int, sizeof(nums) / sizeof(int)>(nums);
	cout << a << endl;
}

char* sz1 = "Hello";
char* sz2 = "Hello";

void test13(void)
{
	printf("sz1: 0x%0X\nsz2: 0x%0X\n", (int)sz1, (int)sz2);
}

int func(int x, int y)
{
	return ((x&y) + ((x^y) >> 1));
}

bool isExp2(int x)
{
	return (!(x&(x - 1)));
}

void Compare(int a, int b)
{
	char* ss[2] = { ">", "<=" };
	unsigned int c = a - b;
	int i = c >> (sizeof(int) * 8 - 1);
	cout << a << ss[i] << b << endl;
}

double GetPI(int N)
{
	int c = 0;
	int x, y;
	int Z = RAND_MAX*RAND_MAX;
	for (int i = 0; i < N; ++i)
	{
		x = rand();
		y = rand();
		if ((x*x + y*y) < Z) ++c;
	}

	return 4.0*c / N;
}

int ReverseInteger(int x)
{
	//if (num > -9 && num < 9) return num;
	int sgn_bit = x & 0x80000000;
	int y = sgn_bit ? -x : x;
	int count = 0, digits[16] = { 0 };
	while (y > 0)
	{
		digits[count++] = y % 10;
		y /= 10;
	}
	y = digits[0];
	float z = y;
	for (int i = 1; i < count; ++i)
	{
		y = 10 * y + digits[i];
		z = 10.0 * z + digits[i];
	}

	if ((float)y != z) return 0;
	return sgn_bit ? -y : y;
}

int myAtoi(string str)
{
	if (str.length() == 0) return 0;
	int digits[10] = { 0 };
	int i_0 = 0, is_negative = 0, n_digit = 0;
	char ch;
	for (int i = 0; i < str.length() && n_digit < 10; ++i)
	{
		ch = str[i];
		if (ch == ' ' || ch == '+')
		{
			continue;
		}
		if (ch == '-')
		{
			is_negative = 1;
			continue;
		}
		ch -= '0';
		if (ch >= 0 && ch <= 9)
		{
			digits[n_digit++] = ch;
		}
		else return 0;
	}

	int n = 0;
	for (int i = 0; i < n_digit; ++i)
	{
		n = 10 * n + digits[i];
	}

	return is_negative ? -n : n;
}

int myAtoi2(string str)
{
	if (str.length() == 0) return 0;
	int digits[32] = { 0 };
	int i_0 = 0, is_negative = 0, n_digit = 0;
	char ch;
	int is_sgn = 0;
	int is_digit = 0;
	for (int i = 0; i < str.length(); ++i)
	{
		ch = str[i];
		if (ch == ' ')
		{
			if (is_digit || is_sgn) break;
			is_digit = 0;
			is_sgn = 0;
			continue;
		}
		if (ch == '+')
		{
			if (is_digit || is_sgn) break;
			is_digit = 0;
			is_sgn = 1;
			continue;
		}
		if (ch == '-')
		{
			if (is_digit || is_sgn) break;
			is_digit = 0;
			is_sgn = 1;
			is_negative = 1;
			continue;
		}
		ch -= '0';
		if (ch >= 0 && ch <= 9)
		{
			digits[n_digit++] = ch;
			is_digit = 1;
		}
		else
		{
			break;
		}
	}

	int n = 0;
	double m = 0.0;
	for (int i = 0; i < n_digit; ++i)
	{
		n = 10 * n + digits[i];
		m = 10.0*m + digits[i];
	}

	if (is_negative)
	{
		if ((double)n != m) n = 0x80000000;
		else n = -n;
	}
	else
	{
		if ((double)n != m) n = 0x7FFFFFFF;
	}

	return n;
}

class AC
{
private:
	friend class BC;
	void print()
	{
		cout << val << endl;
	}
	int val;
};

class BC
{
public:
	//
private:
	AC a;
};

inline float FastSqrt(float x)
{
	if (x <= 0) return 0.0;

	float x_half = 0.5f*x;
	int i = *(int*)&x;                  // get bits for floating VALUE   
	i = 0x5F375A86 - (i >> 1);    // gives initial guess y0  
	x = *(float*)&i;                    // convert bits BACK to float  
	x = x*(1.5f - x_half*x*x);       // Newton step, repeating increases accuracy  
	x = x*(1.5f - x_half*x*x);       // Newton step, repeating increases accuracy  
	x = x*(1.5f - x_half*x*x);        // Newton step, repeating increases accuracy  

	return 1.0f / x;
}
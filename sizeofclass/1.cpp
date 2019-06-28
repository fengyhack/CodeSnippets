class A
{
	virtual void func1();
};

class B: public A
{
	virtual void func2();
};

// sizeof(A)=4;
// sizeof(B)=4;
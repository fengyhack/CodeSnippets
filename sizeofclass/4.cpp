class A
{
	virtual void func1();
	char ch;
};

class B: public virtual A
{
	virtual void func2();
};

// sizeof(A)=8;
// sizeof(B)=16;
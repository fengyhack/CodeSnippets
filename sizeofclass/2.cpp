class A
{
	virtual void func1();
};

class B: public virtual A
{
	virtual void func2();
};

// sizeof(A)=4;
// sizeof(B)=12;
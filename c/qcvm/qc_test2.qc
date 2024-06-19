
#pragma target vanilla
#pragma warning disable Q208
#pragma progs_dat qc_test2.dat
#pragma autoproto

void print(string s, ...) = #1 : print;

class MyClass {
	string classname;
	string targetname;
	void() MyClass;
	virtual void() SayHi;
};

void MyClass::MyClass(void)
{
	print("hello world!\n");
}

void MyClass::SayHi(void)
{
	print("hi!\n");
}

void main()
{
	MyClass m;
	m.SayHi();
}

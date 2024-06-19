
#pragma target vanilla
#pragma warning disable Q208
#pragma progs_dat qc_test3.dat
#pragma autoproto

void print(string s, ...) = #1 : print;

void other_function1()
{
	float num = 3;
}

void other_function2()
{
	float num = 42;
}

void main()
{
	print("hello world!\n");
}

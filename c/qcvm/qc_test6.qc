
#pragma target vanilla
#pragma warning disable Q208
#pragma progs_dat qc_test6.dat
#pragma autoproto

// builtins
void say_hello_world() = #1 : say_hello_world;
entity spawn() = #2 : spawn;

// define some fields
.float test0;
.vector test1;
.float test2;
.vector test3;

// main
void main()
{
	entity e = spawn();
	e.test0 = 69;
	e.test2 = 42;
	e.test1 = [2, 2, 2];
	e.test3 = [3, 3, 3];
}

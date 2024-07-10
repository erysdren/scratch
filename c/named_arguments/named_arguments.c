/* erysdren 2024 - public domain */

#include <stdio.h>

/* function setup macros */
#define ARGS(name) struct _##name
#define DECLARE(name) _##name(struct _##name args)
#define CALL(name, ...) _##name((struct _##name){ __VA_ARGS__ })

/* setup function arguments */
ARGS(doThing) { int x; int y; };

/* function definition */
int DECLARE(doThing)
{
	printf("x=%d y=%d\n", args.x, args.y);
	return 0;
}

/* one last manual convenience macro */
#define doThing(...) CALL(doThing, __VA_ARGS__)

/* test it */
int main(void)
{
	/* these are all equivalent */
	doThing(.x = 64, .y = 1);
	doThing(.y = 1, .x = 64);
	doThing(64, 1);
	doThing();

	return 0;
}

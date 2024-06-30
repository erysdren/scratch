
#include <stdio.h>
#include <libtcc.h>

int there_was_error = 0;

void tcc_error(void *opaque, const char *msg)
{
	fprintf(stderr, "TCC Error: \"%s\"\n", msg);
	there_was_error = 1;
}

int (*program_main)(void);

int main(int argc, char **argv)
{
	TCCState *s = tcc_new();

	// log errors
	tcc_set_error_func(s, NULL, tcc_error);

	// no standard libraries for you
	tcc_set_options(s, "-nostdinc -nostdlib");

	// output to memory
	tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

	// compile the program string
	if (tcc_add_file(s, "program.c") != 0)
		return 1;

	// there was an error of some kind
	if (there_was_error)
		return 1;

	// relocate symbol for execution
	if (tcc_relocate(s, TCC_RELOCATE_AUTO) != 0)
		return 1;

	program_main = tcc_get_symbol(s, "main");

	if (program_main)
		fprintf(stdout, "main: %d\n", program_main());
	else
		fprintf(stderr, "failed to get symbol \"main\"");

	tcc_delete(s);

	return 0;
}

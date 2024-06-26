
#include <stdio.h>
#include <stdlib.h>
#include "qcvm.h"

/*
 *
 * utilities
 *
 */

#define ASIZE(a) (sizeof(a)/sizeof(a[0]))
#define UNUSED(a) ((void)(a))

/* print qcvm error and exit */
static void die(int r)
{
	fprintf(stderr, "qcvm: \"%s\"\n", qcvm_result_string(r));
	exit(EXIT_FAILURE);
}

/* load an entire file into memory */
static void *load_file(const char *filename, unsigned int *sz)
{
	void *buffer;
	unsigned int filesize;
	FILE *file;

	file = fopen(filename, "rb");
	if (!file) return NULL;
	fseek(file, 0L, SEEK_END);
	filesize = ftell(file);
	fseek(file, 0L, SEEK_SET);
	buffer = calloc(1, filesize);
	fread(buffer, 1, filesize, file);
	fclose(file);

	if (sz) *sz = filesize;

	return buffer;
}

/*
 *
 * builtins
 *
 */

int _say_hello_world(qcvm_t *qcvm)
{
	UNUSED(qcvm);
	printf("hello world!\n");
	return QCVM_OK;
}

static const int max_entities = 64;
static int num_entities = 0;

int _spawn(qcvm_t *qcvm)
{
	UNUSED(qcvm);
	qcvm_return_entity(qcvm, ++num_entities);
	return QCVM_OK;
}

struct qcvm_builtin builtins[] = {
	{"say_hello_world", 0, 0, _say_hello_world},
	{"spawn", 0, 0, _spawn}
};

/*
 *
 * main
 *
 */

int main(int argc, char **argv)
{
	int r;
	unsigned int entity_fields, entity_size;
	qcvm_t qcvm;

	/* load progs */
	if (argc > 1)
		qcvm.progs = load_file(argv[1], &qcvm.len_progs);
	else
		qcvm.progs = load_file("qc_test1.dat", &qcvm.len_progs);

	/* create tempstrings buffer */
	qcvm.len_tempstrings = 4096;
	qcvm.tempstrings = malloc(qcvm.len_tempstrings);

	/* setup builtins */
	qcvm.num_builtins = ASIZE(builtins);
	qcvm.builtins = builtins;

	/* init qcvm */
	if ((r = qcvm_init(&qcvm)) != QCVM_OK)
		die(r);

	/* query entity info */
	if ((r = qcvm_query_entity_info(&qcvm, &entity_fields, &entity_size)) != QCVM_OK)
		die(r);

	/* allocate entities buffer */
	qcvm.len_entities = entity_size * max_entities;
	qcvm.entities = malloc(qcvm.len_entities);

	/* run main function */
	if ((r = qcvm_run(&qcvm, "main")) != QCVM_OK)
		die(r);

	/* free data */
	free(qcvm.progs);
	free(qcvm.tempstrings);
	free(qcvm.entities);

	return 0;
}

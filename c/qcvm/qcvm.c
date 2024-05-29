
#include "qcvm.h"

int qcvm_init(qcvm_t *qcvm)
{
	if (qcvm == 0)
		return QCVM_NULL_POINTER;
	if (qcvm->progs == 0 || !qcvm->len_progs)
		return QCVM_INVALID_PROGS;

	/* file header */
	qcvm->header = (struct qcvm_header *)qcvm->progs;

	/* statements */
	qcvm->num_statements = (unsigned int)qcvm->header->num_statements;
	qcvm->statements = (struct qcvm_statement *)((char *)qcvm->progs + qcvm->header->ofs_statements);

	/* functions */
	qcvm->num_functions = (unsigned int)qcvm->header->num_functions;
	qcvm->functions = (struct qcvm_function *)((char *)qcvm->progs + qcvm->header->ofs_functions);

	/* strings */
	qcvm->len_strings = (unsigned int)qcvm->header->len_strings;
	qcvm->strings = (char *)qcvm->progs + qcvm->header->ofs_strings;

	/* field vars */
	qcvm->num_field_vars = (unsigned int)qcvm->header->num_field_vars;
	qcvm->field_vars = (struct qcvm_var *)((char *)qcvm->progs + qcvm->header->ofs_field_vars);

	/* global vars */
	qcvm->num_global_vars = (unsigned int)qcvm->header->num_global_vars;
	qcvm->global_vars = (struct qcvm_var *)((char *)qcvm->progs + qcvm->header->ofs_global_vars);

	/* globals */
	qcvm->num_globals = (unsigned int)qcvm->header->num_globals;
	qcvm->globals = (union qcvm_global *)((char *)qcvm->progs + qcvm->header->ofs_globals);

	return QCVM_OK;
}

const char *qcvm_result_string(int r)
{
	static const char *results[] = {
		"Ok",
		"Unexpected NULL pointer",
		"Function not found",
		"Invalid opcode",
		"Invalid result code",
		"Builtin call",
		"Builtin not found",
		"Execution finished",
		"Invalid progs data"
	};

	if (r < 0 || r >= QCVM_MAX_RESULT_CODES)
		return results[QCVM_INVALID_RESULT_CODE];

	return results[r];
}

int qcvm_load(qcvm_t *qcvm, const char *name)
{
	if (qcvm == 0 || name == 0)
		return QCVM_NULL_POINTER;

	return QCVM_OK;
}

int qcvm_step(qcvm_t *qcvm)
{
	if (qcvm == 0)
		return QCVM_NULL_POINTER;

	return QCVM_EXECUTION_FINISHED;
}

int qcvm_run(qcvm_t *qcvm, const char *name)
{
	int r, running;

	if (qcvm == 0 || name == 0)
		return QCVM_NULL_POINTER;

	/* load function */
	if ((r = qcvm_load(qcvm, name)) != QCVM_OK)
		return r;

	/* start stepping function */
	r = QCVM_OK;
	running = 1;
	while (running)
	{
		r = qcvm_step(qcvm);

		switch (r)
		{
			/* step went ok, proceed to next */
			case QCVM_OK:
				break;

			/* parse builtin call */
			case QCVM_BUILTIN_CALL:
				r = QCVM_BUILTIN_NOT_FOUND;
				running = 0;
				break;

			case QCVM_EXECUTION_FINISHED:
				r = QCVM_OK;
				running = 0;
				break;

			/* something else happened */
			default:
				running = 0;
				break;
		}
	}

	return r;
}

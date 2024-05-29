
#include <stddef.h>
#include "qcvm.h"

#define ASIZE(a) (sizeof(a)/sizeof(a[0]))

int qcvm_init(qcvm_t *qcvm)
{
	if (qcvm == NULL)
		return QCVM_NULL_POINTER;

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
		"Execution finished"
	};

	if (r < 0 || (size_t)r >= ASIZE(results))
		return results[QCVM_INVALID_RESULT_CODE];

	return results[r];
}

int qcvm_load(qcvm_t *qcvm, const char *name)
{
	if (qcvm == NULL || name == NULL)
		return QCVM_NULL_POINTER;

	return QCVM_OK;
}

int qcvm_step(qcvm_t *qcvm)
{
	if (qcvm == NULL)
		return QCVM_NULL_POINTER;

	return QCVM_EXECUTION_FINISHED;
}

int qcvm_run(qcvm_t *qcvm, const char *name)
{
	int r, running;

	if (qcvm == NULL || name == NULL)
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
				/* builtin was not found */
				r = QCVM_BUILTIN_NOT_FOUND;
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

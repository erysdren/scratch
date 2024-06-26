
#include "qcvm.h"

/* recognized version values */
static const int progs_version_old = 3;
static const int progs_version_standard = 6;
static const int progs_version_extended = 7;

/* static offsets into globals table */
#define OFS_NULL (0)
#define OFS_RETURN (1)
#define OFS_PARM0 (4)
#define OFS_PARM1 (7)
#define OFS_PARM2 (10)
#define OFS_PARM3 (13)
#define OFS_PARM4 (16)
#define OFS_PARM5 (19)
#define OFS_PARM6 (22)
#define OFS_PARM7 (25)
#define OFS_RESERVED (28)

#define STR_OFS(o) (qcvm->strings + (o))

/* opcode names */
#include <stdio.h>
const char *qcvm_opcode_names[] = {
	/* vanilla */
	"OPCODE_DONE", "OPCODE_MUL_F", "OPCODE_MUL_V", "OPCODE_MUL_FV", "OPCODE_MUL_VF",
	"OPCODE_DIV_F", "OPCODE_ADD_F", "OPCODE_ADD_V", "OPCODE_SUB_F", "OPCODE_SUB_V",
	"OPCODE_EQ_F", "OPCODE_EQ_V", "OPCODE_EQ_S", "OPCODE_EQ_E", "OPCODE_EQ_FNC",
	"OPCODE_NE_F", "OPCODE_NE_V", "OPCODE_NE_S", "OPCODE_NE_E", "OPCODE_NE_FNC",
	"OPCODE_LE", "OPCODE_GE", "OPCODE_LT", "OPCODE_GT", "OPCODE_LOAD_F", "OPCODE_LOAD_V",
	"OPCODE_LOAD_S", "OPCODE_LOAD_ENT", "OPCODE_LOAD_FLD", "OPCODE_LOAD_FNC",
	"OPCODE_ADDRESS", "OPCODE_STORE_F", "OPCODE_STORE_V", "OPCODE_STORE_S",
	"OPCODE_STORE_ENT", "OPCODE_STORE_FLD", "OPCODE_STORE_FNC", "OPCODE_STOREP_F",
	"OPCODE_STOREP_V", "OPCODE_STOREP_S", "OPCODE_STOREP_ENT", "OPCODE_STOREP_FLD",
	"OPCODE_STOREP_FNC", "OPCODE_RETURN", "OPCODE_NOT_F", "OPCODE_NOT_V", "OPCODE_NOT_S",
	"OPCODE_NOT_ENT", "OPCODE_NOT_FNC", "OPCODE_IF", "OPCODE_IFNOT", "OPCODE_CALL0",
	"OPCODE_CALL1", "OPCODE_CALL2", "OPCODE_CALL3", "OPCODE_CALL4", "OPCODE_CALL5",
	"OPCODE_CALL6", "OPCODE_CALL7", "OPCODE_CALL8", "OPCODE_STATE", "OPCODE_GOTO",
	"OPCODE_AND_F", "OPCODE_OR_F", "OPCODE_BITAND_F", "OPCODE_BITOR_F"
};

/* opcodes */
enum {
	/* vanilla */
	OPCODE_DONE, OPCODE_MUL_F, OPCODE_MUL_V, OPCODE_MUL_FV, OPCODE_MUL_VF,
	OPCODE_DIV_F, OPCODE_ADD_F, OPCODE_ADD_V, OPCODE_SUB_F, OPCODE_SUB_V,
	OPCODE_EQ_F, OPCODE_EQ_V, OPCODE_EQ_S, OPCODE_EQ_E, OPCODE_EQ_FNC,
	OPCODE_NE_F, OPCODE_NE_V, OPCODE_NE_S, OPCODE_NE_E, OPCODE_NE_FNC,
	OPCODE_LE, OPCODE_GE, OPCODE_LT, OPCODE_GT, OPCODE_LOAD_F, OPCODE_LOAD_V,
	OPCODE_LOAD_S, OPCODE_LOAD_ENT, OPCODE_LOAD_FLD, OPCODE_LOAD_FNC,
	OPCODE_ADDRESS, OPCODE_STORE_F, OPCODE_STORE_V, OPCODE_STORE_S,
	OPCODE_STORE_ENT, OPCODE_STORE_FLD, OPCODE_STORE_FNC, OPCODE_STOREP_F,
	OPCODE_STOREP_V, OPCODE_STOREP_S, OPCODE_STOREP_ENT, OPCODE_STOREP_FLD,
	OPCODE_STOREP_FNC, OPCODE_RETURN, OPCODE_NOT_F, OPCODE_NOT_V, OPCODE_NOT_S,
	OPCODE_NOT_ENT, OPCODE_NOT_FNC, OPCODE_IF, OPCODE_IFNOT, OPCODE_CALL0,
	OPCODE_CALL1, OPCODE_CALL2, OPCODE_CALL3, OPCODE_CALL4, OPCODE_CALL5,
	OPCODE_CALL6, OPCODE_CALL7, OPCODE_CALL8, OPCODE_STATE, OPCODE_GOTO,
	OPCODE_AND_F, OPCODE_OR_F, OPCODE_BITAND_F, OPCODE_BITOR_F,

	NUM_OPCODES
};

const int qcvm_num_opcodes = NUM_OPCODES;

int qcvm_init(qcvm_t *qcvm)
{
	if (!qcvm)
		return QCVM_NULL_POINTER;
	if (!qcvm->progs || !qcvm->len_progs)
		return QCVM_INVALID_PROGS;

	/* file header */
	qcvm->header = (struct qcvm_header *)qcvm->progs;

	/* check recognized versions */
	if (qcvm->header->version == progs_version_old)
		return QCVM_UNSUPPORTED_VERSION;
	else if (qcvm->header->version == progs_version_extended)
		return QCVM_UNSUPPORTED_VERSION;
	else if (qcvm->header->version != progs_version_standard)
		return QCVM_INVALID_PROGS;

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

int qcvm_query_entity_info(qcvm_t *qcvm, unsigned int *num_fields, unsigned int *size)
{
	if (!qcvm)
		return QCVM_NULL_POINTER;

	if (!qcvm->header || !qcvm->field_vars || !qcvm->num_field_vars)
		return QCVM_INVALID_PROGS;

	if (num_fields)
		*num_fields = (unsigned int)qcvm->header->num_entity_fields;

	if (size)
		*size = (unsigned int)(qcvm->header->num_field_vars * 4);

	return QCVM_OK;
}

const char *qcvm_result_string(int r)
{
	static const char *results[] = {
		"Ok",
		"Unexpected NULL pointer",
		"Function not found",
		"Invalid opcode",
		"Invalid function",
		"Invalid result code",
		"Builtin call",
		"Builtin not found",
		"Execution finished",
		"Invalid progs data",
		"Unsupported progs version",
		"Unsupported opcode",
		"Stack overflow",
		"Stack underflow"
	};

	if (r < 0 || r >= QCVM_NUM_RESULT_CODES)
		return results[QCVM_INVALID_RESULT_CODE];

	return results[r];
}

/* we have strcmp() at home */
static int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

/* find function by name string */
static int find_function(qcvm_t *qcvm, const char *name, unsigned int *out)
{
	unsigned int i;
	const char *function_name;

	if (!qcvm || !name)
		return QCVM_NULL_POINTER;

	for (i = 0; i < qcvm->num_functions; i++)
	{
		function_name = (const char *)(qcvm->strings + qcvm->functions[i].ofs_name);
		if (_strcmp(name, function_name) == 0)
		{
			if (out) *out = i;
			return QCVM_OK;
		}
	}

	return QCVM_FUNCTION_NOT_FOUND;
}

/* setup function for execution */
static int setup_function(qcvm_t *qcvm, struct qcvm_function *func)
{
	int i, x, p;

	if (!qcvm || !func)
		return QCVM_NULL_POINTER;

	/* setup stack */
	qcvm->stack[qcvm->stack_depth] = qcvm->xstack;
	qcvm->stack_depth++;
	if (qcvm->stack_depth >= QCVM_STACK_DEPTH)
		return QCVM_STACK_OVERFLOW;

	/* setup current local stack */
	for (i = 0; i < func->num_locals; i++)
		qcvm->local_stack[qcvm->local_stack_used + i] = qcvm->globals[func->first_parm + i].i;
	qcvm->local_stack_used += func->num_locals;

	/* copy parameters */
	p = func->first_parm;
	for (i = 0; i < func->num_parms; i++)
	{
		for (x = 0; x < func->parm_sizes[i]; x++)
		{
			qcvm->globals[p].i = qcvm->globals[OFS_PARM0 + i * 3 + x].i;
			p++;
		}
	}

	/* finish setting up */
	qcvm->current_function = func;
	qcvm->xstack.function = func;
	qcvm->current_statement_index = func->first_statement - 1;

	return QCVM_OK;
}

static int close_function(qcvm_t *qcvm)
{
	int i, num_locals;

	/* check for stack underflow */
	if (qcvm->stack_depth <= 0)
		return QCVM_STACK_UNDERFLOW;

	num_locals = qcvm->xstack.function->num_locals;
	qcvm->local_stack_used -= num_locals;

	/* check for stack underflow */
	if (qcvm->local_stack_used < 0)
		return QCVM_STACK_UNDERFLOW;

	/* restore locals from the stack */
	for (i = 0; i < num_locals; i++)
		qcvm->globals[qcvm->xstack.function->first_parm + i].i = qcvm->local_stack[qcvm->local_stack_used + i];

	/* move down the stack */
	qcvm->stack_depth--;
	qcvm->xstack.function = qcvm->stack[qcvm->stack_depth].function;

	/* set next statement */
	qcvm->current_statement_index = qcvm->stack[qcvm->stack_depth].statement;

	return QCVM_OK;
}

int qcvm_load(qcvm_t *qcvm, const char *name)
{
	int r;
	unsigned int func;

	if (!qcvm || !name)
		return QCVM_NULL_POINTER;

	/* retrieve function id */
	if ((r = find_function(qcvm, name, &func)) != QCVM_OK)
		return r;

	/* do actual setup */
	return setup_function(qcvm, &qcvm->functions[func]);
}

int qcvm_step(qcvm_t *qcvm)
{
	int r;
	unsigned short opcode;

	if (!qcvm)
		return QCVM_NULL_POINTER;

	/* advance statement */
	qcvm->current_statement_index++;

	/* get current statement and evaluators */
	qcvm->current_statement = &qcvm->statements[qcvm->current_statement_index];
	qcvm->eval[1] = (union qcvm_eval *)&qcvm->globals[qcvm->current_statement->vars[0]];
	qcvm->eval[2] = (union qcvm_eval *)&qcvm->globals[qcvm->current_statement->vars[1]];
	qcvm->eval[3] = (union qcvm_eval *)&qcvm->globals[qcvm->current_statement->vars[2]];

	/* update stack */
	qcvm->xstack.function->profile++;
	qcvm->xstack.statement = qcvm->current_statement_index;

	/* parse opcode */
	opcode = qcvm->current_statement->opcode;
	printf("opcode: 0x%02x: %s\n", opcode, qcvm_opcode_names[opcode]);
	switch (opcode)
	{
		/* function call */
		case OPCODE_CALL0:
		case OPCODE_CALL1:
		case OPCODE_CALL3:
		case OPCODE_CALL4:
		case OPCODE_CALL5:
		case OPCODE_CALL6:
		case OPCODE_CALL7:
		case OPCODE_CALL8:
		{
			/* check for null function */
			if (qcvm->eval[1]->func < 1)
				return QCVM_INVALID_FUNCTION;

			/* get function argc */
			qcvm->current_argc = opcode - OPCODE_CALL0;

			/* assign next function value */
			qcvm->next_function = &qcvm->functions[qcvm->eval[1]->func];

			/* setup state for builtin call */
			if (qcvm->next_function->first_statement < 1)
				return QCVM_BUILTIN_CALL;

			/* setup for execution */
			if ((r = setup_function(qcvm, qcvm->next_function) != QCVM_OK))
				return r;

			return QCVM_OK;
		}

		/* function return */
		case OPCODE_RETURN:
		case OPCODE_DONE:
		{
			qcvm->globals[OFS_RETURN] = qcvm->globals[qcvm->current_statement->vars[0]];
			qcvm->globals[OFS_RETURN + 1] = qcvm->globals[qcvm->current_statement->vars[0] + 1];
			qcvm->globals[OFS_RETURN + 2] = qcvm->globals[qcvm->current_statement->vars[0] + 2];

			if ((r = close_function(qcvm)) != QCVM_OK)
				return r;

			if (qcvm->stack_depth == qcvm->exit_depth)
				return QCVM_EXECUTION_FINISHED;

			return QCVM_OK;
		}

		case OPCODE_MUL_F:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f * qcvm->eval[2]->f;
			break;
		}

		case OPCODE_MUL_V:
		{
			qcvm->eval[3]->f =
				qcvm->eval[1]->v[0] * qcvm->eval[2]->v[0] +
				qcvm->eval[1]->v[1] * qcvm->eval[2]->v[1] +
				qcvm->eval[1]->v[2] * qcvm->eval[2]->v[2];
			break;
		}

		case OPCODE_MUL_FV:
		{
			qcvm->eval[3]->v[0] = qcvm->eval[1]->f * qcvm->eval[2]->v[0];
			qcvm->eval[3]->v[1] = qcvm->eval[1]->f * qcvm->eval[2]->v[1];
			qcvm->eval[3]->v[2] = qcvm->eval[1]->f * qcvm->eval[2]->v[2];
			break;
		}

		case OPCODE_MUL_VF:
		{
			qcvm->eval[3]->v[0] = qcvm->eval[2]->f * qcvm->eval[1]->v[0];
			qcvm->eval[3]->v[1] = qcvm->eval[2]->f * qcvm->eval[1]->v[1];
			qcvm->eval[3]->v[2] = qcvm->eval[2]->f * qcvm->eval[1]->v[2];
			break;
		}

		case OPCODE_DIV_F:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f / qcvm->eval[2]->f;
			break;
		}

		case OPCODE_ADD_F:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f + qcvm->eval[2]->f;
			break;
		}

		case OPCODE_ADD_V:
		{
			qcvm->eval[3]->v[0] = qcvm->eval[1]->v[0] + qcvm->eval[2]->v[0];
			qcvm->eval[3]->v[1] = qcvm->eval[1]->v[1] + qcvm->eval[2]->v[1];
			qcvm->eval[3]->v[2] = qcvm->eval[1]->v[2] + qcvm->eval[2]->v[2];
			break;
		}

		case OPCODE_SUB_F:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f - qcvm->eval[2]->f;
			break;
		}

		case OPCODE_SUB_V:
		{
			qcvm->eval[3]->v[0] = qcvm->eval[1]->v[0] - qcvm->eval[2]->v[0];
			qcvm->eval[3]->v[1] = qcvm->eval[1]->v[1] - qcvm->eval[2]->v[1];
			qcvm->eval[3]->v[2] = qcvm->eval[1]->v[2] - qcvm->eval[2]->v[2];
			break;
		}

		case OPCODE_EQ_F:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f == qcvm->eval[2]->f;
			break;
		}

		case OPCODE_EQ_V:
		{
			qcvm->eval[3]->f =
				(qcvm->eval[1]->v[0] == qcvm->eval[2]->v[0]) &&
				(qcvm->eval[1]->v[1] == qcvm->eval[2]->v[1]) &&
				(qcvm->eval[1]->v[2] == qcvm->eval[2]->v[2]);
			break;
		}

		case OPCODE_EQ_S:
		{
			qcvm->eval[3]->f = !_strcmp(STR_OFS(qcvm->eval[1]->s), STR_OFS(qcvm->eval[2]->s));
			break;
		}

		case OPCODE_EQ_E:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->i == qcvm->eval[2]->i;
			break;
		}

		case OPCODE_EQ_FNC:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->func == qcvm->eval[2]->func;
			break;
		}

		case OPCODE_NE_F:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f != qcvm->eval[2]->f;
			break;
		}

		case OPCODE_NE_V:
		{
			qcvm->eval[3]->f =
				(qcvm->eval[1]->v[0] != qcvm->eval[2]->v[0]) ||
				(qcvm->eval[1]->v[1] != qcvm->eval[2]->v[1]) ||
				(qcvm->eval[1]->v[2] != qcvm->eval[2]->v[2]);
			break;
		}

		case OPCODE_NE_S:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_NE_E:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->i != qcvm->eval[2]->i;
			break;
		}

		case OPCODE_NE_FNC:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->func != qcvm->eval[2]->func;
			break;
		}

		case OPCODE_LE:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f <= qcvm->eval[2]->f;
			break;
		}

		case OPCODE_GE:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f >= qcvm->eval[2]->f;
			break;
		}

		case OPCODE_LT:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f < qcvm->eval[2]->f;
			break;
		}

		case OPCODE_GT:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f > qcvm->eval[2]->f;
			break;
		}

		case OPCODE_LOAD_F:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_LOAD_V:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_LOAD_S:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_LOAD_ENT:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_LOAD_FLD:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_LOAD_FNC:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_ADDRESS:
		{
			unsigned int *entity_ofs;
			unsigned int *field_ofs;

			/* get offset to entity */
			entity_ofs = (unsigned int *)qcvm->entities +
				(qcvm->eval[1]->e * qcvm->header->num_field_vars);

			/* get offset to entity field */
			field_ofs = &entity_ofs[qcvm->eval[2]->i];

			/* offset from start of entities buffer */
			qcvm->eval[3]->i = (int)((unsigned char *)field_ofs - (unsigned char *)qcvm->entities);

			break;
		}

		case OPCODE_STORE_F:
		{
			qcvm->eval[2]->i = qcvm->eval[1]->i;
			break;
		}

		case OPCODE_STORE_V:
		{
			qcvm->eval[2]->v[0] = qcvm->eval[1]->v[0];
			qcvm->eval[2]->v[1] = qcvm->eval[1]->v[1];
			qcvm->eval[2]->v[2] = qcvm->eval[1]->v[2];
			break;
		}

		case OPCODE_STORE_S:
		{
			qcvm->eval[2]->s = qcvm->eval[1]->s;
			break;
		}

		case OPCODE_STORE_ENT:
		{
			qcvm->eval[2]->e = qcvm->eval[1]->e;
			break;
		}

		case OPCODE_STORE_FLD:
		{
			qcvm->eval[2]->field = qcvm->eval[1]->field;
			break;
		}

		case OPCODE_STORE_FNC:
		{
			qcvm->eval[2]->i = qcvm->eval[1]->i;
			break;
		}

		case OPCODE_STOREP_F:
		{
			qcvm->eval[0] = (union qcvm_eval *)((unsigned char *)qcvm->entities + qcvm->eval[2]->i);
			qcvm->eval[0]->i = qcvm->eval[1]->i;
			break;
		}

		case OPCODE_STOREP_V:
		{
			qcvm->eval[0] = (union qcvm_eval *)((unsigned char *)qcvm->entities + qcvm->eval[2]->i);
			qcvm->eval[0]->v[0] = qcvm->eval[1]->v[0];
			qcvm->eval[0]->v[1] = qcvm->eval[1]->v[1];
			qcvm->eval[0]->v[2] = qcvm->eval[1]->v[2];
			break;
		}

		case OPCODE_STOREP_S:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_STOREP_ENT:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_STOREP_FLD:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_STOREP_FNC:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_NOT_F:
		{
			qcvm->eval[3]->f = !qcvm->eval[1]->f;
			break;
		}

		case OPCODE_NOT_V:
		{
			qcvm->eval[3]->f = !qcvm->eval[1]->v[0] && !qcvm->eval[1]->v[1] && !qcvm->eval[1]->v[2];
			break;
		}

		case OPCODE_NOT_S:
		{
			qcvm->eval[3]->f = !qcvm->eval[1]->s || !qcvm->strings[qcvm->eval[1]->s];
			break;
		}

		case OPCODE_NOT_ENT:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_NOT_FNC:
		{
			qcvm->eval[3]->f = !qcvm->eval[1]->func;
			break;
		}

		case OPCODE_IF:
		{
			if (qcvm->eval[1]->i)
				qcvm->current_statement_index += qcvm->current_statement->vars[1] - 1;
			break;
		}

		case OPCODE_IFNOT:
		{
			if (!qcvm->eval[1]->i)
				qcvm->current_statement_index += qcvm->current_statement->vars[1] - 1;
			break;
		}

		case OPCODE_STATE:
		{
			return QCVM_UNSUPPORTED_OPCODE;
		}

		case OPCODE_GOTO:
		{
			qcvm->current_statement_index += qcvm->current_statement->vars[0] - 1;
			break;
		}

		case OPCODE_AND_F:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f && qcvm->eval[2]->f;
			break;
		}

		case OPCODE_OR_F:
		{
			qcvm->eval[3]->f = qcvm->eval[1]->f || qcvm->eval[2]->f;
			break;
		}

		case OPCODE_BITAND_F:
		{
			qcvm->eval[3]->f = (int)qcvm->eval[1]->f & (int)qcvm->eval[2]->f;
			break;
		}

		case OPCODE_BITOR_F:
		{
			qcvm->eval[3]->f = (int)qcvm->eval[1]->f | (int)qcvm->eval[2]->f;
			break;
		}

		default:
		{
			return QCVM_INVALID_OPCODE;
		}
	}

	return QCVM_OK;
}

int qcvm_run(qcvm_t *qcvm, const char *name)
{
	int r, running;
	unsigned int i;

	if (!qcvm || !name)
		return QCVM_NULL_POINTER;

	/* save exit depth */
	qcvm->exit_depth = qcvm->stack_depth;

	/* load function */
	if ((r = qcvm_load(qcvm, name)) != QCVM_OK)
		return r;

	/* start stepping through function */
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
			{
				if (qcvm->next_function->first_statement == 0)
				{
					char *name = qcvm->strings + qcvm->next_function->ofs_name;

					/* search for named builtin */
					for (i = 0; i < qcvm->num_builtins; i++)
					{
						if (_strcmp(name, qcvm->builtins[i].name) == 0)
						{
							qcvm->builtins[i].func(qcvm);
							qcvm->next_function->first_statement = -1 * (i + 1);
							r = QCVM_OK;
							break;
						}
					}
				}
				else if (qcvm->next_function->first_statement < 0)
				{
					/* get builtin by index */
					int builtin = (-1 * qcvm->next_function->first_statement) - 1;

					/* check bounds */
					if (builtin < 0 || builtin >= (int)qcvm->num_builtins)
					{
						r = QCVM_BUILTIN_NOT_FOUND;
					}
					else
					{
						qcvm->builtins[builtin].func(qcvm);
						r = QCVM_OK;
					}
				}

				/* its error */
				if (r != QCVM_OK)
					return r;
				else
					break;
			}

			/* execution finished */
			case QCVM_EXECUTION_FINISHED:
				return QCVM_OK;

			/* something else happened */
			default:
				return r;
		}
	}

	return r;
}

int qcvm_return_vector(qcvm_t *qcvm, float x, float y, float z)
{
	if (!qcvm)
		return QCVM_NULL_POINTER;

	qcvm->globals[OFS_RETURN].f = x;
	qcvm->globals[OFS_RETURN + 1].f = y;
	qcvm->globals[OFS_RETURN + 2].f = z;

	return QCVM_OK;
}

int qcvm_return_int(qcvm_t *qcvm, int i)
{
	if (!qcvm)
		return QCVM_NULL_POINTER;

	qcvm->globals[OFS_RETURN].i = i;
	qcvm->globals[OFS_RETURN + 1].i = 0;
	qcvm->globals[OFS_RETURN + 2].i = 0;

	return QCVM_OK;
}

int qcvm_return_float(qcvm_t *qcvm, float f)
{
	if (!qcvm)
		return QCVM_NULL_POINTER;

	qcvm->globals[OFS_RETURN].f = f;
	qcvm->globals[OFS_RETURN + 1].f = 0;
	qcvm->globals[OFS_RETURN + 2].f = 0;

	return QCVM_OK;
}

int qcvm_return_entity(qcvm_t *qcvm, unsigned int e)
{
	if (!qcvm)
		return QCVM_NULL_POINTER;

	qcvm->globals[OFS_RETURN].ui = e;
	qcvm->globals[OFS_RETURN + 1].ui = 0;
	qcvm->globals[OFS_RETURN + 2].ui = 0;

	return QCVM_OK;
}

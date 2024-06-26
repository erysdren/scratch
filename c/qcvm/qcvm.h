
#ifndef _QCVM_H_
#define _QCVM_H_
#ifdef __cplusplus
extern "C" {
#endif

/* result codes */
enum {
	QCVM_OK,
	QCVM_NULL_POINTER,
	QCVM_FUNCTION_NOT_FOUND,
	QCVM_INVALID_OPCODE,
	QCVM_INVALID_FUNCTION,
	QCVM_INVALID_RESULT_CODE,
	QCVM_BUILTIN_CALL,
	QCVM_BUILTIN_NOT_FOUND,
	QCVM_EXECUTION_FINISHED,
	QCVM_INVALID_PROGS,
	QCVM_UNSUPPORTED_VERSION,
	QCVM_UNSUPPORTED_OPCODE,
	QCVM_STACK_OVERFLOW,
	QCVM_STACK_UNDERFLOW,
	QCVM_NUM_RESULT_CODES
};

/* these can be adjusted at compile time, but i wouldn't recommend it */
#ifndef QCVM_STACK_DEPTH
#define QCVM_STACK_DEPTH (32)
#endif
#ifndef QCVM_LOCAL_STACK_DEPTH
#define QCVM_LOCAL_STACK_DEPTH (2048)
#endif

/* number of opcodes */
extern const int qcvm_num_opcodes;

/* main container */
typedef struct qcvm {

	/** progs file buffer and size
	 *
	 * this should be loaded directly from the disk into this buffer. there's
	 * not really any way to generate these programmatically besides writing
	 * your own qc compiler. qcvm expects the entire file structure to be
	 * present.
	 */
	unsigned int len_progs;
	void *progs;

	/** entities buffer
	 *
	 * allocate this to a suitably large size to store entity definitions and
	 * all their fields.
	 */
	unsigned int len_entities;
	void *entities;

	/** native functions
	 *
	 * these functions are called from qc if the call opcode is <=0. first,
	 * qcvm will see if the opcode number (made positive) is a valid index into
	 * the array. if not, it will search the array for one with a name string
	 * matching the function called from qc. NOTE: QCVM will update the opcode
	 * in memory to point to the correct builtin array index. this will make
	 * for slightly faster execution in further steps.
	 */
	unsigned int num_builtins;
	struct qcvm_builtin {
		const char *name;
		int num_args;
		const char **args;
		int (*func)(struct qcvm *qcvm);
	} *builtins;

	/** tempstring store
	 *
	 * qc relies heavily on tempstrings. the original qcvm only had a single
	 * 128 byte buffer for tempstrings returned one at a time. this meant that
	 * tempstrings would immediately expire as soon as they were overwritten,
	 * with no way to tell from qc. elsewhere, it would return a 32-bit offset
	 * from the existing string table to wherever the string was in general
	 * memory. later quake engines have added enhancements like garbage
	 * collection and reference counting.
	 *
	 * qcvm takes the current tempstrings buffer position and writes the new
	 * strings after it, wrapping around to the start if it's reached the end
	 * of the buffer.
	 *
	 * if this buffer is null, qcvm will not be able to return strings from
	 * builtins.
	 */
	unsigned int len_tempstrings;
	void *tempstrings;

	/*
	 *
	 * "private" fields, don't mess with these.
	 *
	 */

	/* file header */
	struct qcvm_header {
		int version;
		int crc;
		int ofs_statements;
		int num_statements;
		int ofs_global_vars;
		int num_global_vars;
		int ofs_field_vars;
		int num_field_vars;
		int ofs_functions;
		int num_functions;
		int ofs_strings;
		int len_strings;
		int ofs_globals;
		int num_globals;
		int num_entity_fields;
	} *header;

	/* statements */
	unsigned int num_statements;
	struct qcvm_statement {
		unsigned short opcode;
		short vars[3];
	} *statements;

	/* functions */
	unsigned int num_functions;
	struct qcvm_function {
		int first_statement;
		int first_parm;
		int num_locals;
		int profile;
		int ofs_name;
		int ofs_filename;
		int num_parms;
		unsigned char parm_sizes[8];
	} *functions;

	/* strings */
	unsigned int len_strings;
	char *strings;

	/* field vars */
	unsigned int num_field_vars;
	struct qcvm_var {
		unsigned short type;
		unsigned short ofs;
		int name;
	} *field_vars;

	/* global vars */
	unsigned int num_global_vars;
	struct qcvm_var *global_vars;

	/* globals */
	unsigned int num_globals;
	union qcvm_global {
		float f;
		int i;
		unsigned int ui;
	} *globals;

	/*
	 *
	 * runtime stuff.
	 *
	 */

	/* stack */
	struct qcvm_stack {
		int statement;
		struct qcvm_function *function;
	} stack[QCVM_STACK_DEPTH];
	int stack_depth;
	int local_stack[QCVM_LOCAL_STACK_DEPTH];
	int local_stack_used;
	struct qcvm_stack xstack;

	/* execution state */
	struct qcvm_function *current_function;
	struct qcvm_function *next_function;
	struct qcvm_statement *current_statement;
	int current_statement_index;
	int current_builtin;
	int exit_depth;
	int current_argc;

	/* function evaluation */
	union qcvm_eval {
		int s;
		float f;
		float v[3];
		int func;
		int field;
		int i;
		unsigned int e;
	} *eval[4];

} qcvm_t;

/** initialize qcvm structure
 *
 * this function parses the progs buffer and sets up pointers to the various
 * structures present in the file. it also checks for what features are
 * available, such as writeable progs memory and tempstrings.
 *
 * @param qcvm virtual machine to init
 * @returns result code
 */
int qcvm_init(qcvm_t *qcvm);

/** query qcvm for amount of memory needed for per-entity storage
 *
 * qcvm requires a writeable buffer to store entities and their fields. each
 * entity field is 12 bytes, and the amount of entity fields in a progs file is
 * user-defined. use this function to allocate a suitable amount of space.
 *
 * usage example:
 *
 * const int max_entities = 8192;
 * unsigned int entity_fields = 0;
 * unsigned int entity_size = 0;
 * qcvm_query_entity_info(&qcvm, &entity_fields, &entity_size);
 * qcvm.entities = malloc(max_entities * entity_size);
 *
 * @param qcvm virtual machone to query
 * @returns result code
 */
int qcvm_query_entity_info(qcvm_t *qcvm, unsigned int *num_fields, unsigned int *size);

/** get static string from result code
 * @param r result code
 * @returns null terminated result string
 */
const char *qcvm_result_string(int r);

/** queue up function for execution
 * @param qcvm virtual machine to use
 * @param name function name
 * @returns result code
 */
int qcvm_load(qcvm_t *qcvm, const char *name);

/** execute one qcvm step
 * @param qcvm virtual machine to use
 * @returns result code
 */
int qcvm_step(qcvm_t *qcvm);

/** queue up and execute the named function
 *
 * @param qcvm virtual machine to use
 * @param name case-sensitive function name
 * @returns result code
 */
int qcvm_run(qcvm_t *qcvm, const char *name);

/** return a vector to the function that called this one
 *
 * @param qcvm virtual machine to use
 * @param a vector x value
 * @param b vector y value
 * @param c vector z value
 * @returns result code
 */
int qcvm_return_vector(qcvm_t *qcvm, float x, float y, float z);

/** return an int to the function that called this one
 *
 * @param qcvm virtual machine to use
 * @param i integer value
 * @returns result code
 */
int qcvm_return_int(qcvm_t *qcvm, int i);

/** return a float to the function that called this one
 *
 * @param qcvm virtual machine to use
 * @param f float value
 * @returns result code
 */
int qcvm_return_float(qcvm_t *qcvm, float f);

/** return an entity index to the function that called this one
 *
 * @param qcvm virtual machine to use
 * @param e entity index
 * @returns result code
 */
int qcvm_return_entity(qcvm_t *qcvm, unsigned int e);

#ifdef __cplusplus
}
#endif
#endif /* _QCVM_H_ */

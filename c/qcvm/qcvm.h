
#ifndef _QCVM_H_
#define _QCVM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/* result codes */
enum {
	QCVM_OK,
	QCVM_NULL_POINTER,
	QCVM_FUNCTION_NOT_FOUND,
	QCVM_INVALID_OPCODE,
	QCVM_INVALID_RESULT_CODE,
	QCVM_BUILTIN_CALL,
	QCVM_BUILTIN_NOT_FOUND,
	QCVM_EXECUTION_FINISHED,
	QCVM_INVALID_PROGS
};

/* main container */
typedef struct qcvm {

	/** progs file buffer and size
	 *
	 * this should be loaded directly from the disk into this buffer. there's
	 * not really any way to generate these programmatically besides writing
	 * your own qc compiler. qcvm expects the entire file structure to be
	 * present.
	 */
	size_t len_progs;
	void *progs;

	/** set to >0 if qcvm can write to progs memory
	 *
	 * this only happens when parsing builtin calls. if a call opcode has a
	 * value of 0, then the qcvm will search the qcvm->builtins array for one
	 * with a matching name string, and update the opcode in memory to point to
	 * that one. it will also do this to update an out-of-range builtin number
	 * to one in range, if the name string matches.
	 */
	int progs_writeable;

	/** native functions
	 *
	 * these functions are called from qc if the call opcode is <=0. first,
	 * qcvm will see if the opcode number (made positive) is a valid index into
	 * the array. if not, it will search the array for one with a name string
	 * matching the function called from qc. if progs_writeable is >0, it will
	 * update the opcode in memory to point to the correct builtin array index.
	 * this will make for slightly faster execution in further steps.
	 */
	size_t num_builtins;
	struct qcvm_builtin {
		int id;
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
	size_t len_tempstrings;
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
	size_t num_statements;
	struct qcvm_statement {
		unsigned short opcode;
		short vars[3];
	} *statements;

	/* functions */
	size_t num_functions;
	struct qcvm_function {
		int first_statement;
		int first_parm;
		int num_locals;
		int profile;
		int osf_name;
		int ofs_filename;
		int num_parms;
		unsigned char parm_sizes[8];
	} *functions;

	/* strings */
	size_t len_strings;
	char *strings;

	/* field vars */
	size_t num_field_vars;
	struct qcvm_var {
		unsigned short type;
		unsigned short ofs;
		int name;
	} *field_vars;

	/* global vars */
	size_t num_global_vars;
	struct qcvm_var *global_vars;

	/* globals */
	size_t num_globals;
	union qcvm_global {
		float f;
		int i;
		unsigned int ui;
	} *globals;

} qcvm_t;

/** initialize qcvm structure
 *
 * this function parses the progs buffer and sets up pointers to the various
 * structures present in the file. it also checks for what features are
 * available, such as writeable progs memory and tempstrings.
 */
int qcvm_init(qcvm_t *qcvm);

/** get static string from result code
 */
const char *qcvm_result_string(int r);

/** queue up function for execution
 */
int qcvm_load(qcvm_t *qcvm, const char *name);

/** execute one qcvm step
 */
int qcvm_step(qcvm_t *qcvm);

/** queue up and execute the named function
 */
int qcvm_run(qcvm_t *qcvm, const char *name);

#ifdef __cplusplus
}
#endif
#endif /* _QCVM_H_ */

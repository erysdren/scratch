
#include <stddef.h>

typedef struct streambuffer {
	void *data;
	size_t read;
	size_t write;
	size_t current_size;
	size_t block_size;
} streambuffer_t;

streambuffer_t *streambuffer_new(size_t block_size)
{
	streambuffer_t *sb;

	if (!block_size)
		return 0;

	sb = calloc(1, sizeof(streambuffer_t));

	return sb;
}

void streambuffer_delete(streambuffer_t **sb)
{
	if (!sb)
		return;
	if (!*sb)
		return;

	free((*sb)->data);
	free(*sb);

	*sb = NULL;
}

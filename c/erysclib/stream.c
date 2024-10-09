
#include "stream.h"

enum {
	MODE_READ = 1 << 0,
	MODE_WRITE = 1 << 1,
	MODE_APPEND = 1 << 2
};

enum {
	TYPE_BINARY,
	TYPE_TEXT
};

struct stream {
	unsigned type;
	FILE *fp;
};

static int parse_mode(const char *mode)
{
	char *p;
	int flags = 0;

	if (!mode)
		return 0;
	if (mode[0] == '\0')
		return 0;

	p = (char *)mode;

	while (*p)
	{
		switch (*p)
		{

		}

		p++;
	}

	return flags;
}

/*
 * creation and destruction
 */

/* create stream from file - mode follows cstdlib */
stream_t *stream_from_file(const char *filename, const char *mode)
{
	stream_t *s = NULL;
	FILE *fp = NULL;

	fp = fopen(filename, mode);

	goto done;

fail:
	if (s) stream_delete(&s);
	if (fp) fclose(fp);
done:
	return s;
}

/* create stream from memory buffer */
stream_t *stream_from_buffer(void *buffer, size_t len, int readonly);

/* destroy stream and free all associated memory */
void stream_delete(stream_t **s)
{
	if ((*s)->fp)
		fclose((*s)->fp);

	free(*s);

	*s = NULL;
}

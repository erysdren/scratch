
#include "sys16.h"

/* create file and return handle */
file_t __attribute__((noinline)) file_create(const char __far *filename, uint16_t attribute)
{
	file_t file = 0;
	uint8_t flags = 0;

	asm (
		"int $0x21\n\t"
		"mov %%ax, %0\n\t"
		"jnc file_create_not_failed\n\t"
		"mov $0x1, %1\n\t"
		"file_create_not_failed:\n\t"
		: "=rm" (file), "=rm" (flags)
		: "a" (0x3c00), "c" (attribute), "Rds" (FP_SEG(filename)), "d" (FP_OFS(filename))
		: "memory"
	);

	/* carry flag wasn't set */
	if (flags == 0)
		return file;

	/* error checking and handling */
	switch (file)
	{
		case 3:
			print(str("path does not exist\n\r"));
			return 0;

		case 4:
			print(str("no handle available\n\r"));
			return 0;

		case 5:
			print(str("access denied\n\r"));
			return 0;

		default:
			print(str("unknown error creating file\n\r"));
			return 0;
	}
}

/* open file and return handle */
file_t __attribute__((noinline)) file_open(const char __far *filename, uint8_t mode)
{
	file_t file = 0;
	uint16_t ax = 0x3d00 | mode;
	uint8_t flags = 0;

	/* request file handle */
	asm (
		"int $0x21\n\t"
		"mov %%ax, %0\n\t"
		"jnc file_open_not_failed\n\t"
		"mov $0x1, %1\n\t"
		"file_open_not_failed:\n\t"
		: "=rm" (file), "=rm" (flags)
		: "a" (ax), "Rds" (FP_SEG(filename)), "d" (FP_OFS(filename))
		: "memory"
	);

	/* carry flag wasn't set */
	if (flags == 0)
		return file;

	/* try to create */
	if (mode == MODE_WRITE || mode == MODE_READWRITE)
		return file_create(filename, ATTR_NORMAL);

	/* error checking and handling */
	switch (file)
	{
		case 2:
			print(str("file not found\n\r"));
			return 0;

		case 3:
			print(str("path does not exist\n\r"));
			return 0;

		case 4:
			print(str("no handle available\n\r"));
			return 0;

		case 5:
			print(str("access denied\n\r"));
			return 0;

		case 0x0C:
			print(str("access code invalid\n\r"));
			return 0;

		default:
			print(str("unknown error opening file\n\r"));
			return 0;
	}
}

/* close file handle */
void file_close(file_t file)
{
	if (!file) return;

	/* close file handle */
	asm (
		"int $0x21\n\t"
		:
		: "a" (0x3e00), "b" (file)
		:
	);
}

/* write bytes to file */
uint16_t file_write(file_t file, void __far *data, uint16_t size)
{
	uint16_t written;

	asm (
		"int $0x21\n\t"
		"mov %%ax, %0\n\t"
		: "=rm" (written)
		: "a" (0x4000), "b" (file), "c" (size), "Rds" (FP_SEG(data)), "d" (FP_OFS(data))
		: "memory"
	);

	return written;
}

/* write string to file */
uint16_t file_print(file_t file, string s)
{
	return file_write(file, s.data, s.len);
}

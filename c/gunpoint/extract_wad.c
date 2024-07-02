
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifdef _WIN32
const char pathsep = '\\';
#else
const char pathsep = '/';
#endif

void create_file_path_dirs(char *file_path)
{
	char *dir_path = (char *)malloc(strlen(file_path) + 1);
	char *next_sep = strchr(file_path, pathsep);

	while (next_sep != NULL)
	{
		int dir_path_len = next_sep - file_path;
		memcpy(dir_path, file_path, dir_path_len);
		dir_path[dir_path_len] = '\0';
		mkdir(dir_path, S_IRWXU|S_IRWXG|S_IROTH);
		next_sep = strchr(next_sep + 1, pathsep);
	}

	free(dir_path);
}

int main(int argc, char **argv)
{
	FILE *fh;
	uint32_t len_header, num_files;
	uint32_t len_name, ofs_data, len_data;
	uint32_t pos;
	static char name[256];
	FILE *fx;
	void *data;

	fh = fopen("Gunpoint.wad", "rb");

	if (!fh)
	{
		printf("Failed to open file \"Gunpoint.wad\"\n");
		return 1;
	}

	fread(&len_header, 1, sizeof(uint32_t), fh);
	fread(&num_files, 1, sizeof(uint32_t), fh);

	for (int i = 0; i < num_files; i++)
	{
		memset(name, 0, sizeof(name));

		fread(&len_name, 1, sizeof(uint32_t), fh);
		fread(name, 1, len_name, fh);
		fread(&len_data, 1, sizeof(uint32_t), fh);
		fread(&ofs_data, 1, sizeof(uint32_t), fh);

		pos = ftell(fh);

		printf("%03d: \"%.*s\" - %d bytes at %d\n", i, len_name, name, len_data, ofs_data);

		create_file_path_dirs(name);

		fx = fopen(name, "wb");
		if (!fx)
		{
			fclose(fh);
			printf("Failed to open \"%.*s\"\n", len_name, name);
			return 1;
		}

		data = malloc(len_data);
		fseek(fh, ofs_data + len_header, SEEK_SET);
		fread(data, 1, len_data, fh);

		fwrite(data, 1, len_data, fx);

		free(data);
		fclose(fx);

		fseek(fh, pos, SEEK_SET);
	}

	fclose(fh);

	return 0;
}

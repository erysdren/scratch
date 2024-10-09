/*
MIT License

Copyright (c) 2024 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(x) ((void)(x))

const char test_document[] =
	"# hello world\n"
	"\n"
	"*em1*\n"
	"**em2**\n";

enum {
	TOKEN_NONE,
	TOKEN_WHITESPACE,
	TOKEN_NEWLINE,
	TOKEN_HEADING,
	TOKEN_LIST,
	TOKEN_LITERAL,
	TOKEN_EMPHASIS
};

static const char *token_types[] = {
	"NONE",
	"WHITESPACE",
	"NEWLINE",
	"HEADING",
	"LIST",
	"LITERAL",
	"EMPHASIS"
};

typedef struct token {
	struct token *next;
	struct token *prev;
	int type;
	char *contents;
	size_t len_contents;
} token_t;

token_t *token_new(void)
{
	return calloc(1, sizeof(token_t));
}

void token_delete(token_t *token, void *user)
{
	UNUSED(user);
	free(token->contents);
	free(token);
}

void token_print(token_t *token, void *user)
{
	UNUSED(user);
	printf("token type: %s\n", token_types[token->type]);
}

void token_walk_forwards(token_t *head, void(*callback)(token_t *token, void *user), void *user)
{
	token_t *token = head;

	while (token)
	{
		token_t *next = token->next;
		if (callback) callback(token, user);
		token = next;
	}
}

void token_walk_backbacks(token_t *tail, void(*callback)(token_t *token, void *user), void *user)
{
	token_t *token = tail;

	while (token)
	{
		token_t *prev = token->prev;
		if (callback) callback(token, user);
		token = prev;
	}
}

token_t *token_insert_before(token_t *here, token_t *token)
{
	token->next = here;
	token->prev = here->prev;

	if (here->prev)
		here->prev->next = token;

	here->prev = token;

	return token;
}

token_t *token_insert_after(token_t *here, token_t *token)
{
	token->prev = here;
	token->next = here->next;

	if (here->next)
		here->next->prev = token;

	here->next = token;

	return token;
}

int main(int argc, char **argv)
{
	token_t *head, *tail;

	head = token_new();

	tail = token_insert_after(head, token_new());

	token_walk_forwards(head, token_print, NULL);

	token_walk_forwards(head, token_delete, NULL);

	return 0;
}

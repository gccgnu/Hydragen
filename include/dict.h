#ifndef DICT_H
#define DICT_H

/* Including libraries */
#include <stdlib.h>
#include <string.h>

/* Defines */
#define DICT_SIZE 256

/* Structures */
typedef struct DictEntry {
	char *key;
	void *value;
	struct DictEntry *next;
} DictEntry;

typedef struct {
	DictEntry *buckets[DICT_SIZE];
} Dict;

/* Functions */

static unsigned int
dict_hash(const char *key)
{
	unsigned int hash = 0;
	while (*key) {
		hash = (hash * 31) + *key++;
	}
	return hash % DICT_SIZE;
}

static Dict*
dict_new(void)
{
	Dict *d = (Dict*)calloc(1, sizeof(Dict));
	return d;
}

static void
dict_set(Dict *d, const char *key, void *value)
{
	unsigned int h = dict_hash(key);
	DictEntry *e = d->buckets[h];
	
	while (e) {
		if (strcmp(e->key, key) == 0) {
			e->value = value;
			return;
		}
		e = e->next;
	}
	
	DictEntry *new_entry = (DictEntry*)malloc(sizeof(DictEntry));
	new_entry->key = strdup(key);
	new_entry->value = value;
	new_entry->next = d->buckets[h];
	d->buckets[h] = new_entry;
}

static void*
dict_get(Dict *d, const char *key)
{
	unsigned int h = dict_hash(key);
	DictEntry *e = d->buckets[h];
	
	while (e) {
		if (strcmp(e->key, key) == 0) {
			return e->value;
		}
		e = e->next;
	}
	return NULL;
}

static int
dict_has(Dict *d, const char *key)
{
	return dict_get(d, key) != NULL;
}

static void
dict_remove(Dict *d, const char *key)
{
	unsigned int h = dict_hash(key);
	DictEntry *e = d->buckets[h];
	DictEntry *prev = NULL;
	
	while (e) {
		if (strcmp(e->key, key) == 0) {
			if (prev) {
				prev->next = e->next;
			} else {
				d->buckets[h] = e->next;
			}
			free(e->key);
			free(e);
			return;
		}
		prev = e;
		e = e->next;
	}
}

static void
dict_free(Dict *d)
{
	int i;
	for (i = 0; i < DICT_SIZE; i++) {
		DictEntry *e = d->buckets[i];
		while (e) {
			DictEntry *next = e->next;
			free(e->key);
			free(e);
			e = next;
		}
	}
	free(d);
}

/* Macros for convenience */
#define dict_set_int(d, key, val)		dict_set(d, key, (void*)(long)(val))
#define dict_get_int(d, key)				((int)(long)dict_get(d, key))
#define dict_set_ptr(d, key, val)		dict_set(d, key, (void*)(val))
#define dict_get_ptr(d, key)				dict_get(d, key)

#endif
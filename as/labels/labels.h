#pragma once

/* Including libraries */
#include <stdio.h>
#include <string.h>

#include "../../include/dict.h"
#include "../../include/type.h"

/* Structures */
typedef struct {
	Dict *dict;
	u32 count;
} Labels;

/* Result codes */
typedef enum {
	LABEL_OK = 0,
	LABEL_ERROR_NULL_PTR,
	LABEL_ERROR_ALREADY_EXISTS,
	LABEL_ERROR_NOT_FOUND,
	LABEL_ERROR_INVALID_NAME
} LabelResult;

/* Function prototypes */
Labels* labels_init(void);
void labels_free(Labels *labels);
LabelResult labels_add(Labels *labels, const char *name, u32 address);
int labels_exists(Labels *labels, const char *name);
LabelResult labels_find(Labels *labels, const char *name, u32 *address);
int32_t labels_get_address(Labels *labels, const char *name);
LabelResult labels_remove(Labels *labels, const char *name);
size_t labels_count(Labels *labels);
LabelResult labels_update(Labels *labels, const char *name, u32 new_address);
LabelResult labels_set(Labels *labels, const char *name, u32 address);
void labels_debug_print(Labels *labels);
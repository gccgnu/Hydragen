/* Including header file */
#include "labels.h"

/* Table labels init */
Labels*
labels_init(void)
{
	Labels *labels = (Labels*)malloc(sizeof(Labels));
	if (!labels) return NULL;

	labels->dict = dict_new();
	if (!labels->dict) {
		free(labels);
		return NULL;
	}

	labels->count = 0;
	return labels;
}

/* Remove labels table */
void
labels_free(Labels *labels)
{
	if (!labels) return;

	if (labels->dict) {
		dict_free(labels->dict);
	}

	free(labels);
}

/* Label validator */
static int
labels_is_valid_name(const char *name)
{
	if (!name || *name == '\0') return 0;
    
	/* First character: letter or _ */
	if (!((*name >= 'a' && *name <= 'z') ||
		(*name >= 'A' && *name <= 'Z') ||
		*name == '_')) {
		return 0;
	}

	/* Other characters: letters, numbers, or _ */
	const char *p = name + 1;
	while (*p) {
		if (!((*p >= 'a' && *p <= 'z') ||
			(*p >= 'A' && *p <= 'Z') ||
			(*p >= '0' && *p <= '9') ||
			*p == '_')) {
			return 0;
		}
		p++;
	}

	return 1;
}

/* Add label */
LabelResult
labels_add(Labels *labels, const char *name, u32 address)
{
	if (!labels || !name) return LABEL_ERROR_NULL_PTR;
    
	/* Name validity check */
	if (!labels_is_valid_name(name)) {
		return LABEL_ERROR_INVALID_NAME;
	}
    
	/* Existence check */
	if (dict_has(labels->dict, name)) {
		return LABEL_ERROR_ALREADY_EXISTS;
	}
    
	/* Adding a label (address + 1 to distinguish from NULL/0) */
	dict_set_int(labels->dict, name, (long)(address + 1));
	labels->count++;

	return LABEL_OK;
}

/* Checking the existence of a label */
int
labels_exists(Labels *labels, const char *name)
{
	if (!labels || !name) return 0;
	return dict_has(labels->dict, name);
}

/* Finding a label and getting the address
   Returns LABEL_OK on success, the address is written to *address */
LabelResult
labels_find(Labels *labels, const char *name, u32 *address)
{
	if (!labels || !name || !address) return LABEL_ERROR_NULL_PTR;
	if (!dict_has(labels->dict, name)) return LABEL_ERROR_NOT_FOUND;

	/* We get the value and subtract 1 (see labels_add) */
	long val = dict_get_int(labels->dict, name);
	*address = (u32)(val - 1);
    
	return LABEL_OK;
}

/* Getting the label address (convenient shell) */
int32_t
labels_get_address(Labels *labels, const char *name)
{
	u32 address;

	if (labels_find(labels, name, &address) != LABEL_OK) return -1;
	return (int32_t)address;
}

/* Remove label */
LabelResult
labels_remove(Labels *labels, const char *name)
{
	if (!labels || !name) return LABEL_ERROR_NULL_PTR;
	if (!dict_has(labels->dict, name)) return LABEL_ERROR_NOT_FOUND;
    
	dict_remove(labels->dict, name);
	labels->count--;
    
	return LABEL_OK;
}

/* Getting the nubmer of labels */
size_t
labels_count(Labels *labels)
{
	if (!labels) return 0;
	return labels->count;
}

/* Updating address labels */
LabelResult
labels_update(Labels *labels, const char *name, u32 new_address)
{
	if (!labels || !name) return LABEL_ERROR_NULL_PTR;
	if (!dict_has(labels->dict, name)) return LABEL_ERROR_NOT_FOUND;

	dict_set_int(labels->dict, name, (long)(new_address + 1));

	return LABEL_OK;
}

/* Adding or updating a label */
LabelResult
labels_set(Labels *labels, const char *name, u32 address)
{
	if (!labels || !name) return LABEL_ERROR_NULL_PTR;

	if (!labels_is_valid_name(name)) return LABEL_ERROR_INVALID_NAME;
    
	if (dict_has(labels->dict, name))
		return labels_update(labels, name, address);
	else
		return labels_add(labels, name, address);
}

/* Debug output of all labels */
void
labels_debug_print(Labels *labels)
{
	if (!labels || !labels->dict) {
		printf("Labels: (null)\n");
		return;
	}

	printf("Labels (%zu entries):\n", labels->count);

	int i;
	for (i = 0; i < DICT_SIZE; i++) {
		DictEntry *e = labels->dict->buckets[i];
		while (e) {
			long val = (long)e->value;
			printf("  %-20s = 0x%08X (%u)\n", 
							e->key, 
							(u32)(val - 1),
							(u32)(val - 1));
			e = e->next;
		}
	}
}
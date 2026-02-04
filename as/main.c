/* Including libraries */
#include <stdio.h>
#include "labels/labels.h"
#include "../include/type.h"

/* Entry point */
int
main(int argc, char *argv[])
{
	(void) argc; (void)argv;
	//printf("Hello, World!\n");
		
	/* Testing label manager */
	Labels *labels = labels_init();
	if (!labels) {
		fprintf(stderr, "Failed to init labels\n");
		return 1;
	}

	/* Adding labels */
	labels_add(labels, "start", 0x0000);
	labels_add(labels, "loop", 0x0010);
	labels_add(labels, "end", 0x0100);
	labels_add(labels, "data_section", 0x1000);
    
	/* Finding labels */
	u32 addr;
	if (labels_find(labels, "loop", &addr) == LABEL_OK) {
		printf("Label 'loop' found at address: 0x%04X\n", addr);
	}
    
	/* And labels_get_address */
	i32 result = labels_get_address(labels, "end");
	if (result >= 0) {
		printf("Label 'end' found at address: 0x%04X\n", result);
	}
    
	/* Check exists */
	if (labels_exists(labels, "start")) {
		printf("Label 'start' exists\n");
	}
    
	/* Try add alerdy exist label */
	if (labels_add(labels, "loop", 0x0020) == LABEL_ERROR_ALREADY_EXISTS) {
		printf("Label 'loop' already exists!\n");
	}
    
	/* Update address */
	labels_update(labels, "loop", 0x0020);
    
	/* Debug output */
	printf("Before removing:\n");
	labels_debug_print(labels);

	labels_remove(labels, "data_section");

	printf("After removing:\n");
	labels_debug_print(labels);
    
	/* Free label */
	labels_free(labels);

	return 0;
}
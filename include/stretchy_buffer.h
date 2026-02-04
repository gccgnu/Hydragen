#ifndef STRETCHY_BUFFER_H
#define STRETCHY_BUFFER_H

/* Including libraries */
#include <stdlib.h>

/* Defines */
#define sb_free(a)					((a) ? free(sb__raw(a)),0 : 0)
#define sb_push(a,v)				(sb__maybegrow(a,1), (a)[sb__n(a)++] = (v))
#define sb_count(a)					((a) ? sb__n(a) : 0)
#define sb_add(a,n)					(sb__maybegrow(a,n), sb__n(a)+=(n), &(a)[sb__n(a)-(n)])
#define sb_last(a)					((a)[sb__n(a)-1])

#define sb__raw(a)					((int *) (a) - 2)
#define sb__m(a)						sb__raw(a)[0]
#define sb__n(a)						sb__raw(a)[1]

#define sb__needgrow(a,n)		((a)==0 || sb__n(a)+(n) >= sb__m(a))
#define sb__maybegrow(a,n)	(sb__needgrow(a,(n)) ? sb__grow(a,n) : 0)
#define sb__grow(a,n)				(*((void **)&(a)) = sb__growf((a), (n), sizeof(*(a))))

#endif
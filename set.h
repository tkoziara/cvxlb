/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Tomasz Koziara
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * set.h: rb-tree based set container
 */

#include "mem.h"

#ifndef __set__
#define __set__

typedef struct set SET; /* set type */
typedef int (*SET_Compare) (void*, void*); /* comparison callback */

struct set
{
  SET *p, *l, *r; /* parent, left, right */
  char colour; /* red, blue */
  void *data; /* user data */
};

/* insert an element into the set (return NULL if the data already is in the set) */
SET* SET_Insert (MEM *pool, SET **root,
  void *data, SET_Compare compare); /* 'compare' == NULL 
					=> direct pointer 'data' comparison 
					(this applies below as well) */

/* find an element */
void* SET_Find (SET *root, void *data , SET_Compare compare);

/* check if an element is already in the set */
int SET_Contains (SET *root, void *data , SET_Compare compare);

/* delete an element from the set */
void SET_Delete (MEM *pool, SET **root, void *data, SET_Compare compare);

/* delete a specific set node => return the next node by key */
SET* SET_Delete_Node (MEM *pool, SET **root, SET *node);

/* postorder traverse and free set memory */
void SET_Free (MEM *pool, SET **root);

/* copy set */
SET* SET_Copy (MEM *pool, SET *root);

/* return number of items */
int SET_Size (SET *root);

/* first element */
SET* SET_First (SET *root);

/* last element */
SET* SET_Last (SET *root);

/* previous element */
SET* SET_Prev (SET *node);

/* next element */
SET* SET_Next (SET *node);

#endif

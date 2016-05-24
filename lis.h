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
 * lis.h: list merge sort
 */

#include <limits.h>

#ifndef __lis__
#define __lis__

#define DOUBLY_LINKED(PREV, NEXT) for (i = list; i; j = i, i = i->NEXT) i->PREV = j;

#define SINGLE_LINKED(PREV, NEXT)

#define IMPLEMENT_LIST_SORT(KIND, CALL, LIST, PREV, NEXT, LE)\
static LIST* CALL (LIST *list)\
{\
  LIST *i, *j, *k, *h, *t;\
  int l, m, n;\
\
  for (l = 1; l < INT_MAX;l *= 2)\
  {\
    h = t = NULL;\
\
    for (j = list;;)\
    {\
      i = j;\
\
      for (m = 0; m < l && j; j = j->NEXT, m ++);\
      for (n = 0, k = j; n < l && k; k = k->NEXT, n ++);\
\
      if (!j && i == list)\
      {\
	KIND (PREV, NEXT)\
	return list;\
      }\
      else if (!(m+n)) break;\
\
      if (!h) h = (LE (i, j) ? i : j);\
\
      for (; m && n;)\
      {\
	if (LE (i, j))\
	{\
	  if (t) t->NEXT = i;\
	  t = i;\
	  i = i->NEXT;\
	  m --;\
	}\
	else\
	{\
	  if (t) t->NEXT = j;\
	  t = j;\
	  j = j->NEXT;\
	  n --;\
	}\
      }\
\
      while (m)\
      {\
	t->NEXT = i;\
	t = i;\
	i = i->NEXT;\
	m --;\
      }\
\
      while (n)\
      {\
	t->NEXT = j;\
	t = j;\
	j = j->NEXT;\
	n --;\
      }\
    }\
\
    t->NEXT = NULL;\
    list = h;\
  }\
\
  return list;\
}

#endif

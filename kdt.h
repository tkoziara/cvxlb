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
 * kdt.h: kd-tree based map
 */

#include "set.h"

#ifndef __kdt__
#define __kdt__

typedef struct kdt KDT;

struct kdt
{
  double p [3]; /* point or invalid for a leaf */

  int d; /* splitting dimension or -1 for a leaf */

  KDT *u, *l, *r; /* upper, left and right branch */

  int n; /* tree node index or leaf data items count */

  void **data; /* leaf data items */
};

/* create kd-tree for n points; epsilon separation is ensured
 * between the input points and the remaining points are filtered our */
KDT* KDT_Create (int n, double *p, double epsilon);

/* drop data down the kd-tree */
void KDT_Drop (KDT *kd, double *extents, void *data);

/* pick leaf containing point */
KDT* KDT_Pick (KDT *kd, double *p);

/* pick leaves overlapping the extents */
void KDT_Pick_Extents (KDT *kd, double *extents, SET **leaves);

/* return nearest node in kd-tree within epsilon radius */
KDT* KDT_Nearest (KDT *kd, double *p, double epsilon);

/* return the number kd-tree nodes; note that kd->n indices
 * become valid for tree nodes only after KDT_Size was called */
int KDT_Size (KDT *kd);

/* first node */
KDT* KDT_First (KDT *kd);

/* next node */
KDT* KDT_Next (KDT *kd);

/* destroy kd-tree */
void KDT_Destroy (KDT *kd);

#endif

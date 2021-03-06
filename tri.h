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
 * tri.h: three-dimensional triangle
 */

#include "kdt.h"

#ifndef __tri__
#define __tri__

typedef struct triangle TRI; /* surface triangle */
struct triangle
{
  double out [3], /* outward normal */
        *ver [3]; /* vertices (CCW) */
  TRI   *adj [3]; /* adjacent triangles (ordered: adj[0] <=> ver[0]-ver[1], ...) */
  int    flg;     /* flag(s) => used in external algorithms */
  void  *ptr;     /* used by external algorithms */
};

typedef struct triangle_surface TRISURF; /* triangulized surface */
struct triangle_surface
{
  double center [3]; /* mass center of the volume enclosed by the surface */
  double volume; /* volume of the enclosed solid */
  TRI *tri; /* triangles and related data as outputed by 'cvi' */
  int m; /* number of triangles as outputed by 'cvi' */
};

typedef struct polar_face_vertex PFV; /* vertex of a polar face */
struct polar_face_vertex
{
  double *coord, /* vertex coordinate => this is -pla[0-2]/pla[3] */
	 *nl;    /* outward normal => points to 'ver' in TRI, hence not normalised */
  PFV    *n;     /* next CCW vertex in a circular list */
};

/* sort adjacency as specified above */
void TRI_Sortadj (TRI *tri);

/* make 'p' and 'q' adjacent, assuming
 * there is enough NULL space in 'adj's;
 * return 0 on fault, 1 otherwise */
int TRI_Addadj (TRI *p, TRI *q);

/* copy triangles into a continuous memory block;
 * vertices are placed right after the returned table */
TRI* TRI_Copy (TRI *tri, int n);

/* merge two triangulations; adjacency is not maintained */
TRI* TRI_Merge (TRI *one, int none, TRI *two, int ntwo, int *m);

/* compute adjacency structure */
void TRI_Compadj (TRI *tri, int n);

/* intput a triangulation and a point; output the same triangulation
 * but reordered so that the first 'm' triangles are topologically
 * adjacent to the point; no memory is allocated in this process;
 * return NULL and *m = 0 if no input triangle is near the input point;
 * NOTE => tri->flg will be modified for all input triangles */
TRI* TRI_Topoadj (TRI *tri, int n, double *point, int *m);

/* input => convex polyhedron containing zero (tri, n);
 * output => polar polyhedron defined by 'm' vertex lists;
 * a continuous block of memory is returned; 'nl's point to 'ver'
 * members in 'tri'; 'coord's point within the returned block */
PFV* TRI_Polarise (TRI *tri, int n, int *m);

/* extract vertices of triangulation (tri, n)
 * into a table of size (double [3]) x m */
double* TRI_Vertices (TRI *tri, int n, int *m);

/* extract planes of triangulation (tri, n)
 * into a table of size (double [6]) x m, where
 * each plane is represented by (normal, point) */
double* TRI_Planes (TRI *tri, int n, int *m);

/* compute mass center and volume of triangulated solid */
double TRI_Char (TRI *tri, int n, double *center);

/* create triangulation based kd-tree;
 * nodes store triangle-extents-dropped triangle sets */
KDT* TRI_Kdtree (TRI *tri, int n);

/* compute extents of a single triangle */
void TRI_Extents (TRI *t, double *extents);

#endif

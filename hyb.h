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
 * hyb.c:
 * box overlap detection using the hybrid streamed segment tree described in:
 * Afran Zomorodian, Herbert Edelsbrunner, "Fast software for box intersection",
 * 2002, International Journal of Computer Geometry and Applications, Vol. 12,
 * Numbers 1-2, pp. 142-172.
 */

#ifndef __hyb__
#define __hyb__

typedef struct box BOX; /* axis aligned box */

/* bounding box */
struct box
{
  double extents [6]; /* min x, y, z, max x, y, z */

  void *sgp; /* shape and geometric object pair */

  void *body; /* owner of the shape */

  void *mark; /* auxiliary marker used by hashing algorithms */
};

typedef void (*BOX_Overlap_Create)  (void *data, BOX *one, BOX *two); /* created overlap callback => returns a user pointer */

/* report overlaps between n boxes */
void hybrid (BOX **boxes, int n, void *data, BOX_Overlap_Create create);

/* report overlaps between two sets of boxes */
void hybrid_ext (BOX **seta, int na, BOX **setb, int nb, void *data, BOX_Overlap_Create create);

#endif

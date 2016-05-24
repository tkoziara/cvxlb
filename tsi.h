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
 * tsi.h: triangle-sphere intersection
 */

#ifndef __tsi__
#define __tsi__

enum
{
  TSI_A = 0,
  TSI_B,
  TSI_C,
  TSI_A_B,
  TSI_B_C,
  TSI_C_A,
  TSI_A_B_C,
  TSI_A_BC,
  TSI_B_CA,
  TSI_C_AB,
  TSI_AB,
  TSI_BC,
  TSI_CA,
  TSI_AB_BC,
  TSI_BC_CA,
  TSI_CA_AB,
  TSI_AB_BC_CA,
  TSI_BUBBLE,
  TSI_OUT
};

/* get status of intersection between triangle (a, b, c) and sphere (p, r) */
int TSI_Status (double *a, double *b, double *c, double *p, double r);

/* approximate intersection of triangle (a, b, c) and sphere (p, r) with second order triangular elements;
 * output vector 'cc' contains 'ncc' 2-dimensional points in the natural coordinates of the input triangle;
 * output triangulation 'tt' contains 'ntt' 6-vertex second order triangle vertex numbers, refering to 'cc';
 * output arrays are dynamically allocated; the status of the intersection is returned */
int TSI_Approx (double *a, double *b, double *c, double *p, double r, double **cc, int *ncc, int **tt, int *ntt);

#endif

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
 * spx.c: simplex integration related routines
 */

#include "spx.h"

double simplex_J (double *a, double *b, double *c, double *d)
{
  double q [9], J;

  q [0] = b [0] - a [0];
  q [1] = c [0] - a [0];
  q [2] = d [0] - a [0];
  q [3] = b [1] - a [1];
  q [4] = c [1] - a [1];
  q [5] = d [1] - a [1];
  q [6] = b [2] - a [2];
  q [7] = c [2] - a [2];
  q [8] = d [2] - a [2];

  J = q [0]*q [4]*q [8] + q [3]*q [7]*q [2] + q [6]*q [1]*q [5] -
      q [6]*q [4]*q [2] - q [0]*q [7]*q [5] - q [3]*q [1]*q [8];

  return J;
}

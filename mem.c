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
 * mem.c: memory pool
 */

#include <string.h>
#include <stdlib.h>
#include "mem.h"
#include "err.h"

#if MEMDEBUG
#include "set.h"
#endif

typedef struct { void *p; size_t margin; } PTR; /* pointer with margin */

void* MEM_CALLOC (size_t size)
{
  void *chunk;

  if (!(chunk = malloc (size))) return NULL;

  memset (chunk, 0, size);

  return chunk;
}

void MEM_Init (MEM *pool, size_t chunksize, size_t chunksinblock)
{
  ASSERT_DEBUG (pool && chunksize > 0 && chunksinblock > 0, "A zero argument passed to MEM_Init");

  /* set chunksize not less than 'unsigned long' size
   * as wee plan to use chunks as items of 'deadchunks' list */
  pool->chunksize = (chunksize > sizeof(PTR) ? chunksize : sizeof(PTR));
  pool->chunksinblock = chunksinblock;
  pool->blocks = NULL;
  pool->freechunk = NULL;
  pool->lastchunk = NULL;
  pool->deadchunks = NULL;
}

void* MEM_Alloc (MEM *pool)
{
#if MEMDEBUG
  void *chunk;

  if (!(chunk = malloc (pool->chunksize))) return NULL;
  memset (chunk, 0, pool->chunksize);

  SET_Insert (NULL, (SET**) &pool->blocks, chunk, NULL);

  return chunk;
#else
  void *chunk, *block;

  if (pool->deadchunks)
  { /* if there are deallocated chunks, get one */
	  
    chunk = pool->deadchunks;
    pool->deadchunks = ((PTR*)pool->deadchunks)->p;
    memset (chunk, 0, pool->chunksize);
    return chunk;
  }
  else if (pool->freechunk == pool->lastchunk)
  { /* else if we need to allocate a new block ... */
   
    /* allocate a block of memory */
    block = malloc (pool->chunksize * pool->chunksinblock + sizeof(PTR));
    if (!block) return NULL; /* do not exit() here */
    memset (block, 0, pool->chunksize * pool->chunksinblock + sizeof(PTR));
   
    /* insert allocated block into the list */
    ((PTR*)block)->p = pool->blocks;
    pool->blocks = block;
    /* set free and last chunk */
    pool->freechunk = (char*)block + sizeof(PTR);
    pool->lastchunk = pool->freechunk + pool->chunksize * pool->chunksinblock;
  }

  chunk = pool->freechunk;
  pool->freechunk += pool->chunksize;
  return chunk;
#endif
}

void MEM_Free (MEM *pool, void *chunk)
{
#if MEMDEBUG
  if (!SET_Contains ((SET*)pool->blocks, chunk, NULL))
  {
    ASSERT_DEBUG (0, "Deletion from invalid memory pool");
  }

  SET_Delete (NULL, (SET**) &pool->blocks, chunk, NULL);

  free (chunk);
#else
  /* insert chunk into dead chunks list */
  ((PTR*)chunk)->p = pool->deadchunks;
  pool->deadchunks = chunk;
#endif
}

size_t MEM_Size (MEM *pool)
{
#ifdef MEMDEBUG
  return SET_Size (pool->blocks) * pool->chunksize;
#else
  size_t size = 0, chunk = pool->chunksize *
    pool->chunksinblock + sizeof(PTR);

  void *block = pool->blocks;

  /* loop over all blocks */  
  while (block)
  {
    block = ((PTR*)block)->p;
    size += chunk;
  }

  return size;
#endif
}

void MEM_Release (MEM *pool)
{
#if MEMDEBUG
  for (SET *item = SET_First (pool->blocks); item; item = SET_Next (item)) free (item->data);

  SET_Free (NULL, (SET**) &pool->blocks);
#else
  void *block = pool->blocks;
  size_t next;
  
  /* traverse and free all blocks of memory */
  while (block)
  {
    next = *((size_t*)block);
    free (block);
    block = (void*)next;
  }
#endif

  pool->blocks = NULL;
  pool->freechunk = NULL;
  pool->lastchunk = NULL;
  pool->deadchunks = NULL;
}

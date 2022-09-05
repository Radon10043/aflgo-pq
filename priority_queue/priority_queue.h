/*
 * @Author: Radon
 * @Date: 2022-09-05 16:36:14
 * @LastEditors: Radon
 * @LastEditTime: 2022-09-05 17:03:11
 * @Description: Hi, say something
 */
#ifndef _HAVE_PRIORITY_QUEUE_H
#define _HAVE_PRIORITY_QUEUE_H

#include "../config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

/* 最小堆 */

typedef struct heap {
  u64 size;     // 堆目前的大小
  u64 max_size; // 堆最大容量
  s32 *arr;     // 数组
} heap, priority_queue;

/* Functions */

void swap(s32 *a, s32 *b);

void init_pqueue(heap *ptr);

void push_to_pqueue(heap *ptr, s32 value);

s32 get_pqueue_front(heap *ptr);

void pop_from_pqueue(heap *ptr);

#endif /* _HAVE_PRIORITY_QUEUE_H */
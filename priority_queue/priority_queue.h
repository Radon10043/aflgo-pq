/*
 * @Author: Radon
 * @Date: 2022-09-07 20:21:06
 * @LastEditors: Radon
 * @LastEditTime: 2022-09-08 18:51:32
 * @Description: Hi, say something
 */
#ifndef _HAVE_PRIORITY_QUEUE_H
#define _HAVE_PRIORITY_QUEUE_H

#include "../config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define true 1
#define false 0
#define EPS 1e-6
#define element seed

/* 存储种子信息的结构体 */

typedef struct seed {
  u8 *fname;
  double distance;
} seed;

/* 最小堆 */

typedef struct heap {
  u64 size;                                               // 堆目前的大小
  u64 max_size;                                           // 堆最大容量
  element *arr;                                           // 数组
  s8 (*fptr)(const element *const, const element *const); // 函数指针, 指向比较函数
} heap, priority_queue;

/* Functions */

void swap(element *a, element *b);

priority_queue* init_pqueue();  // TODO: param带上比较函数?

void push_to_pqueue(priority_queue *ptr, element *value);

element *get_pqueue_front(priority_queue *ptr);

void pop_from_pqueue(priority_queue *ptr);

#endif /* _HAVE_PRIORITY_QUEUE_H */
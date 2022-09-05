/*
 * @Author: Radon
 * @Date: 2022-08-15 16:01:30
 * @LastEditors: Radon
 * @LastEditTime: 2022-09-05 17:03:41
 * @Description: Hi, say something
 */
#include "priority_queue.h"

/**
 * @brief 交换a和b的值
 *
 * @param a
 * @param b
 */
void swap(s32 *a, s32 *b) {
  s32 temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * @brief 初始化优先队列
 *
 * @param ptr 指向优先队列的指针
 */
void init_pqueue(priority_queue *ptr) {
  ptr->size = 0;
  ptr->max_size = 1;
  ptr->arr = (s32 *)malloc(sizeof(s32) * ptr->max_size);
}

/**
 * @brief 将元素添加到优先队列, 并进行调整
 *
 * @param ptr 指向的优先队列
 * @param value 添加的值
 */
void push_to_pqueue(priority_queue *ptr, s32 value) {

  /* 超出最大容量的话需要扩展 */

  if (ptr->size + 1 > ptr->max_size) {

    /* 申请一个容量为原先两倍的数组, 并把旧数组中的内容拷贝过去 */

    s32 *new_arr = (s32 *)malloc(sizeof(s32) * (ptr->max_size << 1));
    memcpy(new_arr, ptr->arr, sizeof(s32) * ptr->max_size);

    /* 旧数组没用了, free掉. 结构体的arr指向新数组的首地址 */

    free(ptr->arr);
    ptr->arr = new_arr;

    /* 更改 max_size */

    ptr->max_size <<= 1; // FIXME: 可能存在溢出问题 (概率不大)
  }

  /* 将值插入堆中 */

  ptr->arr[ptr->size++] = value;

  /* 调整堆 */

  s32 now = ptr->size - 1;
  while (now > 0 && ptr->arr[now] < ptr->arr[(now - 1) >> 1]) {
    swap(&ptr->arr[now], &ptr->arr[(now - 1) >> 1]);
    now = (now - 1) >> 1;
  }
}

/**
 * @brief 获取堆顶元素, 若堆为空则返回-1
 *
 * @param ptr 指向的堆
 * @return s32 堆顶元素
 */
s32 get_pqueue_front(priority_queue *ptr) {
  if (ptr->size <= 0) {
    printf("Empty priority_queue ? Return -1.");
    return -1;
  }
  return ptr->arr[0];
}

/**
 * @brief 删除堆顶元素(优先队列的队首元素), 并调整堆
 *
 * @param ptr 指向的堆
 */
void pop_from_pqueue(priority_queue *ptr) {

  /* heap为空时不做任何操作 */

  if (ptr->size <= 0) {
    printf("There is no elements in priority_queue, return.");
    return;
  }

  /* 堆顶元素与最后一个元素互换 */

  swap(&ptr->arr[0], &ptr->arr[ptr->size - 1]);
  ptr->size--;

  /* 从堆顶开始调整堆 */

  s32 now = 0;
  while (true) {

    /* 获得左孩子和右孩子的下标 */

    s32 left = (now << 1) + 1, right = (now << 1) + 2;

    /* 如果当前节点是叶子节点 */

    if (left >= ptr->size)
      break;

    /* 如果只有左孩子 */

    if (left < ptr->size && right >= ptr->size) {
      if (ptr->arr[left] < ptr->arr[now])
        swap(&ptr->arr[now], &ptr->arr[left]);
      break;
    }

    /* 如果左右孩子都有 */

    /* 若左右孩子都比自己大, break */

    if (ptr->arr[left] >= ptr->arr[now] && ptr->arr[right] >= ptr->arr[now])
      break;

    /* 和更小的孩子交换value */

    s32 next_loc = left;
    if (ptr->arr[right] < ptr->arr[left])
      next_loc = right;

    swap(&ptr->arr[now], &ptr->arr[next_loc]);
    now = next_loc;
  }
}
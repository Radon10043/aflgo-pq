/*
 * @Author: Radon
 * @Date: 2022-08-15 16:01:30
 * @LastEditors: Radon
 * @LastEditTime: 2022-09-07 20:23:19
 * @Description: Hi, say something
 */
#include "priority_queue.h"

/**
 * @brief 比较函数, a的距离大返回1, b的距离大返回-1, 相等返回0
 *
 * @param a
 * @param b
 * @return s8
 */
s8 mycmp(const seed *const a, const seed *const b) {
  if (a->distance > b->distance)
    return 1;
  else if (a->distance == b->distance)
    return 0;
  return -1;
}

/**
 * @brief 交换a和b的值
 *
 * @param a
 * @param b
 */
void swap(element *a, element *b) {
  element temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * @brief 初始化堆
 *
 * @param ptr 指向堆的指针
 */
void init_pqueue(priority_queue *ptr) {
  ptr->size = 0;
  ptr->max_size = 1;
  ptr->arr = (element *)malloc(sizeof(element) * ptr->max_size);
  ptr->fptr = &mycmp;
}

/**
 * @brief 将元素添加到堆, 并进行调整
 *
 * @param ptr 指向的堆
 * @param value 添加的值
 */
void push_to_pqueue(priority_queue *ptr, element *value) {

  /* 超出最大容量的话需要扩展 */

  if (ptr->size + 1 > ptr->max_size) {

    /* 申请一个容量为原先两倍的数组, 并把旧数组中的内容拷贝过去 */

    element *new_arr = (element *)malloc(sizeof(element) * (ptr->max_size << 1));
    memcpy(new_arr, ptr->arr, sizeof(element) * ptr->max_size);

    /* 旧数组没用了, free掉. 结构体的arr指向新数组的首地址 */

    free(ptr->arr);
    ptr->arr = new_arr;

    /* 更改 max_size */

    ptr->max_size <<= 1; // FIXME: 可能存在溢出问题 (概率不大)
  }

  /* 将值插入堆中 */

  ptr->arr[ptr->size++] = *value;

  /* 调整堆, 如果插入的值比父母要小的话就交换 */

  u64 now = ptr->size - 1;
  while (now > 0 && ptr->fptr(&ptr->arr[now], &ptr->arr[(now - 1) >> 1]) < 0) {
    swap(&ptr->arr[now], &ptr->arr[(now - 1) >> 1]);
    now = (now - 1) >> 1;
  }
}

/**
 * @brief 获取堆顶元素, 若堆为空则返回NULL
 *
 * @param ptr 指向的堆
 * @return element* 堆顶元素
 */
element *get_pqueue_front(priority_queue *ptr) {
  if (ptr->size <= 0) {
    printf("Empty priority_queue ? Return NULL.");
    return NULL;
  }
  return &ptr->arr[0];
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

  u64 now = 0;
  while (true) {

    /* 获得左孩子和右孩子的下标 */

    u64 left = (now << 1) + 1, right = (now << 1) + 2;

    /* 如果当前节点是叶子节点 */

    if (left >= ptr->size)
      break;

    /* 如果只有左孩子 */

    if (left < ptr->size && right >= ptr->size) {
      if (ptr->fptr(&ptr->arr[left], &ptr->arr[now]) < 0)
        swap(&ptr->arr[now], &ptr->arr[left]);
      break;
    }

    /* 如果左右孩子都有 */

    /* 若左右孩子都比自己大, break */

    if (ptr->fptr(&ptr->arr[left], &ptr->arr[now]) >= 0 && ptr->fptr(&ptr->arr[right], &ptr->arr[now]) >= 0)
      break;

    /* 和更小的孩子交换value */

    u64 next_loc = left;
    if (ptr->fptr(&ptr->arr[right], &ptr->arr[left]) < 0)
      next_loc = right;

    swap(&ptr->arr[now], &ptr->arr[next_loc]);
    now = next_loc;
  }
}

/********** Debug **********/

#if 0

void test_s32() {
  s32 arr[5] = {5, 4, 3, 2, 1};

  /* 目前是数小的元素在队首 (堆顶) */

  priority_queue *pq = (priority_queue *)malloc(sizeof(priority_queue));
  init_pqueue(pq);

  for (s32 i = 0; i < 5; i++) {
    push_to_pqueue(pq, arr + i);
  }

  for (s32 i = 0; i < 5; i++) {
    pop_from_pqueue(pq);
  }
}

#else

void test_seed() {
  seed s[5];
  for (int i = 0; i < 5; i++) {
    s[i].distance = 5 - i;
    s[i].fname = NULL;
  }

  priority_queue *pq = (priority_queue *)malloc(sizeof(priority_queue));
  init_pqueue(pq);

  for (s32 i = 0; i < 5; i++)
    push_to_pqueue(pq, &s[i]);
  for (s32 i = 0; i < 5; i++)
    pop_from_pqueue(pq);
}

#endif

int main(int argc, char **argv) {
  test_seed();
  return 0;
}
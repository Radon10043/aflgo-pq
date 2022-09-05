/*
 * @Author: Radon
 * @Date: 2022-09-05 16:50:04
 * @LastEditors: Radon
 * @LastEditTime: 2022-09-05 17:14:11
 * @Description: Hi, say something
 */
#include "priority_queue.h"

int main(int argc, char **argv) {
  s32 arr[5] = {5, 4, 3, 2, 1};

  /* 目前是数小的元素在队首 (堆顶) */

  priority_queue *pq = (priority_queue *)malloc(sizeof(priority_queue));
  init_pqueue(pq);

  for (s32 i = 0; i < 5; i++) {
    push_to_pqueue(pq, arr[i]);
  }

  for (s32 i = 0; i < 5; i++) {
    pop_from_pqueue(pq);
  }

  return 0;
}
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct item {
    int data;
    struct item* next;
    struct item* prev;
} item;

void check_mem_alloc(void* data);

void create_random_ordered_queue(item** begin, item** end, int num_elements);

void push_front(item** queue_beginning, item** queue_ending, int data);
void push_back(item** begin, item** end, int data);
void insert(item** begin, item** end, item* prev, int data);

void pop_back(item** queue_beginning, item** queue_ending);
void clear(item* beginning);

void merge_sorted_queues_to_list(item** beginning1, item** ending1, item** beginning2, item** ending2, item** list_beginning, item** list_ending);

void print_list(item* begin);
void print_queue(item* end);

#endif // MAIN_H

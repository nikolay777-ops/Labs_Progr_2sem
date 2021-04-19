//задача 5.1 (вариант x3 - 8)
//Даны две упорядоченные очереди. Разработать функцию, которая
//объединяет их в один упорядоченный двунаправленный список.

#include "main.h"

void check_mem_alloc(void* data) {
    if (!data) {
        fprintf(stderr, "failed to allocate memory!\n");
        exit(EXIT_FAILURE);
    }
}

void push_front(item** queue_beginning, item** queue_ending, int data) {
    if (!(*queue_beginning)) {
        *queue_beginning = (item*)malloc(sizeof (item));
        check_mem_alloc(*queue_beginning);

        (*queue_beginning)->data = data;
        (*queue_beginning)->next = (*queue_beginning)->prev = NULL;
        *queue_ending = *queue_beginning;

        return;
    }

    // нужно вставить элемент в начало.
    item* new_item = (item*)malloc(sizeof (item));
    check_mem_alloc(new_item);

    new_item->data = data;
    new_item->prev = NULL;
    new_item->next = *queue_beginning;
    (*queue_beginning)->prev = new_item;
    (*queue_beginning) = new_item;
}

void clear(item* beginning) {
    if (!beginning) { return; }

    item* next = beginning->next;
    for (item* i = beginning; i; i = next) {
        next = i->next;
        free(i);
    }
}

void pop_back(item** queue_beginning, item** queue_ending) {
    // удалить элемент из конца
    if (!(*queue_ending)) {
        // очередь пустая
        return;
    }
    if (*queue_ending == *queue_beginning) {
        free(*queue_ending);
        *queue_beginning = *queue_ending = NULL;
        return;
    }

    item* new_ending = (*queue_ending)->prev;
    new_ending->next = NULL;
    free(*queue_ending);
    *queue_ending = new_ending;
}

// добавление элемента в конец двунаправленного списка
void push_back(item** begin, item** end, int data) {
    if (*begin == NULL && *end == NULL) {
        *end = (item*)malloc(sizeof (item));
        check_mem_alloc(*end);

        (*end)->data = data;
        (*end)->next = (*end)->prev = NULL;
        *begin = *end;
        return;
    }

    // список не пустой
    item* new_item = (item*)malloc(sizeof (item));
    check_mem_alloc(new_item);
    new_item->data = data;
    new_item->next = NULL;
    new_item->prev = *end;
    (*end)->next = new_item;
    (*end) = new_item;
}

void insert(item** begin, item** end, item* prev, int data) {
    // вставляем в начало списка
    if (prev == NULL) {
        push_front(begin, end, data);
        return;
    }
    // вставляем в конец списка
    if (prev == *end) {
        push_back(begin, end, data);
        return;
    }

    // вставляем в середину списка
    item* new_item = (item*)malloc(sizeof (item));
    new_item->data = data;
    new_item->next = prev->next;
    new_item->prev = prev;
    item* old_next = prev->next;
    old_next->prev = new_item;
    prev->next = new_item;
}

void merge_sorted_queues_to_list(item** beginning1, item** ending1, item** beginning2, item** ending2, item** list_beginning, item** list_ending) {
    *list_beginning = *list_ending = NULL;

    // нужно извлекать элементы из обеих очередей и записывать их в список
    // сначала извлечём элементы из одной очереди. и потом извлекаем из другой, записывая
    // их в нужные места в списке
    while (*beginning1) {
        int data = (*ending1)->data;
        pop_back(beginning1, ending1);
        push_back(list_beginning, list_ending, data);
    }

    // на данный момент у нас есть список, в которую полностью записана первая очередь
    while (*beginning2) {
        int data = (*ending2)->data;
        pop_back(beginning2, ending2);

        for (item* i = *list_beginning; i; i = i->next) {
            if (!i->prev) { continue; }

            if (data >= i->prev->data && data <= i->data) {
                insert(list_beginning, list_ending, i->prev, data);
            }
        }
    }
}

void print_list(item* begin) {
    for (item* i = begin; i; i = i->next) {
        printf("%d ", i->data);
    }
    puts("");
}

void print_queue(item* end) {
    for (item* i = end; i; i = i->prev) {
        printf("%d ", i->data);
    }
    puts("");
}

void create_random_ordered_queue(item** begin, item** end, int num_elements) {
    int elem = 1;
    for (int i = 0; i++ < num_elements;) {
        push_front(begin, end, elem);
        elem += rand() % 30;
    }
}

int main() {
    srand(time(NULL));

    item* queue_begin1 = NULL, * queue_begin2 = NULL;
    item* queue_end1 = NULL, * queue_end2 = NULL;
    item* list_begin = NULL, * list_end = NULL;

    create_random_ordered_queue(&queue_begin1, &queue_end1, 40);
    create_random_ordered_queue(&queue_begin2, &queue_end2, 30);

    print_queue(queue_end1);
    print_queue(queue_end2);

    merge_sorted_queues_to_list(&queue_begin1, &queue_end1, &queue_begin2, &queue_end2, &list_begin, &list_end);

    print_list(list_begin);

    clear(list_begin);
    clear(queue_begin1);
    clear(queue_begin2);

    return 0;
}

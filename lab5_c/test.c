#include <assert.h>

#include "main.h"

void test_create_random_ordered_queue() {
    item* begin = NULL, * end = NULL;
    create_random_ordered_queue(&begin, &end, 40);

    item* i;
    for (i = begin; i; i = i->next) {
        if (i->prev) {
            assert(i->prev->data >= i->data);
        }
    }

    clear(begin);
}

void test_push_front() {
    item* b = NULL, * e = NULL;
    push_front(&b, &e, 2);
    assert(b->data == 2);
    push_front(&b, &e, 5);
    assert(b->data == 5);
    assert(b->next->data == 2);

    clear(b);
}

void test_push_back() {
    item* b = NULL, * e = NULL;
    push_back(&b, &e, 2);
    assert(b->data == 2);
    push_back(&b, &e, 5);
    assert(b->data == 2);
    assert(b->next->data == 5);

    clear(b);
}

void test_insert() {
    item* b = NULL, * e = NULL;
    push_back(&b, &e, 2);
    push_back(&b, &e, 6);
    insert(&b, &e, b, 5);
    assert(b->data == 2);
    assert(b->next->data == 5);
    assert(b->next->next->data == 6);

    clear(b);
}

void test_pop_back() {
    item* b = NULL, * e = NULL;
    push_back(&b, &e, 2);
    push_back(&b, &e, 6);
    pop_back(&b, &e);
    assert(b->next == NULL);
    assert(b->data == 2);

    clear(b);
}

void test_merge_sorted_queues_to_list() {
    item* bq1 = NULL, * eq1 = NULL;
    item* bq2 = NULL, * eq2 = NULL;
    item* bl = NULL, * el = NULL;

    push_front(&bq1, &eq1, 5);
    push_front(&bq1, &eq1, 10);
    push_front(&bq1, &eq1, 100);

    push_front(&bq2, &eq2, 6);
    push_front(&bq2, &eq2, 8);
    push_front(&bq2, &eq2, 50);
    push_front(&bq2, &eq2, 70);
    push_front(&bq2, &eq2, 80);

    merge_sorted_queues_to_list(&bq1, &eq1, &bq2, &eq2, &bl, &el);

    assert(bl->data == 5);
    assert(el->data == 100);
    assert(bl->next->next->data == 8);
    assert(el->prev->prev->data == 70);

    clear(bq1);
    clear(bq2);
    clear(bl);
}

#undef main
int main() {
    test_create_random_ordered_queue();
    test_push_front();
    test_push_back();
    test_insert();
    test_pop_back();
    test_merge_sorted_queues_to_list();
    puts("all tests passed");
    return 0;
}

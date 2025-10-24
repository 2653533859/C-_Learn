#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * 链表示例
 * - 包含单链表 (SList) 与双链表 (DList) 的实现
 * - 提供插入、删除、反转等操作，并附带自检测试
 */

typedef struct SListNode {
    int value;
    struct SListNode *next;
} SListNode;

typedef struct {
    SListNode *head;
} SList;

static SListNode *slist_create_node(int value) {
    SListNode *node = (SListNode *)malloc(sizeof(SListNode));
    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = NULL;
    return node;
}

static void slist_push_front(SList *list, int value) {
    SListNode *node = slist_create_node(value);
    node->next = list->head;
    list->head = node;
}

static void slist_push_back(SList *list, int value) {
    SListNode *node = slist_create_node(value);
    if (!list->head) {
        list->head = node;
        return;
    }
    SListNode *cur = list->head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = node;
}

static int slist_remove_first(SList *list, int value) {
    SListNode **cur = &list->head;
    while (*cur) {
        if ((*cur)->value == value) {
            SListNode *tmp = *cur;
            *cur = tmp->next;
            free(tmp);
            return 1;
        }
        cur = &((*cur)->next);
    }
    return 0;
}

static void slist_reverse(SList *list) {
    SListNode *prev = NULL;
    SListNode *cur = list->head;
    while (cur) {
        SListNode *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    list->head = prev;
}

static void slist_clear(SList *list) {
    SListNode *cur = list->head;
    while (cur) {
        SListNode *next = cur->next;
        free(cur);
        cur = next;
    }
    list->head = NULL;
}

static size_t slist_length(const SList *list) {
    size_t len = 0;
    for (SListNode *cur = list->head; cur; cur = cur->next) {
        ++len;
    }
    return len;
}

typedef struct DListNode {
    int value;
    struct DListNode *prev;
    struct DListNode *next;
} DListNode;

typedef struct {
    DListNode *head;
    DListNode *tail;
} DList;

static DListNode *dlist_create_node(int value) {
    DListNode *node = (DListNode *)malloc(sizeof(DListNode));
    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->prev = node->next = NULL;
    return node;
}

static void dlist_push_back(DList *list, int value) {
    DListNode *node = dlist_create_node(value);
    if (!list->tail) {
        list->head = list->tail = node;
        return;
    }
    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
}

static void dlist_push_front(DList *list, int value) {
    DListNode *node = dlist_create_node(value);
    if (!list->head) {
        list->head = list->tail = node;
        return;
    }
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
}

static int dlist_pop_back(DList *list, int *out_value) {
    if (!list->tail) {
        return 0;
    }
    DListNode *node = list->tail;
    if (out_value) {
        *out_value = node->value;
    }
    list->tail = node->prev;
    if (list->tail) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    free(node);
    return 1;
}

static DListNode *dlist_find(const DList *list, int value) {
    for (DListNode *cur = list->head; cur; cur = cur->next) {
        if (cur->value == value) {
            return cur;
        }
    }
    return NULL;
}

static void dlist_remove_node(DList *list, DListNode *node) {
    if (!node) {
        return;
    }
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }
    free(node);
}

static void dlist_clear(DList *list) {
    DListNode *cur = list->head;
    while (cur) {
        DListNode *next = cur->next;
        free(cur);
        cur = next;
    }
    list->head = list->tail = NULL;
}

static void test_slist(void) {
    SList list = {0};
    for (int i = 1; i <= 3; ++i) {
        slist_push_back(&list, i * 10);
    }
    assert(slist_length(&list) == 3);

    slist_push_front(&list, 5);
    assert(list.head->value == 5);

    /* 删除中间节点 */
    int removed = slist_remove_first(&list, 20);
    assert(removed == 1);
    assert(slist_length(&list) == 3);

    slist_reverse(&list);
    int expected[] = {30, 10, 5};
    SListNode *cur = list.head;
    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i) {
        assert(cur);
        assert(cur->value == expected[i]);
        cur = cur->next;
    }
    assert(cur == NULL);

    slist_clear(&list);
    assert(list.head == NULL);
}

static void test_dlist(void) {
    DList list = {0};
    dlist_push_back(&list, 1);
    dlist_push_back(&list, 2);
    dlist_push_back(&list, 3);
    dlist_push_front(&list, 0);

    /* 检查前后指针 */
    assert(list.head->value == 0);
    assert(list.head->next->prev == list.head);
    assert(list.tail->value == 3);
    assert(list.tail->prev->value == 2);

    DListNode *node2 = dlist_find(&list, 2);
    dlist_remove_node(&list, node2);
    assert(dlist_find(&list, 2) == NULL);

    int last;
    int ok = dlist_pop_back(&list, &last);
    assert(ok && last == 3);
    ok = dlist_pop_back(&list, &last);
    assert(ok && last == 1);
    ok = dlist_pop_back(&list, &last);
    assert(ok && last == 0);
    ok = dlist_pop_back(&list, &last);
    assert(ok == 0);

    dlist_clear(&list);
    assert(list.head == NULL && list.tail == NULL);
}

int main(void) {
    puts("[linked_list] Running tests...");
    test_slist();
    test_dlist();
    puts("[linked_list] All tests passed!\n");
    return 0;
}

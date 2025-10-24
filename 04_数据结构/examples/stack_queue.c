#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * 栈与队列示例
 * - 使用顺序存储实现整型栈与循环队列
 * - 使用链式存储实现队列，展示动态扩展能力
 */

#define STACK_CAPACITY 16
#define QUEUE_CAPACITY 16

typedef struct {
    int data[STACK_CAPACITY];
    int top; /* 指向下一个可写入位置 */
} ArrayStack;

static void stack_init(ArrayStack *stack) {
    stack->top = 0;
}

static int stack_is_empty(const ArrayStack *stack) {
    return stack->top == 0;
}

static void stack_push(ArrayStack *stack, int value) {
    if (stack->top >= STACK_CAPACITY) {
        fprintf(stderr, "stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->data[stack->top++] = value;
}

static int stack_pop(ArrayStack *stack) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[--stack->top];
}

static int stack_peek(const ArrayStack *stack) {
    if (stack_is_empty(stack)) {
        fprintf(stderr, "stack empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top - 1];
}

typedef struct {
    int data[QUEUE_CAPACITY];
    int front;
    int rear;
    int size;
} CircularQueue;

static void cq_init(CircularQueue *queue) {
    queue->front = queue->rear = queue->size = 0;
}

static int cq_is_empty(const CircularQueue *queue) {
    return queue->size == 0;
}

static int cq_is_full(const CircularQueue *queue) {
    return queue->size == QUEUE_CAPACITY;
}

static void cq_enqueue(CircularQueue *queue, int value) {
    if (cq_is_full(queue)) {
        fprintf(stderr, "queue overflow\n");
        exit(EXIT_FAILURE);
    }
    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % QUEUE_CAPACITY;
    queue->size++;
}

static int cq_dequeue(CircularQueue *queue) {
    if (cq_is_empty(queue)) {
        fprintf(stderr, "queue underflow\n");
        exit(EXIT_FAILURE);
    }
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % QUEUE_CAPACITY;
    queue->size--;
    return value;
}

typedef struct LQNode {
    int value;
    struct LQNode *next;
} LQNode;

typedef struct {
    LQNode *front;
    LQNode *rear;
    size_t length;
} LinkedQueue;

static void linked_queue_init(LinkedQueue *queue) {
    queue->front = queue->rear = NULL;
    queue->length = 0;
}

static int linked_queue_is_empty(const LinkedQueue *queue) {
    return queue->front == NULL;
}

static void linked_queue_enqueue(LinkedQueue *queue, int value) {
    LQNode *node = (LQNode *)malloc(sizeof(LQNode));
    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = NULL;
    if (queue->rear) {
        queue->rear->next = node;
    } else {
        queue->front = node;
    }
    queue->rear = node;
    queue->length++;
}

static int linked_queue_dequeue(LinkedQueue *queue) {
    if (linked_queue_is_empty(queue)) {
        fprintf(stderr, "linked queue underflow\n");
        exit(EXIT_FAILURE);
    }
    LQNode *node = queue->front;
    int value = node->value;
    queue->front = node->next;
    if (!queue->front) {
        queue->rear = NULL;
    }
    free(node);
    queue->length--;
    return value;
}

static void linked_queue_clear(LinkedQueue *queue) {
    while (!linked_queue_is_empty(queue)) {
        (void)linked_queue_dequeue(queue);
    }
}

static void test_stack(void) {
    ArrayStack stack;
    stack_init(&stack);
    assert(stack_is_empty(&stack));

    for (int i = 0; i < 5; ++i) {
        stack_push(&stack, i);
        assert(stack_peek(&stack) == i);
    }
    assert(!stack_is_empty(&stack));

    for (int i = 4; i >= 0; --i) {
        int value = stack_pop(&stack);
        assert(value == i);
    }
    assert(stack_is_empty(&stack));
}

static void test_circular_queue(void) {
    CircularQueue queue;
    cq_init(&queue);
    assert(cq_is_empty(&queue));

    for (int i = 1; i <= 6; ++i) {
        cq_enqueue(&queue, i * 10);
    }
    assert(!cq_is_empty(&queue));

    /* 执行出队，再入队，验证循环覆盖 */
    for (int i = 1; i <= 3; ++i) {
        int value = cq_dequeue(&queue);
        assert(value == i * 10);
        cq_enqueue(&queue, value + 100);
    }

    int expected[] = {40, 50, 60, 110, 120, 130};
    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i) {
        int value = cq_dequeue(&queue);
        assert(value == expected[i]);
    }
    assert(cq_is_empty(&queue));
}

static void test_linked_queue(void) {
    LinkedQueue queue;
    linked_queue_init(&queue);
    assert(linked_queue_is_empty(&queue));

    for (int i = 0; i < 4; ++i) {
        linked_queue_enqueue(&queue, i + 1);
    }
    assert(queue.length == 4);

    int value = linked_queue_dequeue(&queue);
    assert(value == 1);
    linked_queue_enqueue(&queue, 99);
    assert(queue.length == 4);

    int expected[] = {2, 3, 4, 99};
    for (size_t i = 0; i < sizeof(expected) / sizeof(expected[0]); ++i) {
        value = linked_queue_dequeue(&queue);
        assert(value == expected[i]);
    }
    assert(linked_queue_is_empty(&queue));

    linked_queue_clear(&queue);
}

int main(void) {
    puts("[stack_queue] Running tests...");
    test_stack();
    test_circular_queue();
    test_linked_queue();
    puts("[stack_queue] All tests passed!\n");
    return 0;
}

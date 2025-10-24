#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * 二叉树示例
 * - 基于二叉搜索树 (BST) 的插入、查找、遍历
 * - 包含高度计算、节点统计与旋转打印
 */

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static TreeNode *bst_new_node(int value) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

static TreeNode *bst_insert(TreeNode *root, int value) {
    if (!root) {
        return bst_new_node(value);
    }
    if (value < root->value) {
        root->left = bst_insert(root->left, value);
    } else if (value > root->value) {
        root->right = bst_insert(root->right, value);
    }
    return root;
}

static bool bst_contains(const TreeNode *root, int value) {
    if (!root) {
        return false;
    }
    if (value == root->value) {
        return true;
    }
    if (value < root->value) {
        return bst_contains(root->left, value);
    }
    return bst_contains(root->right, value);
}

static size_t bst_height(const TreeNode *root) {
    if (!root) {
        return 0;
    }
    size_t left = bst_height(root->left);
    size_t right = bst_height(root->right);
    return (left > right ? left : right) + 1;
}

static size_t bst_count_nodes(const TreeNode *root) {
    if (!root) {
        return 0;
    }
    return 1 + bst_count_nodes(root->left) + bst_count_nodes(root->right);
}

typedef struct {
    int *data;
    size_t capacity;
    size_t length;
} IntBuffer;

static void buffer_append(IntBuffer *buf, int value) {
    assert(buf->length < buf->capacity);
    buf->data[buf->length++] = value;
}

static void bst_inorder(const TreeNode *root, IntBuffer *buf) {
    if (!root) {
        return;
    }
    bst_inorder(root->left, buf);
    buffer_append(buf, root->value);
    bst_inorder(root->right, buf);
}

static void bst_preorder(const TreeNode *root, IntBuffer *buf) {
    if (!root) {
        return;
    }
    buffer_append(buf, root->value);
    bst_preorder(root->left, buf);
    bst_preorder(root->right, buf);
}

static void bst_postorder(const TreeNode *root, IntBuffer *buf) {
    if (!root) {
        return;
    }
    bst_postorder(root->left, buf);
    bst_postorder(root->right, buf);
    buffer_append(buf, root->value);
}

static void bst_free(TreeNode *root) {
    if (!root) {
        return;
    }
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

static void bst_print_rotated(const TreeNode *root, int depth) {
    if (!root) {
        return;
    }
    bst_print_rotated(root->right, depth + 1);
    for (int i = 0; i < depth; ++i) {
        printf("    ");
    }
    printf("[%d]\n", root->value);
    bst_print_rotated(root->left, depth + 1);
}

static TreeNode *build_sample_tree(void) {
    int values[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    TreeNode *root = NULL;
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        root = bst_insert(root, values[i]);
    }
    return root;
}

static void test_bst_basic(void) {
    TreeNode *root = build_sample_tree();
    assert(bst_contains(root, 6));
    assert(bst_contains(root, 13));
    assert(!bst_contains(root, 2));

    size_t height = bst_height(root);
    assert(height == 4);

    size_t count = bst_count_nodes(root);
    assert(count == 9);

    bst_free(root);
}

static void test_bst_traversals(void) {
    TreeNode *root = build_sample_tree();

    int inorder_buf[9];
    IntBuffer inorder = {inorder_buf, 9, 0};
    bst_inorder(root, &inorder);
    int inorder_expected[] = {1, 3, 4, 6, 7, 8, 10, 13, 14};
    for (size_t i = 0; i < inorder.length; ++i) {
        assert(inorder.data[i] == inorder_expected[i]);
    }

    int preorder_buf[9];
    IntBuffer preorder = {preorder_buf, 9, 0};
    bst_preorder(root, &preorder);
    int preorder_expected[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    for (size_t i = 0; i < preorder.length; ++i) {
        assert(preorder.data[i] == preorder_expected[i]);
    }

    int postorder_buf[9];
    IntBuffer postorder = {postorder_buf, 9, 0};
    bst_postorder(root, &postorder);
    int postorder_expected[] = {1, 4, 7, 6, 3, 13, 14, 10, 8};
    for (size_t i = 0; i < postorder.length; ++i) {
        assert(postorder.data[i] == postorder_expected[i]);
    }

    puts("[binary_tree] Rotated ASCII print:");
    bst_print_rotated(root, 0);

    bst_free(root);
}

int main(void) {
    puts("[binary_tree] Running tests...");
    test_bst_basic();
    test_bst_traversals();
    puts("[binary_tree] All tests passed!\n");
    return 0;
}

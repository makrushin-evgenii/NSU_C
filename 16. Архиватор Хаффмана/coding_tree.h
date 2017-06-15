// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
#include <stdint.h>
#include <stdbool.h>

typedef struct node_t {
	size_t priority;
	uint8_t value;
	size_t pos;
	bool is_leaf;

	struct node_t * left;
	struct node_t * right;
} node_t;

// Новый внутренний узел дерева.
node_t * tree_new_internal(node_t * left, node_t * right);

// Новый лист дерева
node_t * tree_new_leaf(size_t priority, uint8_t value);

// Освобождает из памяти дерево tree.
void tree_free(node_t * tree);

// Строит дерево по частотам символов.
// chars_freq - массив с частотами всех ASCII символов.
// Возвращает: дерево Хаффмана.
node_t * tree_build_with_freqs(size_t chars_freq[]);

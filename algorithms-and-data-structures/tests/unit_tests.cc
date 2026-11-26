// Unit tests for the sorting routines, the AVL tree and the red-black tree.
// Each program's source is included with its main() renamed, so the tests call
// the same functions the benchmarks time.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <set>
#include <vector>

static int failures = 0;
#define CHECK(cond, ...)                                                    \
  do {                                                                      \
    if (!(cond)) {                                                          \
      ++failures;                                                           \
      std::fprintf(stderr, "FAIL %s:%d: %s -- ", __FILE__, __LINE__, #cond); \
      std::fprintf(stderr, __VA_ARGS__);                                    \
      std::fprintf(stderr, "\n");                                           \
    }                                                                       \
  } while (0)

#define main heap_main
#include "../Heap/main.cc"
#undef main
#define main quick_main
#include "../Quick/main_.cc"
#undef main
#define main insert_main
#include "../Insert/main.cc"
#undef main
#define main select_main
#include "../Select/main.cc"
#undef main
#define main merge_main
#include "../Merge/main_.cc"
#undef main
#define main bubble_main
#include "../Burbuja/main_.cc"
#undef main
#define main avl_main
#include "../AVL/main.cc"
#undef main
#define main rb_main
#include "../RedBlack/main.cc"
#undef main

// Inputs: empty, single, sorted, reversed, all-equal, and random with many
// duplicates (the benchmarks use rand() % 100).
static std::vector<std::vector<int>> inputs() {
  std::vector<std::vector<int>> v = {{}, {7}, {2, 1}, {5, 5}, {1, 2, 3, 4, 5},
                                     {5, 4, 3, 2, 1}, {3, 3, 3, 3, 3, 3}};
  std::srand(12345);
  for (int n : {10, 57, 100, 1000}) {
    std::vector<int> r(n);
    for (int &x : r) x = std::rand() % 100;
    v.push_back(r);
  }
  return v;
}

static void check_sort(const char *name, std::function<void(int *, int)> sort) {
  for (auto in : inputs()) {
    std::vector<int> expected = in;
    std::sort(expected.begin(), expected.end());
    // exact-size heap buffer: under -fsanitize=address any read or write past
    // the end aborts the test
    int *raw = new int[in.size() ? in.size() : 1];
    std::copy(in.begin(), in.end(), raw);
    sort(raw, (int)in.size());
    std::vector<int> buf(raw, raw + in.size());
    delete[] raw;
    CHECK(buf == expected, "%s did not sort an input of n=%zu", name, in.size());
  }
}

static void test_sorts() {
  check_sort("heap", [](int *a, int n) { heap(a, n); });
  check_sort("quicksort", [](int *a, int n) { if (n) quicksort(a, n, 0, n - 1, 0); });
  check_sort("insert", [](int *a, int n) { insert(a, n); });
  check_sort("select", [](int *a, int n) { select(a, n); });
  check_sort("bubble", [](int *a, int n) { for (int i = 0; i < n; i++) F1(a, n, 1); });
}

// Merge/main_.cc's F merges two adjacent sorted runs A[i..j-1] and A[j..k].
static void test_merge_step() {
  std::srand(99);
  for (int trial = 0; trial < 200; trial++) {
    int left = std::rand() % 20 + 1, right = std::rand() % 20 + 1;
    std::vector<int> a(left + right), aux(left + right);
    for (int &x : a) x = std::rand() % 30;
    std::sort(a.begin(), a.begin() + left);
    std::sort(a.begin() + left, a.end());
    std::vector<int> expected = a;
    std::sort(expected.begin(), expected.end());
    F(a.data(), aux.data(), 0, left, left + right - 1);
    CHECK(a == expected, "merge of runs %d+%d is not sorted", left, right);
  }
}

// AVL: after every insert/remove the tree is a BST, balanced, with correct
// heights, and holds exactly the inserted multiset.
template <class T>
static int avl_check(nodoAVL<T> *n, long lo, long hi, std::multiset<int> &seen, bool &ok) {
  if (!n) return 0;
  if (n->dato < lo || n->dato > hi) ok = false;
  seen.insert(n->dato);
  int l = avl_check(n->nodo[0], lo, (long)n->dato, seen, ok);
  int r = avl_check(n->nodo[1], (long)n->dato, hi, seen, ok);
  if (std::abs(l - r) > 1) ok = false;
  if (n->altura != std::max(l, r) + 1) ok = false;
  return std::max(l, r) + 1;
}

static void test_avl() {
  AVL<int> t;
  std::multiset<int> model;
  std::srand(7);
  for (int step = 0; step < 2000; step++) {
    int x = std::rand() % 200;
    if (std::rand() % 3 && !model.empty()) {
      auto it = model.find(x);
      t.remove(x);
      if (it != model.end()) model.erase(it);
    } else {
      t.insert(x);
      model.insert(x);
    }
    std::multiset<int> seen;
    bool ok = true;
    avl_check(t.m_head, -1, 1000, seen, ok);
    CHECK(ok, "AVL invariant broken at step %d", step);
    CHECK(seen == model, "AVL contents differ from the model at step %d", step);
    if (!ok || seen != model) return;
  }
}

// Red-black tree: the library leaves the BST insert to the caller.
struct KeyNode : rbtree::RBNode {
  int key;
  KeyNode(rbtree::RBNode *nil, int k) : rbtree::RBNode(nil), key(k) {}
};
static void no_update(rbtree::RBNode *, rbtree::RBTree *) {}

static void rb_insert(rbtree::RBTree &t, int key) {
  rbtree::RBNode *y = t.nil, *x = t.root;
  KeyNode *z = new KeyNode(t.nil, key);
  while (x != t.nil) {
    y = x;
    x = key < static_cast<KeyNode *>(x)->key ? x->left : x->right;
  }
  z->parent = y;
  if (y == t.nil) t.root = z;
  else if (key < static_cast<KeyNode *>(y)->key) y->left = z;
  else y->right = z;
  t.rbInsertFixup(z, no_update);
}

// returns black height, or -1 if a red-black or BST rule is broken
static int rb_check(rbtree::RBTree &t, rbtree::RBNode *n, long lo, long hi) {
  if (n == t.nil) return 1;
  int k = static_cast<KeyNode *>(n)->key;
  if (k < lo || k > hi) return -1;
  if (n->left != t.nil && n->left->parent != n) return -1;
  if (n->right != t.nil && n->right->parent != n) return -1;
  if (n->color == rbtree::RED &&
      (n->left->color == rbtree::RED || n->right->color == rbtree::RED))
    return -1;
  int l = rb_check(t, n->left, lo, k), r = rb_check(t, n->right, k, hi);
  if (l < 0 || r < 0 || l != r) return -1;
  return l + (n->color == rbtree::BLACK);
}

static void test_rbtree() {
  rbtree::RBTree t;
  std::multiset<int> model;
  std::srand(3);
  for (int i = 0; i < 500; i++) {
    int k = std::rand() % 1000;
    rb_insert(t, k);
    model.insert(k);
    CHECK(t.root->color == rbtree::BLACK, "root is red after insert %d", i);
    CHECK(rb_check(t, t.root, -1, 100000) > 0, "invalid tree after insert %d", i);
  }
  std::vector<int> inorder;
  for (rbtree::RBNode *n = t.treeMinimum(t.root); n != t.nil; n = t.treeSuccessor(n))
    inorder.push_back(static_cast<KeyNode *>(n)->key);
  CHECK(inorder == std::vector<int>(model.begin(), model.end()), "in-order walk is not sorted");

  for (int i = 0; i < 300; i++) {
    rbtree::RBNode *n = t.root;
    for (int d = std::rand() % 6; d > 0 && n->left != t.nil; d--) n = n->left;
    model.erase(model.find(static_cast<KeyNode *>(n)->key));
    t.rbDelete(n, no_update);
    delete n;
    CHECK(rb_check(t, t.root, -1, 100000) > 0, "invalid tree after delete %d", i);
  }
  inorder.clear();
  for (rbtree::RBNode *n = t.treeMinimum(t.root); n != t.nil; n = t.treeSuccessor(n))
    inorder.push_back(static_cast<KeyNode *>(n)->key);
  CHECK(inorder == std::vector<int>(model.begin(), model.end()), "contents wrong after deletes");
}

int main() {
  test_sorts();
  test_merge_step();
  test_avl();
  test_rbtree();
  if (failures) {
    std::fprintf(stderr, "%d check(s) failed\n", failures);
    return 1;
  }
  std::printf("unit tests: all checks passed\n");
  return 0;
}

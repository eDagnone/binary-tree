#include "layout.h"
#include <stdlib.h>
#include <string.h>

//! Initialize a new layout structure
void layout_init(struct Layout *layout, struct LayoutNode *root) {
  layout->root = root;
  root->num_children = 0;
}

//! Initialize a new node in the layout struct. This does not add the node to the layout.
//@param position the position of the node relative to it's parent
void layout_node_init(struct LayoutNode *node, const char *name, int id, struct Position position) {
  node->name = name;
  node->id = id;
  node->position = position;
  node->num_children = 0;
}

//! Add a new node to the tree under the given parent.
void layout_add_child(struct Layout *layout, struct LayoutNode *parent, struct LayoutNode *child) {

  struct LayoutNode **temp;
  //! Avoid using realloc on uninitialized pointer
  if (parent->num_children == 0) {
    temp = malloc(sizeof(struct LayoutNode *));
  } else {
    temp = realloc(parent->children, (parent->num_children + 1) * sizeof(struct LayoutNode *));
  }
  parent->children = temp;
  parent->children[parent->num_children] = child;
  child->parent = parent;
  child->position.x += parent->position.x;
  child->position.y += parent->position.y;
  parent->num_children++;
}

//! Change position of target and child nodes using an offset from the parent.
void layout_node_update_position(struct Layout *layout, struct LayoutNode *node, struct Position position) {
  //! Deltas = new_position - old_position
  int delta_x = node->parent->position.x + position.x - node->position.x;
  int delta_y = node->parent->position.y + position.y - node->position.y;
  layout_node_shift_positions(node, delta_x, delta_y);
}
//! Recursively change position of nodes by an x and y offset
void layout_node_shift_positions(struct LayoutNode *node, int delta_x, int delta_y) {
  node->position.x += delta_x;
  node->position.y += delta_y;
  for (int i = 0; i < node->num_children; ++i) {
    layout_node_shift_positions(node->children[i], delta_x, delta_y);
  }
}

//! Find a node by name or id in the tree using standard dfs (tree is unsorted)
struct LayoutNode *depth_first_search(struct LayoutNode *root, const char *name, int id) {
  if ((name && strcmp(root->name, name) == 0) || (root->id == id))
    return root;
  for (int i = 0; i < root->num_children; ++i) {
    struct LayoutNode *result = depth_first_search(root->children[i], name, id);
    if (result != NULL) {
      return result;
    }
  }
  return NULL;
}

struct Position layout_get_position_for_node(struct Layout *layout, struct LayoutNode *node) {
  return node->position;
}

struct Position layout_get_position_for_name(struct Layout *layout, const char *name) {
  struct LayoutNode *node = depth_first_search(layout->root, name, -1);
  if (node != NULL) {
    return node->position;
  }
}

struct Position layout_get_position_for_id(struct Layout *layout, int id) {
  struct LayoutNode *node = depth_first_search(layout->root, "-1", id);
  if (node != NULL) {
    return node->position;
  }
}
// Recursively deletes a branch of the tree, starting at node
void delete_branch(struct LayoutNode *node) {
  for (int i = 0; i < node->num_children; ++i) {
    delete_branch(node->children[i]);
  }
  if (node->num_children > 0) {
    free(node->children);
  }
}

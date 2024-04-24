//! This header file describes a basic API for implementing a hierarchical layout system.
//! A series of nodes are laid out in a tree where each node has a position relative to it's
//! parent. A user should be able to add nodes to this tree and update their positions and
//! then later query the tree for the absolute positions of the various nodes. There are no
//! limits on how deep the tree can be or how many children a given node may have.
//!
//! When implementing this API, feel free to assume that the user isn't going to screw anything
//! up (nodes will only be added to the tree once and only after being initialized, every
//! node in the tree will have a unique name and id). You may also assume that once a node has
//! been added to the tree the name and id will not be modified.
//!
//! When considering various designs, please try to satisfy the following criteria in order
//! (from most important to least important)
//! 1) Readable and maintainable. What would you write in production
//! 2) Minimize memory utilization
//! 3) Minimize runtime.
//!
//! You may only use the standard C library.
//!
//! Thanks so much for partipating! Good luck!

struct Position {
  int x;
  int y;
};

struct LayoutNode {
  const char *name;
  int id;
  unsigned int num_children;
  struct LayoutNode *parent;
  struct LayoutNode **children; // Array of pointers
  struct Position position;
};

struct Layout {
  struct LayoutNode *root;
};

//! Initialize a new layout structure
void layout_init(struct Layout *layout, struct LayoutNode *root);
//! Initialize a new node in the layout struct. This does not add the node to the layout.
//! @param position the position of the node relative to it's parent
void layout_node_init(struct LayoutNode *node, const char *name, int id, struct Position position);

void layout_add_child(struct Layout *layout, struct LayoutNode *parent, struct LayoutNode *child);

void layout_node_update_position(struct Layout *layout, struct LayoutNode *node, struct Position position);
void layout_node_shift_positions(struct LayoutNode *node, int delta_x, int delta_y);
void delete_branch(struct LayoutNode *node);

struct Position layout_get_position_for_node(struct Layout *layout, struct LayoutNode *node);
struct Position layout_get_position_for_name(struct Layout *layout, const char *name);
struct Position layout_get_position_for_id(struct Layout *layout, int id);

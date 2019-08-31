// C++ program to insert a node in AVL tree 

// An AVL tree node 
class Node { 
	public: 
	int key;
	int size;
    Node *left; 
	Node *right; 
	int height; 
}; 

int height(Node*);
int size(Node*);
void updateHeight(Node* node) {
    if (node == NULL) {
        return;
    }
    node->height = std::max(height(node->left), 
                            height(node->right)) + 1;
}

void updateSize(Node* node) {
    if (node == NULL) {
        return;
    }
    node->size = size(node->left) + 
                 size(node->right); 
}

void update(Node* node) {
    if (node == NULL) {
        return;
    }
    updateHeight(node);
    updateSize(node);
}

// A utility function to get the 
// height of the tree 
int height(Node *N) { 
	if (N == NULL) { 
		return 0; 
    }
	return N->height; 
} 

int size(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->size + 1; 
}


/* Helper function that allocates a 
new node with the given key and 
NULL left and right pointers. */
Node* newNode(int key) { 
	Node* node = new Node(); 
	node->key = key; 
    node->size = 0; 
    node->left = NULL; 
	node->right = NULL; 
	node->height = 1; // new node is initially 
					// added at leaf 
	return node; 
} 

// A utility function to right 
// rotate subtree rooted with y 
// See the diagram given above. 
Node *rightRotate(Node *y) { 
	Node *x = y->left; 
	Node *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights
    update(y);
    update(x); 
	// Return new root 
	return x; 
} 

// A utility function to left 
// rotate subtree rooted with x 
// See the diagram given above. 
Node *leftRotate(Node *x) { 
	Node *y = x->right; 
	Node *T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 

	// Update heights 
    update(x);
    update(y);

	// Return new root 
	return y; 
} 

// Get Balance factor of node N 
int getBalance(Node *N) { 
	if (N == NULL) {
		return 0; 
    }
    return height(N->left) - height(N->right); 
} 

// Recursive function to insert a key 
// in the subtree rooted with node and 
// returns the new root of the subtree. 
Node* insert(Node* node, int key) { 
	/* 1. Perform the normal BST insertion */
	if (node == NULL) { 
		return(newNode(key)); 
    } else if (key < node->key) { 
		node->left = insert(node->left, key); 
    } else { 
		node->right = insert(node->right, key); 
    } 

	/* 2. Update height of this ancestor node */
    update(node);

	/* 3. Get the balance factor of this ancestor 
		node to check whether this node became 
		unbalanced */
	int balance = getBalance(node); 

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < node->left->key) { 
		return rightRotate(node); 
    }

	// Right Right Case 
	if (balance < -1 && key > node->right->key) { 
		return leftRotate(node); 
    }

	// Left Right Case 
	if (balance > 1 && key > node->left->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	// Right Left Case 
	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	/* return the (unchanged) node pointer */
	return node; 
}

int select(Node* node, size_t i) {
    // node CANNOT be NULL
    int left_sz = size( node->left );
    if ( left_sz == i ) {
        return node->key;
    } else if ( i < left_sz ) {
        return select( node->left, i );
    } else {
        return select( node->right, i - (left_sz + 1));
    }
}

void check_node(Node* node) {
    if (node == NULL) {
        std::cerr << "ERROR: Asking for statistical info of a NULL tree. Exiting..." 
            << std::endl;
        exit( 0 );
    }
}

int min(Node* node) {
    check_node( node );

    return select( node, 0 );
}

int max(Node* node) {
    check_node( node );

    return select( node, size( node ) - 1 );
}

double median(Node* node) {
    check_node( node );

    const size_t N = size( node );
    if (N%2 == 0) {
        return (double(select(node, N/2)) + double(select(node, N/2 - 1))) / 2.0;
    } else {
        return double(select(node, N/2));
    }
}

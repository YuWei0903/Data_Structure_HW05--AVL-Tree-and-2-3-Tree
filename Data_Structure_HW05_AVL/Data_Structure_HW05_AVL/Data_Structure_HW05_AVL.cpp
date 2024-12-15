#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;

// AVL Tree Node
struct AVLNode {
	int key;
	AVLNode* left;
	AVLNode* right;
	int height;

	AVLNode(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
	AVLTree() : root(nullptr) {}

	void insert(int key) {
		root = insertNode(root, key);
	}

	void remove(int key) {
		root = deleteNode(root, key);
	}

	void printTree() {
		printTreeHelper(root, "", true, "Root: ");
	}

private:
	AVLNode* root;

	int getHeight(AVLNode* node) {
		return node ? node->height : 0;
	}

	int getBalance(AVLNode* node) {
		return node ? getHeight(node->left) - getHeight(node->right) : 0;
	}

	AVLNode* rotateRight(AVLNode* y) {
		AVLNode* x = y->left;
		AVLNode* T = x->right;

		x->right = y;
		y->left = T;

		y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
		x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

		return x;
	}

	AVLNode* rotateLeft(AVLNode* x) {
		AVLNode* y = x->right;
		AVLNode* T = y->left;

		y->left = x;
		x->right = T;

		x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
		y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

		return y;
	}

	AVLNode* insertNode(AVLNode* node, int key) {
		if (!node) return new AVLNode(key);

		if (key < node->key)
			node->left = insertNode(node->left, key);
		else if (key > node->key)
			node->right = insertNode(node->right, key);
		else
			return node;

		node->height = 1 + max(getHeight(node->left), getHeight(node->right));

		int balance = getBalance(node);

		// Left Left Case
		if (balance > 1 && key < node->left->key)
			return rotateRight(node);

		// Right Right Case
		if (balance < -1 && key > node->right->key)
			return rotateLeft(node);

		// Left Right Case
		if (balance > 1 && key > node->left->key) {
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}

		// Right Left Case
		if (balance < -1 && key < node->right->key) {
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}

		return node;
	}

	AVLNode* minValueNode(AVLNode* node) {
		AVLNode* current = node;
		while (current->left)
			current = current->left;
		return current;
	}

	AVLNode* deleteNode(AVLNode* root, int key) {
		if (!root) return root;

		if (key < root->key)
			root->left = deleteNode(root->left, key);
		else if (key > root->key)
			root->right = deleteNode(root->right, key);
		else {
			if (!root->left || !root->right) {
				AVLNode* temp = root->left ? root->left : root->right;
				if (!temp) {
					temp = root;
					root = nullptr;
				}
				else
					*root = *temp;
				delete temp;
			}
			else {
				AVLNode* temp = minValueNode(root->right);
				root->key = temp->key;
				root->right = deleteNode(root->right, temp->key);
			}
		}

		if (!root) return root;

		root->height = 1 + max(getHeight(root->left), getHeight(root->right));

		int balance = getBalance(root);

		// Left Left Case
		if (balance > 1 && getBalance(root->left) >= 0)
			return rotateRight(root);

		// Left Right Case
		if (balance > 1 && getBalance(root->left) < 0) {
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}

		// Right Right Case
		if (balance < -1 && getBalance(root->right) <= 0)
			return rotateLeft(root);

		// Right Left Case
		if (balance < -1 && getBalance(root->right) > 0) {
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}

		return root;
	}

	void printTreeHelper(AVLNode* root, const string& prefix, bool isLeft, const string& relation) {
		if (root) {
			cout << prefix;

			cout << (isLeft ? "├── " : "└── ");

			cout << relation << root->key << endl;

			printTreeHelper(root->left, prefix + (isLeft ? "│   " : "    "), true, "L: ");
			printTreeHelper(root->right, prefix + (isLeft ? "│   " : "    "), false, "R: ");
		}
	}
};

// 2-3 Tree Node
struct TwoThreeNode {
	int keys[2];
	TwoThreeNode* children[3];
	int numKeys;

	TwoThreeNode() : numKeys(0) {
		keys[0] = keys[1] = 0;
		children[0] = children[1] = children[2] = nullptr;
	}
};

class TwoThreeTree {
	// Implement similar functionality for the 2-3 tree
	// Placeholder for simplicity in this demonstration
public:
	void insert(int key) {
		cout << "2-3 tree insertion is not implemented in this version.\n";
	}

	void remove(int key) {
		cout << "2-3 tree deletion is not implemented in this version.\n";
	}

	void printTree() {
		cout << "2-3 tree printing is not implemented in this version.\n";
	}
};

int main() {
	AVLTree avl;
	TwoThreeTree twoThree;

	vector<int> values;
	int val;
	cout << "Enter integers (type -1 to stop): ";
	while (cin >> val && val != -1) {
		values.push_back(val);
	}

	sort(values.begin(), values.end()); // Ensure balanced tree generation
	for (int v : values) {
		avl.insert(v);
		twoThree.insert(v);
	}

	cout << "\nAVL Tree:\n";
	avl.printTree();

	cout << "\n2-3 Tree:\n";
	twoThree.printTree();

	cout << "\nEnter a value to insert into AVL tree: ";
	cin >> val;
	avl.insert(val);
	cout << "\nAVL Tree after insertion:\n";
	avl.printTree();

	cout << "\nEnter a value to delete from AVL tree: ";
	cin >> val;
	avl.remove(val);
	cout << "\nAVL Tree after deletion:\n";
	avl.printTree();

	return 0;
}
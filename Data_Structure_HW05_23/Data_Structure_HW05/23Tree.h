#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// 2-3 Tree Node
struct TwoThreeNode {
    int keys[2];
    TwoThreeNode* children[3];
    TwoThreeNode* parent;
    int numKeys;

    TwoThreeNode() : parent(nullptr), numKeys(0) {
        keys[0] = keys[1] = 0;
        children[0] = children[1] = children[2] = nullptr;
    }
};

class TwoThreeTree {
public:
    TwoThreeTree() : root(nullptr) {}

    void insert(int key) {
        if (!root) {
            root = new TwoThreeNode();
            root->keys[0] = key;
            root->numKeys = 1;
        }
        else {
            TwoThreeNode* node = findLeaf(root, key);
            insertIntoNode(node, key);
        }
    }

    void remove(int key) {
        TwoThreeNode* node = findLeafWithKey(root, key);
        if (!node) {
            cout << "Key not found in the tree.\n";
            return;
        }
        removeFromNode(node, key);
        if (root->numKeys == 0 && root->children[0]) {
            // Update root if it's empty and has children
            TwoThreeNode* oldRoot = root;
            root = root->children[0];
            root->parent = nullptr;
            delete oldRoot;
        }
    }

    void printTree() {
        if (!root) {
            cout << "Tree is empty.\n";
            return;
        }
        printTreeHelper(root, "", true, "");
    }

private:
    TwoThreeNode* root;

    // Find the appropriate leaf node for insertion
    TwoThreeNode* findLeaf(TwoThreeNode* node, int key) {
        while (node->children[0]) {
            if (key < node->keys[0]) {
                node = node->children[0];
            }
            else if (node->numKeys == 1 || key < node->keys[1]) {
                node = node->children[1];
            }
            else {
                node = node->children[2];
            }
        }
        return node;
    }

    // Find the leaf node containing the key
    TwoThreeNode* findLeafWithKey(TwoThreeNode* node, int key) {
        while (node) {
            if (key == node->keys[0] || (node->numKeys > 1 && key == node->keys[1])) {
                return node;
            }
            if (key < node->keys[0]) {
                node = node->children[0];
            }
            else if (node->numKeys == 1 || key < node->keys[1]) {
                node = node->children[1];
            }
            else {
                node = node->children[2];
            }
        }
        return nullptr;
    }

    void removeFromNode(TwoThreeNode* node, int key) {
        // Remove the key from the node
        if (key == node->keys[0]) {
            node->keys[0] = node->keys[1];
        }
        node->keys[1] = 0;
        node->numKeys--;

        // If node underflows, fix the tree
        if (node->numKeys == 0) {
            fixUnderflow(node);
        }
    }

    void fixUnderflow(TwoThreeNode* node) {
        if (!node->parent) {
            return; // Root underflow is handled in remove()
        }

        TwoThreeNode* parent = node->parent;
        int childIndex = findChildIndex(parent, node);

        // Try borrowing from left sibling
        if (childIndex > 0 && parent->children[childIndex - 1]->numKeys > 1) {
            borrowFromLeftSibling(parent, childIndex);
        }
        // Try borrowing from right sibling
        else if (childIndex < parent->numKeys && parent->children[childIndex + 1]->numKeys > 1) {
            borrowFromRightSibling(parent, childIndex);
        }
        // Merge with a sibling
        else {
            mergeWithSibling(parent, childIndex);
        }
    }

    int findChildIndex(TwoThreeNode* parent, TwoThreeNode* child) {
        for (int i = 0; i <= parent->numKeys; ++i) {
            if (parent->children[i] == child) {
                return i;
            }
        }
        return -1;
    }

    void borrowFromLeftSibling(TwoThreeNode* parent, int childIndex) {
        TwoThreeNode* leftSibling = parent->children[childIndex - 1];
        TwoThreeNode* node = parent->children[childIndex];

        // Shift keys in node
        node->keys[1] = node->keys[0];
        node->keys[0] = parent->keys[childIndex - 1];
        parent->keys[childIndex - 1] = leftSibling->keys[leftSibling->numKeys - 1];

        leftSibling->keys[leftSibling->numKeys - 1] = 0;
        leftSibling->numKeys--;
        node->numKeys++;
    }

    void borrowFromRightSibling(TwoThreeNode* parent, int childIndex) {
        TwoThreeNode* rightSibling = parent->children[childIndex + 1];
        TwoThreeNode* node = parent->children[childIndex];

        // Shift keys in right sibling
        node->keys[node->numKeys] = parent->keys[childIndex];
        parent->keys[childIndex] = rightSibling->keys[0];

        rightSibling->keys[0] = rightSibling->keys[1];
        rightSibling->keys[1] = 0;
        rightSibling->numKeys--;
        node->numKeys++;
    }

    void mergeWithSibling(TwoThreeNode* parent, int childIndex) {
        TwoThreeNode* node = parent->children[childIndex];

        if (childIndex > 0) {
            TwoThreeNode* leftSibling = parent->children[childIndex - 1];
            leftSibling->keys[leftSibling->numKeys] = parent->keys[childIndex - 1];
            leftSibling->numKeys++;

            if (node->numKeys == 1) {
                leftSibling->keys[leftSibling->numKeys] = node->keys[0];
                leftSibling->numKeys++;
            }

            parent->keys[childIndex - 1] = parent->keys[childIndex];
            parent->children[childIndex] = nullptr;
        }
        else {
            TwoThreeNode* rightSibling = parent->children[childIndex + 1];
            node->keys[node->numKeys] = parent->keys[childIndex];
            node->numKeys++;

            if (rightSibling->numKeys == 1) {
                node->keys[node->numKeys] = rightSibling->keys[0];
                node->numKeys++;
            }

            parent->keys[childIndex] = parent->keys[childIndex + 1];
            parent->children[childIndex + 1] = nullptr;
        }

        parent->numKeys--;
    }

    void insertIntoNode(TwoThreeNode* node, int key) {
        // If the node has space, insert the key
        if (node->numKeys < 2) {
            if (key < node->keys[0]) {
                node->keys[1] = node->keys[0];
                node->keys[0] = key;
            }
            else {
                node->keys[1] = key;
            }
            node->numKeys++;
        }
        else {
            // Split the node if it's full
            splitNode(node, key);
        }
    }

    void splitNode(TwoThreeNode* node, int key) {
        vector<int> keys = { node->keys[0], node->keys[1], key };
        sort(keys.begin(), keys.end());

        TwoThreeNode* leftChild = new TwoThreeNode();
        leftChild->keys[0] = keys[0];
        leftChild->numKeys = 1;

        TwoThreeNode* rightChild = new TwoThreeNode();
        rightChild->keys[0] = keys[2];
        rightChild->numKeys = 1;

        if (!node->parent) {
            // Create a new root if splitting the original root
            root = new TwoThreeNode();
            root->keys[0] = keys[1];
            root->numKeys = 1;
            root->children[0] = leftChild;
            root->children[1] = rightChild;
            leftChild->parent = root;
            rightChild->parent = root;
        }
        else {
            // Insert the middle key into the parent
            TwoThreeNode* parent = node->parent;
            leftChild->parent = parent;
            rightChild->parent = parent;

            if (parent->children[0] == node) {
                parent->children[2] = parent->children[1];
                parent->children[1] = rightChild;
                parent->children[0] = leftChild;
            }
            else {
                parent->children[2] = rightChild;
                parent->children[1] = leftChild;
            }

            insertIntoNode(parent, keys[1]);
        }

        delete node;
    }

    void printTreeHelper(TwoThreeNode* node, const string& prefix, bool isLeft, const string& childLabel) {
        if (node) {
            cout << prefix;

            cout << (isLeft ? "¢u¢w¢w " : "¢|¢w¢w ") << childLabel;

            for (int i = 0; i < node->numKeys; ++i) {
                cout << node->keys[i] << (i < node->numKeys - 1 ? ", " : "");
            }
            cout << endl;

            if (node->children[0]) {
                printTreeHelper(node->children[0], prefix + (isLeft ? "¢x   " : "    "), true, "L: ");
                printTreeHelper(node->children[1], prefix + (isLeft ? "¢x   " : "    "), false, "R: ");
                if (node->numKeys == 2)
                    printTreeHelper(node->children[2], prefix + (isLeft ? "¢x   " : "    "), false, "R: ");
            }
        }
    }
};
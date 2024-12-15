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
        cout << "2-3 tree deletion is not fully implemented in this version.\n";
    }

    void printTree() {
        if (!root) {
            cout << "Tree is empty.\n";
            return;
        }
        printTreeHelper(root, "", true);
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

    void printTreeHelper(TwoThreeNode* node, const string& prefix, bool isLeft) {
        if (node) {
            cout << prefix;

            cout << (isLeft ? "¢u¢w¢w " : "¢|¢w¢w ");

            for (int i = 0; i < node->numKeys; ++i) {
                cout << node->keys[i] << (i < node->numKeys - 1 ? ", " : "");
            }
            cout << endl;

            if (node->children[0]) {
                printTreeHelper(node->children[0], prefix + (isLeft ? "¢x   " : "    "), true);
                printTreeHelper(node->children[1], prefix + (isLeft ? "¢x   " : "    "), false);
                if (node->numKeys == 2)
                    printTreeHelper(node->children[2], prefix + (isLeft ? "¢x   " : "    "), false);
            }
        }
    }
};

int main() {
    TwoThreeTree tree;

    vector<int> values;
    int val;
    cout << "Enter integers (type -1 to stop): ";
    while (cin >> val && val != -1) {
        values.push_back(val);
    }

    sort(values.begin(), values.end());
    for (int v : values) {
        tree.insert(v);
    }

    cout << "\n2-3 Tree:\n";
    tree.printTree();

    cout << "\nEnter a value to insert into the 2-3 tree: ";
    cin >> val;
    tree.insert(val);
    cout << "\n2-3 Tree after insertion:\n";
    tree.printTree();

    cout << "\nEnter a value to delete from the 2-3 tree: ";
    cin >> val;
    tree.remove(val);
    cout << "\n2-3 Tree after deletion (placeholder):\n";
    tree.printTree();

    return 0;
}

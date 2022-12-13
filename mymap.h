//
// mymap.
// Self-balancing threaded binary search tree : This class builds a self-balancing threaded binary search tree
// only the right pointers are threaded if needed, can be used with any primitive variable type
//
// Tyler Strach
// U. of Illinois, Chicago
// Fall 2022
//

#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE *left;  // links to left child
        NODE *right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE *root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    /**
     * returns the smallest priority in the given tree
     * @param cur the root of tree
     * @return
     */
    NODE *findSmallest(NODE *cur) {
        if (cur == nullptr) {
            return nullptr;
        }
        while (cur->left != nullptr)
            cur = cur->left;
        return cur;
    }

    /**
     * returns the node with the specified key
     * used to check if node exists in tree and needs to be updated with new value
     * @param key
     * @return
     */
    NODE *search(keyType key) {
        NODE *cur = root;

        while (cur != nullptr) { // until the end of tree, moves cur down the tree
            if (key == cur->key) // returns if found
                return cur;
            else if (key < cur->key) // moves down left tree
                cur = cur->left;
            else if (key > cur->key) // moves down right tree
                cur = (cur->isThreaded) ? nullptr : cur->right; // treats threaded as a nullptr
        }
        return cur; // returns nullptr if not found
    }

    /**
     * returns the parent of node with the specified key, while not updating counts
     * used to get violator parent
     * @param key
     * @return node with specified key
     */
    NODE *searchParent(keyType key) {
        NODE *cur = root;
        NODE *prev = nullptr;

        while (cur != nullptr) { // until the end of tree, moves cur down the tree
            if (key == cur->key) // returns if found
                return prev;
            else if (key < cur->key) { // moves down left tree
                prev = cur;
                cur = cur->left;
            } else if (key > cur->key) { // moves down right tree
                prev = cur;
                cur = (cur->isThreaded) ? nullptr : cur->right; // treats threaded as a nullptr
            }
        }
    }

    /**
     * returns the parent to the node with the specified key and updates nL and nR along the path
     * violator saves a pointer to the first violator of the seesaw property closest to the root of tree
     * @param key node to be searched for
     * @param violator points to the violator node if found
     * @return parent to the node with the specified key
     */
    NODE *searchParentUpdateCount(keyType key, NODE *&violator) {
        NODE *cur = root;
        NODE *parent = nullptr;
        bool foundViolator = false; // indicator to mark the first violator closest to the root

        while (cur != nullptr) { // until the end of tree, moves cur and prev down the tree
            if (key < cur->key) { // moves down left tree
                parent = cur;
                (parent->nL)++; // increments left node counter by 1
                cur = cur->left;
            } else if (key > cur->key) { // moves down right tree
                parent = cur;
                (parent->nR)++; // increments right node counter by 1
                cur = (cur->isThreaded) ? nullptr : cur->right; // treats threaded as a nullptr
            }

            if (!foundViolator) {
                violator = (max(parent->nL, parent->nR) <= 2 * min(parent->nL, parent->nR) + 1) ? nullptr : parent;
                if (violator != nullptr) // updates to indicate a violator was found
                    foundViolator = true;
            }
        }
        return parent; // if not found, returns nullptr
    }

    /**
     * recursive function that copies the tree starting from the source node
     * @param source
     */
    void _copy(NODE *source) {
        if (source == nullptr) // if tree is empty return
            return;
        else {
            put(source->key, source->value); // copies the node
            _copy(source->left); // moves to the left subtree
            source = (source->isThreaded) ? nullptr : source->right; // if threaded, treat right ptr as null
            _copy(source); // moves to the right subtree
        }
    }

    /**
     * recursive function that stores the inorder values of the current queue into ostream object, similar to _output
     * @param pairs vector holding the key/value pairs
     * @param cur head of tree to be worked on
     */
    void _tovector(vector<pair<keyType, valueType> > &pairs, NODE *cur) {
        if (cur == nullptr) // if emtpy returns
            return;
        else {
            _tovector(pairs, cur->left); // moves into left subtree
            pairs.push_back({cur->key, cur->value});
            cur = (cur->isThreaded) ? nullptr : cur->right; // if threaded, treat right ptr as null
            _tovector(pairs, cur); // moves into right subtree
        }
    }

    /**
     * stores the tree in-order into a string for testing
     * @param final ostream object
     * @param cur head of desired tree
     */
    void _output(ostream &final, NODE *cur) {
        if (cur == nullptr) // if emtpy returns
            return;
        else {
            _output(final, cur->left); // moves into left subtree
            final << "key: " << cur->key << " value: " << cur->value << "\n"; // stores values
            cur = (cur->isThreaded) ? nullptr : cur->right; // if threaded, treat right ptr as null
            _output(final, cur); // moves into right subtree
        }
    }

    /**
     * recursive function that stores the preorder values of the current queue into ostream object
     * @param final ostream object
     * @param cur root of desired tree
     */
    void _outputBalanced(ostream &final, NODE *cur) {
        if (cur == nullptr) // if emtpy returns
            return;
        else {
            final << "key: " << cur->key << ", nL: " << cur->nL << ", nR: " << cur->nR << "\n"; // stores values
            _outputBalanced(final, cur->left); // moves into left subtree
            cur = (cur->isThreaded) ? nullptr : cur->right; // if threaded, treat right ptr as null
            _outputBalanced(final, cur); // moves into right subtree
        }
    }

    /**
     * recursive postorder to delete the elements in the tree
     * @param cur head of tree
     */
    void _clear(NODE *cur) {
        if (cur == nullptr) // if empty tree, return
            return;
        else {
            _clear(cur->left); // moves into the left subtree
            if (!(cur->isThreaded)) { // moves into right subtree only if not threaded
                _clear(cur->right);
            }

            //deletes from the bottom up, and sets pointers to null
            cur->left = nullptr;
            cur->right = nullptr;
            delete cur;
            size--;
        }
    }

    /**
     * builds the violator vector in-order, to be used to re-balance and re-thread this portion of the tree
     * @param treeRebal vector holding the nodes
     * @param cur head of subtree to be rebalanced
     */
    void _buildViolatorVector(vector<NODE *> &treeRebal, NODE *cur) {
        if (cur == nullptr) // if emtpy returns
            return;
        else {
            _buildViolatorVector(treeRebal, cur->left); // moves into left subtree
            treeRebal.push_back(cur);
            cur = (cur->isThreaded) ? nullptr : cur->right; // if threaded, treat right ptr as null
            _buildViolatorVector(treeRebal, cur); // moves into right subtree
        }
    }

    /**
     * uses recursion to correctly build the new tree so it is properly balanced
     * calls subPut, which is the put function for the new subtree to be made with correct threading
     * @param nodes holds the children nodes of the violator in-order
     * @param newRoot a pointer to the new root of the tree to be updated and changed
     * @param low left most index of sub-array
     * @param high right most index of sub-array
     */
    void _buildSubTree(vector<NODE *> &nodes, NODE *&newRoot, int low, int high) {
        if (low > high) // base case when hitting the bounds of the oldOrder vector
            return;

        int mid = (low + high) / 2; // gets the middle index, or current node
        subPut(newRoot, nodes.at(mid)); // puts the node at mid of the vector into the new tree

        // recurse along the left half, and then the right half of vector
        _buildSubTree(nodes, newRoot, low, mid - 1);
        _buildSubTree(nodes, newRoot, mid + 1, high);
    }

    /**
     * altered original subSearchParentUpdateCount to update nR and nL for re-balanced re-threaded subtree
     * @param newRoot passed by reference newRoot
     * @param key the value of the key to be added
     * @return the node of the parent key
     */
    NODE *subSearchParentUpdateCount(NODE *&newRoot, keyType key) {
        NODE *cur = newRoot;
        NODE *parent = nullptr;

        while (cur != nullptr) { // until the end of tree, moves cur and prev down the tree
            if (key < cur->key) { // moves down left tree
                parent = cur;
                (parent->nL)++; // increments left node counter by 1
                cur = cur->left;
            } else if (key > cur->key) { // moves down right tree
                parent = cur;
                (parent->nR)++; // increments right node counter by 1
                cur = (cur->isThreaded) ? nullptr : cur->right; // treats threaded as a nullptr
            }
        }
        return parent; // if not found, returns nullptr
    }

    /**
     * altered original put function to build re-balanced and re-threaded sub-tree
     * @param newRoot the root of the new subtree
     * @param node the current node being added
     */
    void subPut(NODE *&newRoot, NODE *node) {
        // resets the node values as if fresh new nodes
        node->left = nullptr;
        node->right = nullptr;
        node->nL = 0;
        node->nR = 0;
        node->isThreaded = true; // new nodes will always be threaded

        // gets the parent of node being added while updating nL and nR counts
        NODE *parentAdd = subSearchParentUpdateCount(newRoot, node->key);
        if (parentAdd == nullptr)// checks if the parent is nullptr, means it is the first node added to tree
            newRoot = node;
        else if (node->key < parentAdd->key) { // checks if it is less than, parent left pointer is assigned
            node->right = parentAdd; // threaded to the parent
            parentAdd->left = node;
        } else { // else right parent pointer is assigned
            node->right = parentAdd->right; // threaded to parent nodes thread
            parentAdd->isThreaded = false; // parent is no longer threaded
            parentAdd->right = node;
        }
    }

    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    struct iterator {
    private:
        NODE *curr;  // points to current in-order node for begin/end

        // returns the smallest priority in the given tree
        NODE *findSmallest(NODE *cur) {
            while (cur->left != nullptr)
                cur = cur->left;
            return cur;
        }
    public:
        explicit iterator(NODE *node) {
            curr = node;
        }

        keyType operator*() {
            return curr->key;
        }

        bool operator==(const iterator &rhs) {
            return curr == rhs.curr;
        }

        bool operator!=(const iterator &rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        /**
         * advances curr to the next in-order node [ O(logn) ]
         * @return iterator(curr)
         */
        iterator operator++() {
            curr = (curr->isThreaded) ? curr->right : findSmallest(curr->right);
            return iterator(curr);
        }
    };

public:
    /**
     * creates an empty mymap [ O(1) ]
     */
    mymap() {
        root = nullptr;
        size = 0;
    }

    /**
     * constructs a mymap, which is a copy of other [ O(nlogn) ]
     * @param other mymap to be copied
     */
    mymap(const mymap &other) {
        root = nullptr;
        size = 0;
        _copy(other.root); // recursive pre-order
    }

    /**
     * clears this mymap and then makes a copy of other mymap [ O(nlogn) ]
     * @param other other mymap given to copy
     * @return the copied mymap of other
     */
    mymap &operator=(const mymap &other) {
        clear();
        _copy(other.root); // recursive preorder
        return *this;
    }

    /**
     * frees all memory associated with mymap, used for testing [ O(n) ]
     */
    void clear() {
        _clear(root);
        root = nullptr;
    }

    /**
     * frees memory of mymap automatically when leaves scope [ O(n) ]
     */
    ~mymap() { _clear(root); }

    /**
     * Inserts the key/value into the threaded, self-balancing BST based on the key. [ O(logn + mlogm) ]
     * n = total nodes in the tree, and m = number of nodes in the subtree
     * @param key key to be added
     * @param value value to be added with value
     */
    void put(keyType key, valueType value) {
        // checks if the node already exists, and only updates the value
        NODE *updateNode = search(key);
        if (updateNode != nullptr) {
            updateNode->value = value;
        } else { // creates a new node and adds to the tree
            NODE *temp = new NODE();
            temp->key = key;
            temp->value = value;
            temp->left = nullptr;
            temp->right = nullptr;
            temp->nL = 0;
            temp->nR = 0;
            temp->isThreaded = true; // new nodes will always be threaded

            NODE *violator = nullptr; // pointer to save where the first violator occurs
            NODE *parentAdd = searchParentUpdateCount(key, violator);

            if (parentAdd == nullptr)// checks if the parent is nullptr, means it is the first node added to tree
                root = temp;
            else if (temp->key < parentAdd->key) { // checks if it is less than, parent left pointer is assigned
                temp->right = parentAdd; // threaded to the parent
                parentAdd->left = temp;
            } else { // else right parent pointer is assigned
                temp->right = parentAdd->right; // threaded to parent nodes thread
                parentAdd->isThreaded = false; // parent is no longer threaded
                parentAdd->right = temp;
            }

            // if tree needs to be rebalanced
            if (violator != nullptr) {
                NODE *violatorParent = searchParent(violator->key); // saves the violators parent to add later

                // builds vector with all inorder nodes that need to be rebalanced
                vector<NODE *> treeRebal;
                _buildViolatorVector(treeRebal, violator);

                // builds vector using inorder nodes and recursion to correctly put nodes into new tree
                NODE *newRoot = nullptr;
                _buildSubTree(treeRebal, newRoot, 0, treeRebal.size() - 1);

                if (violator == root) // if the tree was rebalanced at the root
                    root = newRoot;
                else if (newRoot->key < violatorParent->key) // if it was a left child of another node
                    violatorParent->left = newRoot;
                else // if it was a right child of another node
                    violatorParent->right = newRoot;
            }

            size++; // increment the size by one when a new node is added and tree is properly rebalanced
        }
    }

    /**
     * returns whether key is in mymap or not [ O(logn) ]
     * @param key key to search for
     * @return true if in map, false if not
     */
    bool contains(keyType key) {
        NODE *foundNode = search(key);  // searches for the key, and returns a pointer to node with key if found
        if (foundNode == nullptr)
            return false;
        else
            return true;
    }

    /**
     * returns the value corresponding to the given key [ O(logn) ]
     * @param key key to search for
     * @return corresponding value if found, otherwise return default value
     */
    valueType get(keyType key) {
        NODE *foundNode = search(key); // searches for node with matching key
        if (foundNode == nullptr)
            return valueType();
        else
            return foundNode->value;
    }

    /**
     * either returns the value that matches the key, or adds the new key to the map [ O(logn +mlogm) ]
     * n = total number of nodes in threaded self balancing BST, m is the number of nodes in subtree being rebalanced
     * @param key desired key
     * @return value for the given key or the default value for the type if added
     */
    valueType operator[](keyType key) {
        valueType retVal = get(key);

        if (retVal == valueType())
            put(key, retVal);

        return retVal;
    }

    /**
     * returns the number of key/value pairs in the mymap, 0 if empty [ O(1) ]
     * @return size
     */
    int Size() { return size; }

    /**
     * returns the first inorder node [ O(logn) ]
     * @return iterator(curr) to first inorder node
     */
    iterator begin() {
        NODE *curr = findSmallest(root); // gets the smallest key
        return iterator(curr);
    }

    /**
     * returns last inorder node [ O(1) ]
     * @return iterator(nullptr)
     */
    iterator end() { return iterator(nullptr); }

    /**
     * returns an inorder string of the entire mymap [ O(n) ]
     * format: "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n"
     * @return string ^
     */
    string toString() {
        stringstream output;
        string final, line;
        _output(output, root); // loads stringstream object with each line being a value/pair in mymap
        return output.str();
    }

    /**
     * uses in-order recursion to return a vector of the {key, value} pairs in mymap [ O(n) ]
     * @return vector<> pairs
     */
    vector<pair<keyType, valueType> > toVector() {
        vector<pair<keyType, valueType> > pairs;
        _tovector(pairs, root); // stores each mymap pair into the vector
        return pairs;
    }

    /**
     * uses preorder recursion to return each key in the map,
     * along with its left (nL) and right (nR) node counts [ O(n) ]
     * "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
     * @return string in this form ^
     */
    string checkBalance() {
        stringstream output;
        string final, line;
        _outputBalanced(output, root); // loads stringstream object with each line being a value/pair in mymap
        return output.str();
    }
};

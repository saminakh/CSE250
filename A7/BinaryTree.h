// ============================================================================
// BinaryTree.h
// ~~~~~~~~~~~~
// hqn
// - A Very Basic Binary Tree Class
// - Nodes have string payloads
// ============================================================================

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <vector>
#include <string>
#include <map>

class BinaryTree
{
private:
    struct Node 
    {
        std::string payload;
        Node* left;
        Node* right;
        Node(std::string s = std::string(),
             Node* l = NULL, Node* r = NULL) : payload(s), left(l), right(r) 
        {}
    };

public:
    // default constructor
    BinaryTree();

    // this constructor constructs a tree from a preorder and an inorder vector
    BinaryTree(std::vector<std::string>& a, std::vector<std::string>& b);

    // destructor
    ~BinaryTree();

    /**
     * this changes the current tree to a new tree, using the 
     * preorder sequence a and inorder sequence b
     * - return true if the input sequences are good
     * - return false if they don't represent a tree
     */
    bool setTree(std::vector<std::string>& a, std::vector<std::string>& b);

    // simple size check
    bool isEmpty() const;

    // common traversal sequences
    std::string levelOrderSequence();
    std::string inOrderSequence();
    std::string postOrderSequence();
    std::string preOrderSequence();

    /**
     * TODO: you are to implement the following function
     */
    std::string horizontal();

    /**
     * TODO: you are to implement the following function
     */
    std::string vertical();

    /**
     * TODO: you are to implement the following function
     */
    std::string symmetric();
    //void maxLengthSym(Node*, size_t*);
    std::string helperSym(Node*);

    std::string baseVer(Node*);
    std::string leftVer(Node*, std::string);
    std::string rightVer(Node*, std::string);

private:
    /** 
     * auxiliary routine called by setTree to construct a new tree.
     * recursively construct a tree from a preorder vector and an inorder vector
     * a[a_start, ..., a_end] is the preorder sequence
     * b[b_start, ..., b_end] is the inorder sequence
     * where a_end = a_start + len
     *       b_end = b_start + len
     * this routines assumes that the preorder sequence is a permutation of
     * the inorder sequence
     */
    Node* constructTree(std::vector<std::string>& a, size_t a_start, 
                        std::vector<std::string>& b, size_t b_start, 
                        size_t len);

    // check if a vector of strings is a permutation of another
    bool isPermutation(std::vector<std::string> a, std::vector<std::string> b);

    // helper for inorder sequence
    std::string inOrderSequence(Node*);
    std::string postOrderSequence(Node*);
    std::string preOrderSequence(Node*);

    // helper function for destructor
    void clearTree(Node*);

    // TODO: helper functions or data for vertical print here

    // TODO: helper functions or data for horizontal print here

    // TODO: helper functions or data for symmetric print here

    // Google Style guide indicates that a trailing underscore should be put
    // at the end of data member names
    Node* root_;
};

#endif

#include "TreeNode.h"

void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
    return;
}

void TreeNode::setRight(TreeNode* newRight){
    right = newRight;
    return;
}
TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;
    left = NULL;
    right = NULL;
}

    // the destructor
TreeNode::~TreeNode(){
    delete entryPtr;
}

// gets the left child of the TreeNode.
TreeNode* TreeNode::getLeft() const{
    return left;
}

// gets the right child of the TreeNode
TreeNode* TreeNode::getRight() const{
    return right;
}

// returns a pointer to the DBentry the TreeNode contains. 
DBentry* TreeNode::getEntry() const{
    return entryPtr;
}
#ifndef RED_BLACK_TREE_IMPLEMENTATION_
#define RED_BLACK_TREE_IMPLEMENTATION_

#include "redBlackTree.h"

/**
 * Construct the tree.
 * negInf is a value less than equal to all others.
 */
template <typename Comparable>
RedBlackTree<Comparable>::RedBlackTree(const Comparable& negInf) : ITEM_NOT_FOUND(negInf)
{
	initTree();
}

/**
 * Copy constructor.
 */
template <typename Comparable>
RedBlackTree<Comparable>::RedBlackTree(const RedBlackTree<Comparable>& rhs)
	: ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{
	initTree();
	*this = rhs;
}

/**
 * Destructor.
 */
template <typename Comparable>
RedBlackTree<Comparable>::~RedBlackTree()
{
 	makeEmpty();
 	delete nullNode;
 	delete header;
}

/**
 * Return the maximum element if the red black tree is not empty.
 * Otherwise return ITEM_NOT_FOUND.
 */
template <typename Comparable>
const Comparable& RedBlackTree<Comparable>::findMax()const
{
	RedBlackNode *r = header;
	while (r -> right != nullNode)
		r = r -> right;
	return r -> element;
}

/**
 * Return the minimum element if the red black tree is not empty.
 * Otherwise return ITEM_NOT_FOUND.
 */
template <typename Comparable>
const Comparable& RedBlackTree<Comparable>::findMin() const
{
	RedBlackNode *r = header;
	while (r -> left != nullNode)
		r = r -> left;
	return r -> element;
}

/**
 * Return item that matchs ele.
 * If there is no item matchs ele, return ITEM_NOT_FOUND.
 */
template <typename Comparable>
Comparable RedBlackTree<Comparable>::find(const Comparable& ele)
{
	RedBlackNode *r = findAux(ele);
	if (r == nullNode)
		return ITEM_NOT_FOUND;
	return r -> element;
}

/**
 * Return true if ele is contained in red black tree.
 * Otherwise return false.
 */
template <typename Comparable>
bool RedBlackTree<Comparable>::contains(const Comparable& ele)
{
	findAux(ele);
	return current != nullNode;
}

/**
 * Return true if red black tree is empty.
 * Otherwise return false.
 */
template <typename Comparable>
bool RedBlackTree<Comparable>::isEmpty() const
{
	return header -> right == nullNode;
}

/**
 * Remove all nodes in red black tree.
 */
template <typename Comparable>
void RedBlackTree<Comparable>::makeEmpty()
{
	makeEmpty(header -> right);
	header -> left = header -> right = nullNode;
}

/**
 * Insert ele into red black tree.
 * Nothing will be done if ele is already in tree.
 */
template <typename Comparable>
void RedBlackTree<Comparable>::insert(const Comparable& ele)
{
	//insertButtomUp(ele);
	insertTopDown(ele);
}

/**
 * Remove node containing ele from red black tree.
 */
template <typename Comparable>
void RedBlackTree<Comparable>::remove(const Comparable& ele)
{
//	std::cout << "Has not implemented yet!" << std::endl;
	removeButtomUp(ele);
//	removeTopDown(ele);
}


/**
 * Print red black tree.
 */
template <typename Comparable>
void RedBlackTree<Comparable>::printTree() const
{
	if (isEmpty())
		std::cout << "Empty tree" << std::endl;
	else { 
		printTree(header -> right);
		std::cout << std::endl;
	}

}

/**
 * Assignment operation
 */
template <typename Comparable>
const RedBlackTree<Comparable>& RedBlackTree<Comparable>::operator=(const RedBlackTree<Comparable>& rhs)
{
	if (this != &rhs) {
		makeEmpty();
		header ->left = header -> right = clone(rhs.header -> right);
	}
	return *this;
}

/************************
 *						*
 * Internal functions	*
 *						*
 ************************/

/**
 * Initialize nullNode and header.
 */
template <typename Comparable>
void RedBlackTree<Comparable>::initTree()
{
 	nullNode = new RedBlackNode;
	nullNode -> left = nullNode -> right = nullNode;
	header = new RedBlackNode(ITEM_NOT_FOUND);
	header -> left = header -> right = nullNode;
	nullNode -> parent = header;
	header -> parent = nullNode;
}

/**
 * Return true if RedBlackNode rbn is black.
 */
template <typename Comparable>
bool RedBlackTree<Comparable>::isBlack(const typename RedBlackTree<Comparable>::RedBlackNode *rbn) const
{
	return rbn -> color == BLACK;
}

/**
 * Return true if RedBlackNode rbn is red.
 */
template <typename Comparable>
bool RedBlackTree<Comparable>::isRed(const typename RedBlackTree<Comparable>::RedBlackNode *rbn) const
{
	return rbn -> color == RED;
}

/**
 * Return node that contains ele in red black tree.
 */
template <typename Comparable>
typename RedBlackTree<Comparable>::RedBlackNode *RedBlackTree<Comparable>::findAux(const Comparable& ele)
{
	grand = parent = header;
	current = parent -> right;
	while (current != nullNode) {
		if (current -> element == ele)
			return current;
		else { 
			grand = parent;
			parent = current;
			if (current -> element < ele)
				current = current -> right;
			else 
				current = current -> left;
		}
	}
	return current;
}

/**
 * Recursively print subtree whose root is r.
 */
template <typename Comparable>
void RedBlackTree<Comparable>::printTree(const typename RedBlackTree<Comparable>::RedBlackNode* r) const
{
	if (r != nullNode) {
		printTree(r -> left);
		std::cout << r -> element << " ";
		printTree(r -> right);
	}
}

/**
 * Copy all nodes of tree whose root is rbn
 */
template <typename Comparable>
typename RedBlackTree<Comparable>::RedBlackNode *RedBlackTree<Comparable>::clone(const RedBlackNode* rbn)
{
	if (rbn != nullNode) {
		return new RedBlackNode(rbn -> element, clone(rbn -> left), clone(rbn -> right), rbn, rbn -> color);
	}
	return nullNode;
}

/**
 * Remove all nodes in subtree whose root is rbn
 */
template <typename Comparable>
void RedBlackTree<Comparable>::makeEmpty(typename RedBlackTree<Comparable>::RedBlackNode *rbn)
{
	if (rbn != nullNode) {
		makeEmpty(rbn -> left);
		makeEmpty(rbn -> right);
		delete rbn;
	}
}

/**
 * From node rbn up, adjust nodes to keep red black tree proprity
 */
template <typename Comparable>
void RedBlackTree<Comparable>::insertFixUp(RedBlackNode *rbn)
{	
	while (isRed(rbn -> parent)) {
		if (rbn -> parent == rbn -> parent -> parent -> left) {	// Node needs to be adjusted is in left subtree	
			if (isRed(rbn -> parent -> parent -> right)) {	// Case 1
				colorExchange(rbn -> parent -> parent);
				rbn = rbn -> parent -> parent;
			}					
			else {
				if (rbn == rbn -> parent -> right)	{	// Case 2
					rotateWithRightChild(rbn -> parent);
					rbn = rbn -> left;
				}
				rotateWithLeftChild(rbn -> parent -> parent);	// Case 3
				rbn -> parent -> color = BLACK;
				rbn -> parent -> right -> color = RED;
				break;
			}
		}
		else {							// Node needs to be adjusted is in right subtree
			if (isRed(rbn -> parent -> parent -> left)) {		// Case 1
				colorExchange(grand);
				rbn = rbn -> parent -> parent;
			}
			else {
				if (rbn == rbn -> parent -> left) {	// Case 2
					rotateWithLeftChild(rbn -> parent);
					rbn = rbn -> right;
				}
				rotateWithRightChild(rbn -> parent -> parent);
				rbn -> parent -> color = BLACK;
				rbn -> parent -> left -> color = RED;
				break;
			}
		}
	}
	header -> right -> color = BLACK;
}

/**
 * Exchange color between rbn and its children
 */
template <typename Comparable>
void RedBlackTree<Comparable>::colorExchange(typename RedBlackTree<Comparable>::RedBlackNode* rbn)
{
	if (isBlack(rbn) && isRed(rbn -> left) && isRed(rbn -> right)) {
		rbn -> color = RED;
		rbn -> left -> color = rbn -> right -> color = BLACK;
		return;
	}
	if (isRed(rbn) && isBlack(rbn -> left) && isBlack(rbn -> right)) {
		rbn -> color = BLACK;
		rbn -> left -> color = rbn -> right -> color = RED;
		return;
	}
}

/**
 * Rotate left 
 */
template <typename Comparable>
void RedBlackTree<Comparable>::rotateWithLeftChild(typename RedBlackTree<Comparable>::RedBlackNode *rbn)
{
//	std::cout << "Call rotate left" << std::endl;

	RedBlackNode *tmp = rbn -> left;
	rbn -> left = tmp -> right;
	tmp -> right -> parent = rbn;
	tmp -> right = rbn;
	tmp -> parent = rbn -> parent;
	if (rbn == header -> left) {
		header -> left = header -> right = tmp;
	}
	else {
		if (rbn -> parent -> left == rbn) {
			rbn -> parent -> left = tmp;
		}
		else {
			rbn -> parent -> right = tmp;
		}
	}
	rbn -> parent = tmp;
}

template <typename Comparable>
void RedBlackTree<Comparable>::rotateWithRightChild(typename RedBlackTree<Comparable>::RedBlackNode *rbn)
{
//	std::cout << "Call rotate right" << std::endl;

	RedBlackNode *tmp = rbn -> right;
	rbn -> right = tmp -> left;
	tmp -> left -> parent = rbn;
	tmp -> left = rbn;
	tmp -> parent = rbn -> parent;
	if (rbn == header -> left) {
		header -> left = header -> right = tmp;
	}
	else {
		if (rbn == rbn -> parent -> left) {
			rbn -> parent -> left = tmp;
		}
		else {
			rbn -> parent -> right = tmp;
		}
	}
	rbn -> parent = tmp;
}

/**
 * Insert ele into tree using buttom up method.
 */
template <typename Comparable>
void RedBlackTree<Comparable>::insertButtomUp(const Comparable& ele)
{
	RedBlackNode *r = findAux(ele);
	if (r != nullNode)	// ele is already in red black tree
		return;
	r = new RedBlackNode(ele, nullNode, nullNode, parent, RED);
	if (parent == header) {	// Empty tree
		header -> left = header -> right = r;
		r -> color = BLACK;
		return;
	}
	if (r -> element < parent -> element)
		parent -> left = r;
	else 
		parent -> right = r;
	insertFixUp(r);
}

/**
 * Insert ele into red black tree using top-down method.
 */
template <typename Comparable>
void RedBlackTree<Comparable>::insertTopDown(const Comparable& ele)
{	
	parent = header;
	current = parent -> left;
	while (current != nullNode) {
		if (isBlack(current) && isRed(current -> left) && isRed(current -> right)) {
			colorExchange(current);
			insertFixUp(current);
		}
		if (current -> element == ele) {
			break;
		}
		else {
			parent = current;
			if (current -> element < ele) {
				current = current -> right;
			}
			else {
				current = current -> left;
			}
		}
	}

	if (current != nullNode)	// ele is already in the tree
		return;
	RedBlackNode *r = new RedBlackNode(ele, nullNode, nullNode, parent, RED);
	if (parent == header) {
		header -> left = header -> right = r;
		r -> color = BLACK;
		return;
	}
	if (parent -> element > ele) 
		parent -> left = r;
	else 
		parent -> right = r;
	insertFixUp(r);
}

/**
 * Remove ele from the tree using buttom-up method.
 */
template <typename Comparable>
void RedBlackTree<Comparable>::removeButtomUp(const Comparable& ele)
{
	RedBlackNode *r = header -> right;
	while (r != nullNode) {
		if (ele < r -> element)
			r = r -> left;
		else if (ele == r -> element)
			break;
		else 
			r = r -> right;
	}
	if (r == nullNode)
		return;
	removeButtomUpAux(r);
}

template <typename Comparable>
void RedBlackTree<Comparable>::removeButtomUpAux(typename RedBlackTree<Comparable>::RedBlackNode *r)
{
	int deleteColor = r -> color;
	RedBlackNode *x;
	if (r -> left == nullNode && r -> right == nullNode) {
		x = r -> parent;
		if (r == x -> left)
			x -> left = nullNode;
		if (r == x -> right)
			x -> right = nullNode;
		delete r;
	}
	else if (r -> left == nullNode && r -> right) {
		x = r -> right;
		if (r == r -> parent -> left) 
			r -> parent -> left = x;
		else 
			r -> parent -> right = x;
		x -> parent = r -> parent;
		delete r;
	} 
	else if (r -> left && r -> right == nullNode) {
		x = r -> left;
		if (r == r -> parent -> left)
			r -> parent -> left = x;
		else
			r -> parent -> right = x;
		x -> parent = r -> parent;
		delete r;
	}
	else {
		x = r -> right;
		while (x -> left != nullNode) 
			x = x -> left;
		deleteColor = x -> color;
		r -> element = x -> element;
		r = x;
		if (x == x -> parent -> left)
			x -> parent -> left = x -> right;
		if (x == x -> parent -> right)
			x -> parent -> right = x -> right;
		if (x -> right != nullNode) {
			x -> right -> parent = x -> parent;
			x = x -> right;
		}
		else 
			x = x -> parent;
		delete r;
	}
	if (deleteColor == BLACK)
		removeFixUp(x);
}

/**
 * Keep red black tree's characteristics after removing some item from the tree.
 */
template <typename Comparable>
void RedBlackTree<Comparable>::removeFixUp(typename RedBlackTree<Comparable>::RedBlackNode *r)
{
	while (r != header && isBlack(r)) {
		if (r == r -> parent -> left) {
			if (isRed(r -> parent -> right)) {	// Case 1
				r -> parent -> color = RED;
				r -> parent -> right -> color = BLACK;
				rotateWithRightChild(r -> parent);
			}
			if (isBlack(r -> parent -> right -> left) && isBlack(r -> parent -> right -> right)) {	// Case 2
				r -> parent -> right -> color = RED;
				r = r -> parent;
			}
			else {
				if (isBlack(r -> parent -> right -> right)) {	// Case 3
					r -> parent -> right -> color = RED;
					r -> parent -> right -> left -> color = BLACK;
					rotateWithLeftChild(r -> parent -> right);
				}
				r -> parent -> right -> color = r -> parent -> color;	// Case 4
				r -> parent -> color = BLACK;
				rotateWithRightChild(r -> parent);
				r = header -> right;
			}
		}
		else {
			if (isRed(r -> parent -> left)) {	// Case 1
				r -> parent -> color = RED;
				r -> parent -> left -> color = BLACK;
				rotateWithLeftChild(r -> parent);
			}
			if (isBlack(r -> parent -> left -> left) && isBlack(r -> parent -> left -> right)) {	// Case 2
				r -> parent -> left -> color = RED;
				r = r -> parent;
			}
			else {
				if (isBlack(r -> parent -> left -> left)) {	// Case 3
					r -> parent -> left -> color = RED;
					r -> parent -> left -> right -> color = BLACK;
					rotateWithRightChild(r -> parent -> left);
				}
				r -> parent -> left -> color = r -> parent -> color;
				r -> parent -> color = BLACK;
				rotateWithLeftChild(r -> parent);
				r = header -> right;
			}

		}
	}
	r -> color = BLACK;
}
#endif	// RED_BLACK_TREE_IMPLEMENTATION_
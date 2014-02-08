#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "bst_tree.hh"
#include <cmath>

#ifdef DEBUG
#include <iostream>
#endif

namespace Asd
{
    template<typename Element>
    struct AvlTreeNode : public TreeNode<Element>
    {
	AvlTreeNode(const Element& e, AvlTreeNode* parent = 0)
	    :TreeNode<Element>(e, parent), balance(0), rheight(0), lheight(0)
	    {}

	int balance;
	int rheight;
	int lheight;
    };

    template<typename Element>
    class AvlTree : public BstTree<Element>
    {
    public:
	void insert(const Element& e);
	void remove(const Element& e);
	int height() const; 
	
    private:
	typedef AvlTreeNode<Element> Node;
    protected:
	void rotateLeft(Node*);
	void rotateRight(Node*);
	void rotateLeftRight(Node*);
	void rotateRightLeft(Node*);
	void balance(Node*);
	void balanceToRoot(Node*);
	int height(const Node*) const;
    };

    template<typename Element>
    void AvlTree<Element>::insert(const Element& e)
    {
#ifdef DEBUG
	std::cout << "Inserting: " << e << std::endl;
#endif
	balanceToRoot(dynamic_cast<Node*>(BstTree<Element>::insertNode(new Node(e))));
    }

    template<typename Element>
    void AvlTree<Element>::remove(const Element& e)
    {
#ifdef DEBUG
	std::cout << "Removing: " << e << std::endl;
#endif
	balanceToRoot(dynamic_cast<Node*>(BstTree<Element>::removeNode(BstTree<Element>::find(e))));
    }
    
    template<typename Element>
    int AvlTree<Element>::height() const
    {
	return height(dynamic_cast<Node*>(Tree<Element>::root_));
    }
    
    template<typename Element>
    void AvlTree<Element>::balanceToRoot(Node* node)
    {
#ifdef DEBUG
	if(node)
	    std::cout << "Balancing to root: " << node->element << std::endl;
#endif
	while(node)
	{
	    balance(node);
	    node = dynamic_cast<Node*>(node->parent);
	}
    }

    template<typename Element>
    void AvlTree<Element>::balance(Node* node)
    {
	node->lheight = height(dynamic_cast<Node*>(node->left));
	node->rheight = height(dynamic_cast<Node*>(node->right));
	node->balance = node->rheight - node->lheight;
#ifdef DEBUG
	std::cout << "Balancing: " << node->element
		  << "[balance: " << node->balance << "]"
		  << "[height: " << height(dynamic_cast<Node*>(node)) << "]" << std::endl;
#endif
	if(node->balance < -1)
	{
	    if(dynamic_cast<Node*>(node->left)->balance < 0)
		rotateRight(node);
	    else
		rotateLeftRight(node);
	}
	if(node->balance > 1)
	{
	    if(dynamic_cast<Node*>(node->right)->balance > 0)
		rotateLeft(node);
	    else
		rotateRightLeft(node);		
	}
    }
    
    template<typename Element>
    int AvlTree<Element>::height(const Node* node) const
    {
	return node == 0 ? -1 : (std::max(node->lheight, node->rheight) + 1);
    }

    template<typename Element>
    void AvlTree<Element>::rotateRight(Node* node)
    {
#ifdef DEBUG
	std::cout << "Rotating right: " << node->element 
		  << "[pivot: " << node->left->element << "]" << std::endl;
#endif
	Node* pivot = dynamic_cast<Node*>(node->left);
	node->left = pivot->right;
	if(node->left)
	    node->left->parent = node;

	BstTree<Element>::swapChild(node, pivot);

	pivot->right = node;
	pivot->right->parent = pivot;

	balance(node);
    }

    template<typename Element>
    void AvlTree<Element>::rotateLeft(Node* node)
    {
#ifdef DEBUG
	std::cout << "Rotating left: " << node->element
		  << "[pivot: " << node->right->element << "]" << std::endl;
#endif
	Node* pivot = dynamic_cast<Node*>(node->right);
	node->right = pivot->left;
	if(node->right)
	    node->right->parent = node;

	BstTree<Element>::swapChild(node, pivot);

	pivot->left = node;
	pivot->left->parent = pivot;

	balance(node);
    }

    template<typename Element>
    void AvlTree<Element>::rotateRightLeft(Node* node)
    {
#ifdef DEBUG
	std::cout << "Rotating right-left: " << node->element << std::endl;
#endif
 	rotateRight(dynamic_cast<Node*>(node->right));
	rotateLeft(node);
    }

    template<typename Element>
    void AvlTree<Element>::rotateLeftRight(Node* node)
    {
#ifdef DEBUG
	std::cout << "Rotating left-right: " << node->element << std::endl;
#endif
 	rotateLeft(dynamic_cast<Node*>(node->left));
	rotateRight(node);
    }
}


#endif // AVL_TREE_HPP

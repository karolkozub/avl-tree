#ifndef ASD_BST_TREE_HPP
#define ASD_BST_TREE_HPP

#include "tree.hh"
#include <cmath>

namespace Asd
{

    template <typename Element>
    class BstTree : public Tree<Element>
    {
    public:
	~BstTree();

	bool empty() const;
	bool member(const Element& el) const;
	void insert(const Element& el);
	void remove(const Element& el);
	int height() const;
	
	void clear();
	
    protected:
	typedef TreeNode<Element> Node;
	Node* find(const Element&) const;
	Node* insertNode(Node*);
	Node* removeNode(Node*);
	void clearNode(Node*);

	void swapChild(Node* from, Node* to);
	Node* findPredecessor(Node*);
	int height(Node*) const;
    };

    template <typename Element>
    BstTree<Element>::~BstTree()
    {
	clear();
    }

    template <typename Element>
    void BstTree<Element>::clear()
    {
	clearNode(Tree<Element>::root_);
	Tree<Element>::root_ = 0;
    }

    template <typename Element>
    int BstTree<Element>::height() const
    {
	return height(Tree<Element>::root_);
    }

    template <typename Element>
    int BstTree<Element>::height(Node* node) const
    {
	return node == 0 ? -1 : (std::max(height(node->left), height(node->right)) + 1);
    }


    template <typename Element>
    void BstTree<Element>::clearNode(Node* node)
    {
	if(node)
	{
	    clearNode(node->left);
	    clearNode(node->right);
	    delete node;
	}
    }

    template <typename Element>
    bool BstTree<Element>::empty() const
    {
	return Tree<Element>::root_ == 0;
    }
    
    template <typename Element>
    bool BstTree<Element>::member(const Element& el) const
    {
	return find(el);
    }

    template <typename Element>    
    void BstTree<Element>::insert(const Element& el)
    {
	insertNode(new Node(el));
    }

    template <typename Element>
    TreeNode<Element>* BstTree<Element>::insertNode(Node* node)
    {
	if(!Tree<Element>::root_)
	    Tree<Element>::root_ = node;
    
	for(Node* n = Tree<Element>::root_; n->element != node->element;)
	{
	    if(node->element > n->element)
	    {
		if(!n->right)
		{
		    n->right = node;
		    node->parent = n;
		}
	    
		n = n->right;
	    }
	    else
	    {
		if(!n->left)
		{
		    n->left = node;
		    node->parent = n;
		}
	    
		n = n->left;
	    }
	}

	return node;
    }

    template<typename Element>
    void BstTree<Element>::remove(const Element& e)
    {
	removeNode(find(e));
    }

    template<typename Element>
    TreeNode<Element>* BstTree<Element>::removeNode(Node* del)
    {
	if(!del)
	    return 0;

	Node* parent = del->parent;

	if(del->left && del->right)
	{
	    Node* repl = findPredecessor(del);
	    parent = repl->parent;
		
	    swapChild(repl, repl->left);

	    del->element = repl->element;
	    del = repl;
	}
	else
	{
	    swapChild(del, del->left ? del->left : del->right);
	}

	delete del;
	return parent;
    }

    template <typename Element>
    TreeNode<Element>* BstTree<Element>::find(const Element& el) const
    {
	Node* node = Tree<Element>::root_;
	
	while(node && node->element != el)
	    node = (el > node->element) ? node->right : node->left;
	
	return node;
    }

    template <typename Element>
    void BstTree<Element>::swapChild(Node* from, Node* to)
    {
	if(from->parent)
	{
	    if(from->parent->left == from)
		from->parent->left = to;
	    else
		from->parent->right = to;

	    if(to)
		to->parent = from->parent;
	}
	else if(from == Tree<Element>::root_)
	{
	    Tree<Element>::root_ = to;
	    if(to)
		to->parent = 0;
	}
    }

    template<typename Element>
    TreeNode<Element>* BstTree<Element>::findPredecessor(Node* node)
    {
	Node* pred = node->left;
	    
	while(pred->right)
	    pred = pred->right;
	
	return pred;
    }
}

#endif

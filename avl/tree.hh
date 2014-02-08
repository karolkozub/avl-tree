#ifndef ASD_TREE_HPP
#define ASD_TREE_HPP

#include <ostream>

namespace Asd
{

    template <typename Element>
    struct TreeNode
    {
	TreeNode(const Element& e, TreeNode* parent = 0)
	    :element(e), parent(parent), left(0), right(0)
	    {}

	virtual ~TreeNode() {}
    
	Element element;
	TreeNode* parent;
	TreeNode* left;
	TreeNode* right;
    };

    template <typename Element>
    class Tree
    {
    public:
	Tree():root_(0) {}
	virtual ~Tree() {}
  
	virtual bool empty() const = 0;
	virtual bool member(const Element&) const = 0;
	virtual void insert(const Element&) = 0;
	virtual void remove(const Element&) = 0;
	virtual int height() const = 0;


	virtual void printPreOrder(std::ostream&) const;
	virtual void printInOrder(std::ostream&) const;
	virtual void printPostOrder(std::ostream&) const;

    protected:
	TreeNode<Element>* root_;

	virtual void printNodePreOrder(const TreeNode<Element>*, std::ostream&) const;
	virtual void printNodeInOrder(const TreeNode<Element>*, std::ostream&) const;
	virtual void printNodePostOrder(const TreeNode<Element>*, std::ostream&) const;

	virtual void printNode(const TreeNode<Element>*, std::ostream&) const;
    };

    template <typename Element>
    void Tree<Element>::printPreOrder(std::ostream& os) const
    {
	printNodePreOrder(root_, os);
	os << std::endl;
    }

    template <typename Element>
    void Tree<Element>::printInOrder(std::ostream& os) const
    {
	printNodeInOrder(root_, os);
	os << std::endl;
    }

    template <typename Element>
    void Tree<Element>::printPostOrder(std::ostream& os) const
    {
	printNodePostOrder(root_, os);
	os << std::endl;
    }

    template <typename Element>
    void Tree<Element>::printNodePreOrder(const TreeNode<Element>* n, std::ostream& os) const
    {
	if(n)
	{
	    printNode(n, os);
	    printNodePreOrder(n->left, os);
	    printNodePreOrder(n->right, os);
	}
    }

    template <typename Element>
    void Tree<Element>::printNodeInOrder(const TreeNode<Element>* n, std::ostream& os) const
    {
	if(n)
	{
	    printNodeInOrder(n->left, os);
	    printNode(n, os);
	    printNodeInOrder(n->right, os);
	}
    }

    template <typename Element>
    void Tree<Element>::printNodePostOrder(const TreeNode<Element>* n, std::ostream& os) const
    {
	if(n)
	{
	    printNodePostOrder(n->left, os);
	    printNodePostOrder(n->right, os);
	    printNode(n, os);
	}
    }

    template <typename Element>
    void Tree<Element>::printNode(const TreeNode<Element>* n, std::ostream& os) const
    {
	os << n->element << ' ';
    }

} // namespace Asd

#endif //ASD_TREE_HPP

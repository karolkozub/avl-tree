#include <string>
#include <sstream>
#include <iostream>
#include "bst_tree.hh"
#include "avl_tree.hh"

void interactive_test(std::istream& is, std::ostream& os)
{
    using namespace Asd;
    BstTree<int>* bst = new BstTree<int>();
    AvlTree<int>* avl = new AvlTree<int>();
    BstTree<int>* tree = avl;
    std::string command, line;
    std::stringstream stream;
    int arg;

    while(is.good())
    {
	std::getline(is, line);
	if(!is.good())
	    break;

	stream.clear();
	stream.str(line + ' ');
	command = "";
	stream >> command;
	
	if(command == "")
	    continue;

	if(command == "insert")
	{
	    while(stream.good())
	    {
		stream >> arg;
		if(stream.good())
		    tree->insert(arg);
	    }
	}else if(command == "remove")
	{
	    while(stream.good())
	    {
		stream >> arg;
		if(stream.good())
		    tree->remove(arg);
	    }
	}else if(command == "clear")
	{
	    tree->clear();
	}else if(command == "member")
	{
	    stream >> arg;
	    os << (tree->member(arg)?"true":"false") << std::endl;
	}else if(command == "height")
	{
	    os << tree->height() << std::endl;
	}else if(command == "empty")
	{
	    os << (tree->empty()?"true":"false") << std::endl;
	}else if(command == "preorder")
	{
	    tree->printPreOrder(os);
	}else if(command == "inorder")
	{
	    tree->printInOrder(os);
	}else if(command == "postorder")
	{
	    tree->printPostOrder(os);
	}else if(command == "settree")
	{
	    stream >> command;
	    if(command == "avl")
		tree = avl;
	    else if(command == "bst")
		tree = bst;
	    else
		os << "Invalid tree type '" << command << "' choose from [avl, bst]" << std::endl;

	    tree->clear();
	}else if(command == "help")
	{
	    os << "Valid commands:\n"
	       << "\t insert int [int ...]\n"
	       << "\t remove int [int ...]\n"
	       << "\t empty\n"
	       << "\t member int\n"
	       << "\t clear\n"
	       << "\t height\n"
	       << "\t preorder\n"
	       << "\t inorder\n"
	       << "\t postorder\n"
	       << "\t settree [avl|bst]\n"
	       << "\t help"
	       << std::endl;
	}else
	{
	    os << "Invalid command '" << command << "'. Type 'help' for the list of valid commands." << std::endl;
	}
	
    }

    delete avl;
    delete bst;
}

int main()
{
    interactive_test(std::cin, std::cout);

    return 0;
}

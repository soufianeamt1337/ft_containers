/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:55:57 by samajat           #+#    #+#             */
/*   Updated: 2023/03/03 16:16:02 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "red_black_tree.hpp"
#include "pair.hpp"
#include <functional>
#include <memory>
#include <iostream>
#include <algorithm>
#include <map>
#include "../containers/map.hpp"
#include "../containers/vector.hpp"

#include <math.h>

class value_compare
{
    
        std::less<int> comp;
        typedef 	ft::pair<const int,int>    value_type;
    public:
        value_compare(std::less<int> c) : comp(c) {}
        bool operator()(const value_type &_lhs, const value_type &_rhs) const
        {
            return comp(_lhs.first, _rhs.first);
        }
};


typedef ft::RedBlack_tree <int, int, value_compare ,std::allocator<int> > bst;

typedef ft::Node<ft::pair <const int, int> >*  NodePtr;


template <typename Node_ptr>
void    print_node(Node_ptr node)
{
    std::cout << "Key: "<< node->data.first  << std::endl;
    if (node->parent)
        std::cout << "parent: "<< node->parent->data.first  << std::endl;
    if (node->left)
        std::cout << "left: "<< node->left->data.first  << std::endl;
    if (node->right)
        std::cout << "right: "<< node->right->data.first  << std::endl;
    std::cout << "--------------\n";
}


//  void padding(char c, int n) 
//         {
//             for (int i = 0; i < n; i++)
//                 std::cout << c;
//         }

//   void find_node_next(NodePtr root, int lvl, NodePtr *arr, size_t &indx)
//         {
//             if (!root)
//             {
//                 lvl = pow(2, lvl);
//                 while (lvl-- > 0)
//                     arr[indx++] = NULL;
//                 return ;
//             }
//             if (lvl == 1)
//             {
//                 arr[indx++] = root->left;
//                 arr[indx++] = root->right;
//                 return;
//             }
//             find_node_next(root->left, lvl-1, arr, indx);
//             find_node_next(root->right, lvl-1, arr, indx);
//         }

//  void print_tree_2(NodePtr _root)
//         {
//             NodePtr arr[1000000];
//             size_t index = 1;
//             size_t height = 2 * log2(10);
            
//             arr[0] = _root;
//             for (size_t j = 0 ; j < height; j++)
//                     find_node_next(_root, j + 1, arr, index);
//             size_t lvl = 1;
//             int pad = height * 16;
//             while (arr[--index] == NULL);
//             for (size_t i = 0; i <= index; i++)
//             {
//                 if (i + 1 == lvl)
//                 {                
//                     std::cout << "\n\n\n";
//                     lvl *= 2;
//                     pad /= 2;
//                 }
//                 padding(' ', pad);
//                 if (arr[i])
//                 {
//                     if (arr[i]->color == RED)
//                         std::cout << "\e[0;31m";
//                     std::cout << '(' << arr[i]->data.first << ')' << "\e[0m";
//                 }
//                 else
//                     std::cout << "  ";
//                 padding(' ', pad);
//             }
//             std::cout << "\n\n\n";
//             (void)_root;
//             (void)arr;
//         }

int main ()
{
    ft::map <int, int > m;

    m.insert_test (ft::make_pair(40, 0), BLACK);
    m.insert_test (ft::make_pair(20, 0), BLACK);
    m.insert_test (ft::make_pair(60, 0), BLACK);
    m.insert_test (ft::make_pair(10, 0), BLACK);
    m.insert_test (ft::make_pair(30, 0), BLACK);
    m.insert_test (ft::make_pair(50, 0), BLACK);
    m.insert_test (ft::make_pair(80, 0), RED);
    m.insert_test (ft::make_pair(90, 0), BLACK);
    m.insert_test (ft::make_pair(70, 0), BLACK);
    m.insert_test (ft::make_pair(100, 0), RED);
    m.print_tree ();
    m.erase(50);
    m.print_tree ();
    m.erase(20);
    m.print_tree ();
    // bst a;
    // bool s;
    // a.insert(ft::make_pair(42, "lol"));
	// a.insert(ft::make_pair(42, "mdr"));

	// a.insert(ft::make_pair(50, "mdr"));
	// a.insert(ft::make_pair(35, "funny"));

	// a.insert(ft::make_pair(45, "bunny"));
	// a.insert(ft::make_pair(21, "fizz"));
	// a.insert(ft::make_pair(38, "buzz"));

    //     a.insert(ft::make_pair(10, 3) );
    //     a.insert(ft::make_pair(5, 3) );
    //     a.insert(ft::make_pair(30, 3) );
    //     a.insert(ft::make_pair(40, 3) );
    //     a.insert(ft::make_pair(25, 3) );
    //     a.insert(ft::make_pair(2, 3) );
    //     a.insert(ft::make_pair(35, 3) );
    //     a.insert(ft::make_pair(38, 3) );
    //     a.insert(ft::make_pair(50, 3) );
    //     a.insert(ft::make_pair(36, 3) );
    //     a.insert(ft::make_pair(37, 3) );
    //     a.insert(ft::make_pair(38, 3) );
    }
    
    
//     print_tree_2 (a.__tree_root, a.size());
//     a.erase (30);
//     print_tree_2 (a.__tree_root, a.size());

// }

// int    func (bool & b)
// {
//     b = false;
// return (true);
// }

// int print(bool p)
// {
//     if (p)
//         std::cout << "hello\n";
//     return (true);
// }

// // typedef int bla;
// #define NAME_SPACE ft
// #include <iterator>
// int main ()
// {
//     NAME_SPACE::map <int, int > m;
//     m.insert (NAME_SPACE::pair<int, int >(1, 4));
//     m.insert (NAME_SPACE::pair<int, int >(5, 4));
//     m.insert (NAME_SPACE::pair<int, int >(9, 4));
//     m.insert (NAME_SPACE::pair<int, int >(2, 4));
//     std::cout <<m.equal_range(-10).first->first << std::endl;
//     std::cout <<m.equal_range(-10).second->first << std::endl;
//     // m.insert (ft::pair <int, int > (4, 4));
//     // m.insert (ft::pair <int, int > (4, 4));
//     // m.insert (ft::pair <int, int > (4, 4));
//     // for ( ft::map <int, int, std::greater<int> >::iterator i = m.begin(); i != m.end(); i++)
//     //     std::cout << i->first << std::endl;
// }

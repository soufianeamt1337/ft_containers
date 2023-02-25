/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:55:57 by samajat           #+#    #+#             */
/*   Updated: 2023/02/25 16:22:10 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.hpp"
#include "pair.hpp"
#include <functional>
#include <memory>
#include <iostream>
#include <algorithm>
#include <map>
#include "../containers/map.hpp"


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


typedef ft::binary_tree <int, int, value_compare ,std::allocator<int> > bst;

template <typename Iterator>
void    print_node(Iterator node)
{
    std::cout << "Key: "<< node->first  << std::endl;
    if (node.base()->parent)
        std::cout << "parent: "<< node.base()->parent->data.first  << std::endl;
    if (node.base()->left)
        std::cout << "left: "<< node.base()->left->data.first  << std::endl;
    if (node.base()->right)
        std::cout << "right: "<< node.base()->right->data.first  << std::endl;
    std::cout << "--------------\n";
}



int main ()
{
     bst a;
    bool s;

    srand (time(NULL));
    // for (size_t i = 1; i < 4; i++)
        a.insert(ft::make_pair(5, 3));
        a.insert(ft::make_pair(1, 3));
        a.insert(ft::make_pair(6, 3));
    
    // bst::iterator it = ++a.begin(); 
    // bst::iterator it1 = ++(++(a.begin())); 
    // // std::cout << it->first << " ----- " << it1->first << std::endl;
    // print_node (it);
    // print_node (it1);

    // it.base()->swap_for_deletion ((it1).base());
    // a.__tree_root = (it1).base();

    // print_node (it);
    // bst::iterator i = a.begin() ;
    bst::const_iterator i = a.begin();
    for (bst::const_iterator i = a.begin() ; i != a.end() ; i++)
    {
        std::cout << i.base()<< std::endl;
        print_node (i);
    }
    std::cout << "\n\n###################\n\n";
    a.erase(++(++a.begin()) , a.end());
    
    for (bst::const_iterator i = a.begin() ; i != a.end() ; i++)
    {
        std::cout << i.base()<< std::endl;
        print_node (i);
    }

    // for (bst::iterator i = a.begin() ; i != a.end() ; i++)
    //     print_node (i);
    // print_node (i);

    // for (bst::iterator it = a.begin(); it != a.end(); it++)
    //     std::cout << it->first << "---" << it->second << std::endl;
    
}

// int main ()
// {
//     std::map <int , int > a;
//     a.insert(std::make_pair(5, 3));
//     a.insert(std::make_pair(1, 3));
//     a.insert(std::make_pair(6, 3));

//     for (std::map <int , int >::const_iterator i = a.begin(); i != a.end(); i++)
//         std::cout << i->first << std::endl;
// }

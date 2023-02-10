/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:13:44 by samajat           #+#    #+#             */
/*   Updated: 2023/02/10 18:58:31 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functional>
#include <utils.hpp>

#include "iterators/bidirectional_it.hpp"
#include "iterators/reverse_iterator.hpp"
#include "tree.hpp"

namespace ft
{

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T>>
    > class map
{

    typedef     Key                                 key_type;
    typedef     T                                   mapped_type;
    typedef 	pair<const key_type,mapped_type>    value_type;
    typedef     Compare                 key_compare;
    //value_compare
    typedef     Allocator               allocator_type;
    typedef     value_type&             reference;
    typedef     const  value_type&      const_reference;
    typedef     value_type*	            pointer;
    typedef     const pointer           const_pointer;
    typedef     size_t                  size_type;
    typedef     ptrdiff_t               difference_type;


    /*Iterators*/
    typedef typename              ft::bidirectional_it<pointer>                iterator;
    typedef typename              ft::bidirectional_it<const_pointer>          const_iterator;
    
    /*reverse_iterator*/
    typedef typename              ft::reverse_iterator<iterator >            reverse_iterator;
    typedef typename              ft::reverse_iterator<const_iterator >      const_reverse_iterator;




    explicit map( const key_compare& comp =  key_compare(),
                  const allocator_type& alloc = allocator_type() );
    
    template< class InputIt >
    map( InputIt first, InputIt last,
         const key_compare& comp = key_compare(),
         const allocator_type& alloc = allocator_type() );
    
    map( const map& other );

    map&                               operator=( const map& other );

    //Capacity

    size_type                           size() const;
    size_type                           max_size() const;
    bool                                empty() const;

    //Element access:                   
    mapped_type&                        operator[] (const key_type& k);
    mapped_type&                        at (const key_type& k);
    const mapped_type&                  at (const key_type& k) const;

        //Modifiers
    iterator                            insert (iterator position, const_reference val);
    
    template <class InputIterator> 
    void                                insert (InputIterator first, InputIterator last);
    
    iterator                            erase (iterator position);
    iterator                            erase (iterator first, iterator last);
    size_type                           erase (const key_type& k);
    void                                swap (map& x);
    void                                clear();

    //iterators
    iterator                begin();
    const_iterator          begin() const;
    iterator                end();
    const_iterator          end() const;
    
    //reverse iterators
    reverse_iterator       rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator       rend();
    const_reverse_iterator rend() const;

    //Observers:
    key_compare                         key_comp() const;
    value_compare                       value_comp() const;

    //Operations:
    iterator                            find (const key_type& k);
    const_iterator                      find (const key_type& k) const;
            
    size_type                           count (const key_type& k) const;
                
    iterator                            lower_bound (const key_type& k);
    const_iterator                      lower_bound (const key_type& k) const;
                
    iterator                            upper_bound (const key_type& k);
    const_iterator                      upper_bound (const key_type& k) const;

    pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
    pair<iterator,iterator>             equal_range (const key_type& k);

    allocator_type                      get_allocator() const;

    ~map();

    private:
    //all the member functions of the _tree have to be friends and private 
    binary_tree                 _tree;
    key_compare                 _comp;
    allocator_type              _allocat;
};



template< class Key, class T, class Compare , class Allocator  > 
map<Key, T, Compare, Allocator>::map()
{
    
}


template< class Key, class T, class Compare , class Allocator  > 
map<Key, T, Compare, Allocator>::map( const map& other )
{
    for (iterator it = other.begin(); it != other.end() ; it++)
        insert(end(), *it);
    _allocat = other._allocat;
    _comp = other._comp;
}

template< class Key, class T, class Compare , class Allocator  > 
map<Key, T, Compare, Allocator>&    
map<Key, T, Compare, Allocator>::operator=( const map& other )
{
    clear();
    for (iterator it = other.begin(); it != other.end() ; it++)
        insert(end(), *it);
    _allocat = other._allocat;
    _comp = other._comp;
}


template< class Key, class T, class Compare , class Allocator  > 
typename map<Key, T, Compare, Allocator>::size_type
map<Key, T, Compare, Allocator>::size() const
{
    return (_tree.size());
}


template< class Key, class T, class Compare , class Allocator  > 
typename map<Key, T, Compare, Allocator>::size_type
map<Key, T, Compare, Allocator>::max_size() const
{
    return (_allocat.max_size());
}

template< class Key, class T, class Compare , class Allocator  > 
bool   map<Key, T, Compare, Allocator>::empty() const
{
    return (!size());
}


template< class Key, class T, class Compare , class Allocator  > 
typename map<Key, T, Compare, Allocator>::mapped_type&    
map<Key, T, Compare, Allocator>::operator[] (const key_type& k)
{
    tree_node   *node = _tree.search(k);
    if (!node)
        insert (end(), pair<k, mapped_type());
    return (node->data.second);
}



template< class Key, class T, class Compare , class Allocator  > 
typename map<Key, T, Compare, Allocator>::mapped_type&
map<Key, T, Compare, Allocator>::at (const key_type& k)
{
    tree_node   *node = _tree.search(k);
    if (!node)
        throw std::out_of_range ("Out of range please provide a valid key to map!");
    return (node->data.second);
}


template< class Key, class T, class Compare , class Allocator  > 
const typename map<Key, T, Compare, Allocator>::mapped_type&    
map<Key, T, Compare, Allocator>::at (const key_type& k) const
{
    tree_node   *node = _tree.search(k);
    if (!node)
        throw std::out_of_range ("Out of range please provide a valid key to map!");
    return (node->data.second);
}



template< class Key, class T, class Compare , class Allocator  > 
void map<Key, T, Compare, Allocator>::swap (map& x)
{
    std::swap(_tree, x._tree);
    std::swap(this->_v_size, x._v_size);
    std::swap(this->allocator, x.allocator);
}

template< class Key, class T, class Compare , class Allocator  > 
void map<Key, T, Compare, Allocator>::clear()
{
    _tree.clear();
}


template< class Key, class T, class Compare , class Allocator  > 
typename map<Key, T, Compare, Allocator>::key_compare
map<Key, T, Compare, Allocator>::key_comp() const
{
    return (_comp);
}


template< class Key, class T, class Compare , class Allocator  > 
typename map<Key, T, Compare, Allocator>::iterator                            
map<Key, T, Compare, Allocator>::find (const key_type& k)
{
    
}

template< class Key, class T, class Compare , class Allocator  > 
typename map<Key, T, Compare, Allocator>::const_iterator                     
map<Key, T, Compare, Allocator>::find (const key_type& k) const
{
    
}


}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:32:37 by samajat           #+#    #+#             */
/*   Updated: 2023/03/07 15:31:37 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "../dependencies/utility.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../dependencies/red_black_tree.hpp"

namespace ft
{
template < class T, class Compare = std::less<T>,  class Alloc = std::allocator<T> > 
class set
{
       public:
    
    typedef     T                                            key_type;
    typedef 	const key_type                                     value_type;
    typedef     Compare                                      key_compare;/////set has non_cpmleted memebers 
    typedef     Compare                                      value_compare;
    typedef     Alloc                                    allocator_type;
    typedef     value_type&                                  reference;
    typedef     value_type*	                                 pointer;
    typedef     const value_type*	                         const_pointer;
    typedef     size_t                                       size_type;
    typedef     ptrdiff_t                                    difference_type;
    typedef     ft::Node<value_type>                             Node;
    typedef     Node*                                        node_ptr;
    typedef 	pair<const key_type,value_type>             pair;
    


    typedef     const value_type&                  const_reference;

    typedef     ft::RedBlack_tree<value_type,  value_compare, allocator_type>  RedBlack_tree;


    /*Iterators*/
    typedef typename              RedBlack_tree::const_iterator                iterator;
    typedef typename              RedBlack_tree::const_iterator         const_iterator;
    
    
    
    /*reverse_iterator*/
    typedef typename              ft::reverse_iterator<const_iterator >            reverse_iterator;
    typedef typename              ft::reverse_iterator<const_iterator >      const_reverse_iterator;


    private:
    
    RedBlack_tree                 __tree;

/* ************************************************************************** */
                            // Costructors :
/* ************************************************************************** */
    public:
    explicit 
    set( const key_compare& key_comp =  key_compare(),
                  const allocator_type& alloc = allocator_type() ):__tree(value_compare(key_comp), alloc){}

    template< class InputIt >
    set( InputIt first, InputIt last,
         const key_compare& key_comp = key_compare(),
         const allocator_type& alloc = allocator_type() ):__tree(key_comp, alloc)
         {   
            __tree.insert (first, last);
         }
         
    
    set( const set& other ) :__tree(other.__tree){   }

// /* ************************************************************************** */
//                             // operator= :
// /* ************************************************************************** */

    set&                                operator=( const set& other ){      this->__tree = other.__tree;    return (*this);}


// /* ************************************************************************** */
//                             // Capacity= :
// /* ************************************************************************** */
    size_type                           size() const{   return (__tree.__size);}
    size_type                           max_size() const{   return (__tree.max_size());}
    bool                                empty() const{  return (__tree.size() == 0);}


// /* ************************************************************************** */
//                             // Modifiers= :
// /* ************************************************************************** */

    ft::pair<iterator,bool>                 insert (const value_type& val)
    {
        ft::pair <node_ptr, bool> ret = __tree.insert(val);
        return (ft::make_pair(iterator(ret.first) , ret.second));
    }
    iterator                            insert (iterator position, const_reference val){    return iterator(__tree.insert(position.__node, val)); }
    
    template <class InputIterator> 
    void                                insert (InputIterator first, InputIterator last){ 
        while (first != last)
        {
            insert(*first);
            first++;
        }
    }
    
    
    iterator                            erase (iterator position) { return iterator(__tree.erase(position.base()));}
    iterator                            erase (iterator first, iterator last)
    {        
        iterator to_erase ;
        while (first != last)
        {
            to_erase = first++;
            __tree.erase (to_erase.__node);
        }
        if (!__tree.__size){     __tree.__tree_root = nullptr;}
        return (to_erase);
    }
    size_type                           erase (const key_type& k){  return (__tree.erase(k));    }
    
    void                                swap (set& x) { __tree.swap (x.__tree);}
    void                                clear() {   __tree.clear(); }

// /* ************************************************************************** */
//                             // iterators= :

// /* ************************************************************************** */
    iterator                            begin(){    return (__tree.begin());}
    const_iterator                      begin() const{      return (__tree.begin());};
    iterator                            end(){return (__tree.end());}
    const_iterator                      end() const{return (__tree.end());}
    
//     // reverse iterators
    reverse_iterator                    rbegin(){    return (__tree.rbegin());}
    const_reverse_iterator              rbegin() const{      return (__tree.rbegin());};
    reverse_iterator                    rend(){return (__tree.rend());}
    const_reverse_iterator              rend()  const{return (__tree.rend());}

// /* ************************************************************************** */
//                             // Observers= :
// /* ************************************************************************** */

    key_compare                          key_comp() const {    return (key_compare());}
    value_compare                        value_comp() const{        return (value_compare(key_compare()));};

// /* ************************************************************************** */
//                             // Operations= :
// /* ************************************************************************** */

    iterator                             find (const key_type& k) 
    {
        node_ptr ret = __tree.find(k);

         return (ret == nullptr ? iterator (__tree.end()) : iterator (ret));  
    }
    
    const_iterator                       find (const key_type& k) const 
    {   
        node_ptr ret = __tree.find(k);

         return (ret == nullptr ? const_iterator (__tree.end()) : const_iterator (ret));  
    };
    
    size_type                            count (const key_type& k) const {  return (__tree.find(k) != nullptr); }
        
    iterator                             lower_bound (const value_type& v) {  return (__tree.lower_bound (v));    }
    const_iterator                       lower_bound (const value_type& v) const{  return (__tree.lower_bound (v));    };
        
    iterator                             upper_bound (const value_type& v) {  return (__tree.upper_bound(v));}
    const_iterator                       upper_bound (const value_type& v) const{  return (__tree.upper_bound(v));}

    ft::pair<iterator, iterator>             equal_range (const value_type& v) {   
        return (__tree.equal_range(v)); }
        
    ft::pair<const_iterator, const_iterator> equal_range (const value_type& v) const { return (__tree.equal_range(v));
     }

    allocator_type                      get_allocator() const{      return (allocator_type());  };
    
// /* ************************************************************************** */
//                             // Destructor= :
// /* ************************************************************************** */
    ~set(){}

};








template< class Key, class Compare, class Alloc >
bool operator==( const set<Key, Compare, Alloc>& lhs,
                 const set<Key, Compare, Alloc>& rhs )
{
    return (lhs.size() == rhs.size() && ft::equal (lhs.begin(), lhs.end(), rhs.begin()));
}
                 
template< class Key, class Compare, class Alloc >
bool operator!=( const set<Key, Compare, Alloc>& lhs,
                 const set<Key, Compare, Alloc>& rhs )
{
   return (!(lhs == rhs));
}
                 
template< class Key, class Compare, class Alloc >
bool operator<( const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs )
{
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template< class Key, class Compare, class Alloc >
bool operator>=( const set<Key, Compare, Alloc>& lhs,
                 const set<Key, Compare, Alloc>& rhs )
{
   return (!(lhs < rhs));
}
                 

template< class Key, class Compare, class Alloc >
bool operator>( const set<Key, Compare, Alloc>& lhs,
                const set<Key, Compare, Alloc>& rhs )
{
    return (!(lhs < rhs) && lhs != rhs);

}
            
template< class Key, class Compare, class Alloc >
bool operator<=( const set<Key, Compare, Alloc>& lhs,
                 const set<Key, Compare, Alloc>& rhs )
{
   return (!(lhs > rhs));
}


template< class Key, class Compare, class Alloc >
void swap( set<Key, Compare, Alloc>& lhs ,
            set<Key, Compare, Alloc>& rhs)
{
    lhs.swap (rhs);
}
 
}


#endif
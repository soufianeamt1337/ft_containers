/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:05:29 by samajat           #+#    #+#             */
/*   Updated: 2023/01/17 13:25:35 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include "iterator.hpp"

/*/////////////////////////////////////////////////////////////////
                
                    /*ft::vector prototype*/

/////////////////////////////////////////////////////////////////*/

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
    public:
        typedef T                                        value_type;
        typedef Allocator                                allocator_type;
        typedef value_type&                              reference;
        typedef const value_type&                        const_reference;
        typedef value_type*                              pointer;
        typedef const value_type*                        const_pointer;
        typedef size_t                                   size_type;
        
        // typedef typename allocator_type::size_type       allocator_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        /*Iterators*/
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>              iterator;
        typedef typename ft::iterator<ft::random_access_iterator_tag, T>              const_iterator;
        
        
        
        explicit vector (const allocator_type& alloc = allocator_type());
        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
        
        template <class InputIterator>         
        vector (InputIterator first, InputIterator last,    const allocator_type& alloc = allocator_type());
        
        vector (const vector& x);
        ~vector();
        vector& operator= (const vector& x);
        
        //Capacity
        size_type size() const;
        size_type capacity() const;
        size_type max_size() const;
        void      resize(size_type n, value_type val = value_type());
        bool      empty() const;
        void      reserve (size_type n);

        //Function overloading
        reference       operator[] (size_type n);
        const_reference operator[] (size_type n) const;

        //Element access:

        reference               at (size_type n);
        const_reference         at (size_type n) const;
        
        reference               front();
        const_reference         front() const;
        
        reference               back();
        const_reference         back() const;
        
        //Modifiers
        void                    assign (size_type n, const value_type& val);
        template <class InputIterator>  
        void                    assign (InputIterator first, InputIterator last);
        
        void                    push_back (const value_type& val);
        void                    pop_back();

        iterator                insert (iterator position, const value_type& val);
        void                    insert (iterator position, size_type n, const value_type& val);    
        template <class InputIterator>
        void                    insert (iterator position, InputIterator first, InputIterator last);

        iterator                erase (iterator position);
        iterator                erase (iterator first, iterator last);
        
        void                    swap (vector& x);
 
        void                    clear();

        allocator_type          get_allocator() const;

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

    private:
        pointer                 elements;
        size_type               _v_capacity;
        size_type               _v_size;
        allocator_type          allocator;

        //utils
        value_type              *_alloc_double_capacity(size_type    acctual_capacity);
        void                    _copy_elements  (value_type* dst, value_type* src, size_t    n);
    };
        
        




/*/////////////////////////////////////////////////////////////////
                
                    /*ft::vector Implementation*/

/////////////////////////////////////////////////////////////////*/





/*/////////////////////////////////////////////////////////////////*/
//                   /*constructors*/                              //
/*/////////////////////////////////////////////////////////////////*/

template <class T, class Allocator  >
vector <T, Allocator>::vector (const allocator_type& MyAllocator):_v_capacity(0), _v_size(0), allocator(MyAllocator)
{
    this->elements = NULL;
}



template <class T, class Allocator  >
vector <T, Allocator>::vector (size_type n, const value_type& val = value_type(),
    const allocator_type& alloc = allocator_type()):_v_capacity(n), _v_size(n), allocator(MyAllocator)
{
    this->elements = alloc.allocate (n);
    for (size_t i = 0; i < n; i++)
        alloc.construct(this->elements + i, val);
}


template <class T, class Allocator >
template <class InputIterator>
vector <T, Allocator >::vector (InputIterator first, InputIterator last,
    const allocator_type& alloc = allocator_type()):_v_capacity(n), _v_size(n), allocator(MyAllocator)
{
    while (first != last)
    {
        this->push_back(*first);
        first++;
    }
}

template <class T, class Allocator >
vector<T, Allocator>::vector (const vector& x)
{
    this->_v_size = x.size();
    this->_v_capacity = x.size();
    this->elements = alloc.allocate (this->_v_size);
    for (size_t i = 0; i < this->size; i++)
        alloc.construct(this->elements + i, x[i]);
}

template <class T, class Allocator >
vector<T, Allocator>:: ~vector()
{
    if (this->element)
    {
        for (size_t i = 0; i < _v_capacity; i++)
            alloc.destroy(this->elements + i);
        alloc.deallocate(this->elements, _v_capacity);
    }
}


template <class T, class Allocator >
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& x)
{
    
}

/*/////////////////////////////////////////////////////////////////*/
//                   /*Capacity*/                              //
/*/////////////////////////////////////////////////////////////////*/



template <class T, class Allocator >
typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const
{
    return (this->_v_size);
}

template <class T, class Allocator >
typename vector<T, Allocator>::size_type vector<T, Allocator>:: capacity() const
{
    return  (this->_v_capacity);
}

template <class T, class Allocator >
typename vector<T, Allocator>::size_type vector<T, Allocator>::  max_size() const
{
    return (alloc.max_size());
}

// template <class T, class Allocator >
// void vector<T, Allocator>::resize (size_type n, value_type val = value_type())
// {
//     vector temp     (*this);
//     std::allocator<T>  alloc;

//     this->_v_size = n;
//     alloc.destroy(this->elements);
//     alloc.deallocate(this->elements, _v_capacity);
//     this->elements = alloc.allocate(n);
//     for (size_t i = 0; i < this->size(); i++)
//         alloc.construct(this->elements + i, temp[i]);
//     for (size_t i = 0; i < temp.size(); i++)
//         alloc.construct(this->elements + i, val);
// }


template <class T, class Allocator >
bool vector<T, Allocator>::empty() const
{
    return (_v_size == 0);
}

/*If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).

In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.

This function has no effect on the vector size and cannot alter its elements.
*/

template <class T, class Allocator >
void      vector<T, Allocator>::reserve (size_type n)
{
    vector              temp(*this);

    n <= _v_capacity ? return : NULL;
    for (size_t i = 0; i < _v_capacity; i++)        
        alloc.destroy(this->elements + i);
    alloc.deallocate(this->elements, _v_capacity);
    this->elements = alloc.allocate(n);
    for (size_t i = 0; i < temp.size(); i++)
        alloc.construct(this->elements + i, temp[i]);
}




/*/////////////////////////////////////////////////////////////////*/
//                   /*function overloading*/                      //
/*/////////////////////////////////////////////////////////////////*/


template <class T, class Allocator >
typename vector<T, Allocator>::reference       
vector<T, Allocator>::operator[] (size_type i)
{
    if (this->_v_size <= i)
        throw std::out_of_range ();
    return (this->elements[i]);
}

template <class T, class Allocator >
typename vector<T, Allocator>::const_reference 
vector<T, Allocator>::operator[] (size_type i) const
{
    if (this->_v_size <= i)
        throw std::out_of_range ();
    return (this->elements[i]);
}

template <class T, class Allocator >
typename vector<T, Allocator>::reference    
vector<T, Allocator>::at (size_type n)
{
    if (this->_v_size <= i)
        throw std::out_of_range ();
    return (this->elements[i]);
}

template <class T, class Allocator >
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::at (size_type n) const
{
    if (this->_v_size <= i)
        throw std::out_of_range ();
    return (this->elements[i]);
}


// I don't need that these following methods need to be protected as calling them on an empty vector causes an undefined behavior
template <class T, class Allocator >
typename vector<T, Allocator>::reference    
vector<T, Allocator>::front()
{
    return (this->elements[0]);
}

template <class T, class Allocator >
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::front() const
{
    return (this->elements[0]);
}


template <class T, class Allocator >
typename vector<T, Allocator>::reference    
vector<T, Allocator>::back()
{
    return (this->elements[this->size() - 1]);
}

template <class T, class Allocator >
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::back() const
{
    return (this->elements[this->size() - 1]);
}



//Modifiers:

template <class T, class Allocator> 
void vector<T, Allocator>::assign (size_type n, const value_type& val)
{
    this->_v_size = n;
    if (n > this->_v_capacity)
    {
        for (size_t i = 0; i < _v_capacity; i++)        
            alloc.destroy(this->elements + i);
        alloc.deallocate(this->elements, _v_capacity);
        this->elements = alloc.allocate(n);
    }
    for (size_t i = 0; i < n; i++)
        alloc.construct(this->elements + i, val);
}


template <class T, class Allocator> 
template <class InputIterator>
void vector<T, Allocator>::assign (InputIterator first, InputIterator last)
{
    
}


template <class T, class Allocator> 
void vector<T, Allocator>::push_back (const value_type& val)
{
    size_t  new_element_index;

    new_element_index = this->_v_size;
    if (this->_v_capacity == _v_size)
    {
        pointer temp;
        temp = this->_alloc_double_capacity(this->_v_capacity);
        this->_copy_elements(temp, this->elements,this->_v_size);
        if (this->_v_size)
        {
            for (size_t i = 0; i < _v_capacity; i++)        
                alloc.destroy(this->elements + i);
            alloc.deallocate(this->elements, _v_capacity);
        }
        this->elements = temp;
        this->_v_capacity = this->_v_capacity > 0 ? (this->_v_capacity * 2) : 1;
    }
    this->elements[new_element_index] = val;
    this->_v_size++;
}




template <class T, class Allocator> 
void vector<T, Allocator>::pop_back()
{
    alloc.destroy   (this->elements + _v_size - 1);
    this->_v_size--;
}


// template <class T, class Allocator> 
// iterator                insert (iterator position, const value_type& val)
// {
    
// }
// template <class T, class Allocator> 
// void                    insert (iterator position, size_type n, const value_type& val)
// {
    
// }   
//  template <class T, class Allocator> 

// template <class InputIterator>
// void                    insert (iterator position, InputIterator first, InputIterator last)
// {
    
// }


//*-*//



template <class T, class Allocator> 
void vector<T, Allocator>::swap (vector& x)
{
    vector tmp (x);

    x = *this;
    *this = tmp;
}


template <class T, class Allocator> 
void vector<T, Allocator>::clear()
{
    for (size_t i = 0; i < _v_size; i++)
        alloc.destroy(this->elements + i);
    this->_v_size = 0;       
}



template <class T, class Allocator> 
typename vector<T, Allocator>::allocator_type 
vector<T, Allocator>::get_allocator() const
{
    return (alloc);
}





/*/////////////////////////////////////////////////////////////////*/
//                   /*Non-member function overloads*/             //
/*/////////////////////////////////////////////////////////////////*/



template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
    if (equal(lhs.begin()))
}

template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
    
}

template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
    
}

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
    
}

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
    
}

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
    
}


        //*swap*//
template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
{
    vector tmp (x);

    x = y;
    y = tmp;
}




template <class InputIterator1, class InputIterator2>  
bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
    while (first1!=last1)
    {
        if (*first1 != *first2)
            return false;
        ++first1;
        ++first2;
    }
    return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>  
bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
    while (pred(first1, last1))
    {
        if (*first1 != *first2)
            return false;
        ++first1;
        ++first2;
    }
    return true;
}


template <class InputIterator1, class InputIterator2>  
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
    while (first1!=last1)
    {
      if (first2==last2 || *first2<*first1) return false;
      else if (*first1<*first2) return true;
      ++first1; ++first2;
    }
    return (first2!=last2);
}

template <class InputIterator1, class InputIterator2, class Compare>  
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
{
    while (first1!=last1)
    {
      if (first2==last2 || comp (*first2, *first1))
        return false;
      else if (comp (*first1, *first2))
        return true;
      ++first1; ++first2;
    }
    return (first2!=last2);
}



/*/////////////////////////////////////////////////////////////////*/
//                   /*iteraors*/                                  //
/*/////////////////////////////////////////////////////////////////*/


template <class T, class Allocator> 
typename vector<T, Allocator>::iterator       vector<T, Allocator>::begin()
{
    return (this->elements);
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const
{
    return (this->elements);
}

template <class T, class Allocator> 
typename vector<T, Allocator>::iterator       vector<T, Allocator>::end()
{
    return (this->elements + _v_size);
}

template <class T, class Allocator> 
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const
{
    return (this->elements + _v_size);
}




/*/////////////////////////////////////////////////////////////////*/
//                   /*reverse iteraors*/                                  //
/*/////////////////////////////////////////////////////////////////*/
// template <class T, class Allocator> 
// reverse_iterator       rbegin();
// template <class T, class Allocator> 
// const_reverse_iterator rbegin() const

// template <class T, class Allocator> 
// reverse_iterator       rend();
// template <class T, class Allocator> 
// const_reverse_iterator rend() const;


/*/////////////////////////////////////////////////////////////////*/
//                   /*utils*/                                   //
/*/////////////////////////////////////////////////////////////////*/

template <class T, class Allocator> 
vector<T, Allocator>::value_type  
*vector<T, Allocator>::_alloc_double_capacity(size_type    acctual_capacity)
{
    Allocator alloc;
    
    acctual_capacity > 0 ? return (alloc.allocate(acctual_capacity * 2)) : return (alloc.allocate(1));
}

template <class T, class Allocator> 
void vector<T, Allocator>::_copy_elements  (value_type* dst, value_type* src, size_t    n)
{
    Allocator alloc;

    for (size_t i = 0; i < n; i++)
        alloc.construct(dst + i, src + i );
}

}
#endif
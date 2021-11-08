/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterators.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegarr <adegarr@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:46:23 by ade-garr          #+#    #+#             */
/*   Updated: 2021/11/04 17:08:22 by adegarr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATORS_HPP
# define VECTOR_ITERATORS_HPP

# include <iterator>

namespace ft {

	template<class T> class vector_const_iterator;

    template< typename T >
    class vector_iterator {

        public:

        // ----- MEMBER TYPES -----
        typedef std::random_access_iterator_tag	iterator_category;
        typedef T								value_type;
        typedef ptrdiff_t						difference_type;
        typedef value_type*						pointer;
        typedef value_type&						reference;

        // ----- ITERATOR PROPERTIES -----
        vector_iterator(pointer ptr = NULL) : v_it(ptr) {
        };
        vector_iterator(vector_iterator const &cpy) {
            *this = cpy;
        }
        ~vector_iterator() {}
        vector_iterator &operator=(vector_iterator const &rhs) {
            if (*this != rhs)
                v_it = rhs.v_it;
            return (*this);
        }
        friend bool operator==(vector_iterator< T > const &lhs, vector_iterator< T > const &rhs) {
            if (lhs.v_it == rhs.v_it)
                return (true);
            return (false);
        }
        friend bool operator!=(vector_iterator< T > const &lhs, vector_iterator< T > const &rhs) {
            if (lhs.v_it != rhs.v_it)
                return (true);
            return (false);
        }
        reference operator*() const {
            return (*v_it);
        }
        pointer operator->() const {
            return (v_it);
        }
        vector_iterator &operator++() {
            v_it++;
            return (*this);
        }
        vector_iterator operator++(int) {
            vector_iterator tmp = *this;
            v_it++;
            return (tmp);
        }
        vector_iterator &operator--() {
            v_it--;
            return (*this);
        }
        vector_iterator operator--(int) {
            vector_iterator tmp = *this;
            v_it--;
            return (tmp);
        }
        vector_iterator operator+(difference_type n) const {
            return (vector_iterator(v_it + n));
        }
        friend vector_iterator operator+(difference_type n, vector_iterator const &rhs) {
            return (vector_iterator(rhs.v_it + n));
        }
        vector_iterator operator-(difference_type n) const {
            return (vector_iterator(v_it - n));
        }
        difference_type operator-(vector_iterator const &rhs) const {
            return (v_it - rhs.v_it);	
        }
        friend bool operator<(vector_iterator< T > const &lhs, vector_iterator< T > const &rhs) {
            if (lhs.v_it < rhs.v_it)
                return (true);
            return (false);
        }
        friend bool operator>(vector_iterator< T > const &lhs, vector_iterator< T > const &rhs) {
            if (lhs.v_it > rhs.v_it)
                return (true);
            return (false);
        }
        friend bool operator<=(vector_iterator< T > const &lhs, vector_iterator< T > const &rhs) {
            if (lhs.v_it <= rhs.v_it)
                return (true);
            return (false);
        }
        friend bool operator>=(vector_iterator< T > const &lhs, vector_iterator< T > const &rhs) {
            if (lhs.v_it >= rhs.v_it)
                return (true);
            return (false);
        }
        vector_iterator &operator+=(difference_type n) {
            v_it += n;
            return (*this);
        }
        vector_iterator &operator-=(difference_type n) {
            v_it -= n;
            return (*this);
        }
        reference operator[](difference_type n) const {
            return (v_it[n]);
        }
    
        private:

        pointer	v_it;

    };

    template< typename T >
    class vector_const_iterator {

        public:

        // ----- MEMBER TYPES -----
        typedef std::random_access_iterator_tag	iterator_category;
        typedef T								value_type;
        typedef ptrdiff_t						difference_type;
        typedef const value_type*				pointer;
        typedef const value_type&				reference;

        // ----- ITERATOR PROPERTIES -----
        vector_const_iterator(pointer ptr = NULL) : v_it(ptr) {};
        vector_const_iterator(vector_const_iterator const &cpy) {
            *this = cpy;
        }
        vector_const_iterator(vector_iterator<value_type> const &it) : v_it(it.operator->()) {}
        ~vector_const_iterator() {}
        vector_const_iterator &operator=(vector_const_iterator const &rhs) {
            if (*this != rhs)
                v_it = rhs.v_it;
            return (*this);
        }
        friend bool operator==(vector_const_iterator< T > const &lhs, vector_const_iterator< T > const &rhs) {
            if (lhs.v_it == rhs.v_it)
                return (true);
            return (false);
        }
        friend bool operator!=(vector_const_iterator< T > const &lhs, vector_const_iterator< T > const &rhs) {
            if (lhs.v_it != rhs.v_it)
                return (true);
            return (false);
        }
        reference operator*() const {
            return (*v_it);
        }
        pointer operator->() const {
            return (v_it);
        }
        vector_const_iterator &operator++() {
            v_it++;
            return (*this);
        }
        vector_const_iterator operator++(int) {
            vector_const_iterator tmp = *this;
            v_it++;
            return (tmp);
        }
        vector_const_iterator &operator--() {
            v_it--;
            return (*this);
        }
        vector_const_iterator operator--(int) {
            vector_const_iterator tmp = *this;
            v_it--;
            return (tmp);
        }
        vector_const_iterator operator+(difference_type n) const {
            return (vector_const_iterator(v_it + n));
        }
        friend vector_const_iterator operator+(difference_type n, vector_const_iterator const &rhs) {
            return (vector_const_iterator(rhs.v_it + n));
        }
        vector_const_iterator operator-(difference_type n) const {
            return (vector_const_iterator(v_it - n));
        }
        difference_type operator-(vector_const_iterator const &rhs) const {
            return (v_it - rhs.v_it);	
        }
        friend bool operator<(vector_const_iterator< T > const &lhs, vector_const_iterator< T > const &rhs) {
            if (lhs.v_it < rhs.v_it)
                return (true);
            return (false);
        }
        friend bool operator>(vector_const_iterator< T > const &lhs, vector_const_iterator< T > const &rhs) {
            if (lhs.v_it > rhs.v_it)
                return (true);
            return (false);
        }
        friend bool operator<=(vector_const_iterator< T > const &lhs, vector_const_iterator< T > const &rhs) {
            if (lhs.v_it <= rhs.v_it)
                return (true);
            return (false);
        }
        friend bool operator>=(vector_const_iterator< T > const &lhs, vector_const_iterator< T > const &rhs) {
            if (lhs.v_it >= rhs.v_it)
                return (true);
            return (false);
        }
        vector_const_iterator &operator+=(difference_type n) {
            v_it += n;
            return (*this);
        }
        vector_const_iterator &operator-=(difference_type n) {
            v_it -= n;
            return (*this);
        }
        reference operator[](difference_type n) const {
            return (v_it[n]);
        }

        private:

        pointer	v_it;

    };
}

#endif
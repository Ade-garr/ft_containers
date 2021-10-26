/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:55:44 by ade-garr          #+#    #+#             */
/*   Updated: 2021/10/26 18:12:25 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REVERSE_ITERATOR_HPP
# define FT_REVERSE_ITERATOR_HPP

# include "ft_iterator_traits.hpp"

namespace ft {
	
	template<class iterator>
	class reverse_iterator {

        public:

		// ----- MEMBER TYPES -----
		typedef iterator				                                iterator_type;
		typedef typename iterator_traits<iterator>::iterator_category   iterator_category;
		typedef typename iterator_traits<iterator>::value_type	        value_type;
		typedef typename iterator_traits<iterator>::difference_type     difference_type;
		typedef typename iterator_traits<iterator>::pointer	            pointer;
		typedef typename iterator_traits<iterator>::reference	        reference;

		// ----- MEMBER FUNCTIONS -----
		reverse_iterator(pointer ptr = NULL) : m_it(iterator_type(ptr)) {}
		explicit reverse_iterator(iterator_type it) : m_it(--it) {}
		reverse_iterator(const reverse_iterator<iterator>& cpy) : m_it(cpy.m_it) {}	
		iterator_type base() const {
			iterator_type tmp(m_it);
			return (++tmp);
		}
		reference operator*() const {
			return (*m_it);
		}
		reverse_iterator operator+(difference_type n) const {
			reverse_iterator tmp(base().operator-(n));
			return (tmp);
		}
        reverse_iterator& operator++() {
            this->m_it.operator--();
            return (*this);
        }
        reverse_iterator operator++(int) {
            reverse_iterator tmp(*this);
            ++(*this);
            return (tmp);
        }
        reverse_iterator& operator+=(int n) {
            this->m_it.operator-=(n);
            return (*this);
        }
        reverse_iterator operator-(difference_type n) const {
            reverse_iterator tmp(*this);
            tmp.m_it.operator+(n);
            return (tmp);
        }
        reverse_iterator& operator--() {
            this->m_it.operator++();
            return (*this);
        }
        reverse_iterator operator--(int) {
            reverse_iterator tmp(*this);
            --(*this);
            return (tmp);
        }
        reverse_iterator& operator-=(int n) {
            this->m_base.operator+=(n);
            return (*this);
        }
        pointer operator->() const {
            return (&this->operator*());
        }
        reference operator[](size_t n) { 
            return this->m_base.operator[](n);
        }
		
        private:

		iterator_type	m_it;
    };

	template< class Iter >
	typename reverse_iterator<Iter>
    operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) {
		return reverse_iterator<Iter>(it.operator+(n));
	}
    
    template< class Iter >
	typename reverse_iterator<Iter>::difference_type
    operator-( const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs ) {
		return (rhs.base() - lhs.base());
	}

	template< class IterL, class IterR >
	typename reverse_iterator<IterL>::difference_type
    operator-( const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs ) {
		return (IterL(rhs.base()) - lhs.base());
	}

#endif
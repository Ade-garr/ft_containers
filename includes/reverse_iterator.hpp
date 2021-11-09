/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:55:44 by ade-garr          #+#    #+#             */
/*   Updated: 2021/11/10 00:27:29 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "vector_iterators.hpp"

namespace ft {
	
	template<class iterator>
	class reverse_iterator {

		// ----- PUBLIC -----
        public:

		// ----- MEMBER TYPES -----
		typedef iterator				                                iterator_type;
		typedef typename iterator_traits<iterator>::iterator_category   iterator_category;
		typedef typename iterator_traits<iterator>::value_type	        value_type;
		typedef typename iterator_traits<iterator>::difference_type     difference_type;
		typedef typename iterator_traits<iterator>::pointer	            pointer;
		typedef typename iterator_traits<iterator>::reference	        reference;

		// ----- MEMBER FUNCTIONS -----
		reverse_iterator() : b_it() { }
		explicit reverse_iterator(iterator_type it) : b_it(--it) {}
		template< typename U >
		reverse_iterator(reverse_iterator< U > const &cpy) : b_it(cpy.operator->()) {}
		template< typename U >
		reverse_iterator &operator=(reverse_iterator< U > const &rhs ) {
			b_it = rhs.operator->();
			return (*this);
		}
		iterator_type base() const {
			iterator_type tmp(b_it);
			return (++tmp);
		}
		reference operator*() const {
			return (*b_it);
		}
		reverse_iterator operator+(difference_type n) const {
			return (reverse_iterator(base() - n));
		}
        reverse_iterator& operator++() {
            --b_it;
            return (*this);
        }
        reverse_iterator operator++(int) {
            reverse_iterator tmp(*this);
            ++(*this);
            return (tmp);
        }
        reverse_iterator& operator+=(int n) {
            b_it.operator-=(n);
            return (*this);
        }
        reverse_iterator operator-(difference_type n) const {
            return (reverse_iterator(base() + n));
        }
        reverse_iterator& operator--() {
            ++b_it;
            return (*this);
        }
        reverse_iterator operator--(int) {
            reverse_iterator tmp(*this);
            --(*this);
            return (tmp);
        }
        reverse_iterator& operator-=(int n) {
            b_it.operator+=(n);
            return (*this);
        }
        pointer operator->() const {
            return (&this->operator*());
        }
        reference operator[](size_t n) { 
        	return (base()[-n-1]);
        }
		
		// ----- PRIVATE -----
        private:

		iterator_type	b_it;
    };

	// ----- NON MEMBER FUNCTIONS -----

	template< typename Iter >
	reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) {
		return reverse_iterator<Iter>(it.operator+(n));
	}
    
    template< typename Iter >
	typename reverse_iterator<Iter>::difference_type operator-( const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs ) {
		return (rhs.base() - lhs.base());
	}

	template< typename IterL, typename IterR >
	typename reverse_iterator<IterL>::difference_type operator-( const reverse_iterator<IterL>& lhs, const reverse_iterator<IterR>& rhs ) {
		return (IterL(rhs.base()) - lhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() == rhs.base();
	}
	
	template< class Iterator1, class Iterator2 >
	bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() > rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() >= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() <= rhs.base();
	}
}

#endif
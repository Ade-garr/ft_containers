/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:55:44 by ade-garr          #+#    #+#             */
/*   Updated: 2021/10/27 11:56:12 by ade-garr         ###   ########.fr       */
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
		reverse_iterator(pointer ptr = NULL) : b_it(iterator_type(ptr)) {}
		explicit reverse_iterator(iterator_type it) : b_it(--it) {}
		reverse_iterator(const reverse_iterator<iterator>& cpy) : b_it(cpy.b_it) {}	
		iterator_type base() const {
			iterator_type tmp(b_it);
			return (++tmp);
		}
		reference operator*() const {
			return (*b_it);
		}
		reverse_iterator operator+(difference_type n) const {
			reverse_iterator tmp(base().operator-(n));
			return (tmp);
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
            reverse_iterator tmp(*this);
            tmp.b_it.operator+(n);
            return (tmp);
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
            iterator_type it = b_it;
			for (difference_type i = 0; i != -(-n - 1); i++, it--)
				;
			return (*it);
        }
		
        private:

		iterator_type	b_it;
    };

	// ----- NON MEMBER FUNCTIONS -----

	template< typename Iter >
	typename reverse_iterator<Iter>
    operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) {
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

#endif
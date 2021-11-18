/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterators.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:47:11 by ade-garr          #+#    #+#             */
/*   Updated: 2021/11/18 12:45:04 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATORS_HPP
# define MAP_ITERATORS_HPP

# include "map.hpp"

namespace ft {

    template< typename T >
    class map_iterator {

		// ----- PUBLIC -----
        public:

        // ----- MEMBER TYPES -----
        typedef std::bidirectional_iterator_tag	iterator_category;
        typedef T								value_type;
        typedef ptrdiff_t						difference_type;
        typedef value_type*						pointer;
        typedef value_type&						reference;

        // ----- ITERATOR PROPERTIES -----
		map_iterator(NodePtr node = NULL) : ptr(node) {}
		map_iterator(map_iterator const &cpy) {
            *this = cpy;
        }
		~map_iterator() {}
		map_iterator &operator=(map_iterator const &rhs) {
            if (*this != rhs)
				this->ptr = rhs.ptr;
			return (*this);
		}
		friend bool operator==(map_iterator const &lhs, map_iterator const &rhs) {
			return (lhs.ptr == rhs.ptr);
		}
		friend bool operator!=(map_iterator const &lhs, map_iterator const &rhs) {
			return !(lhs._node == rhs._node);
		}

		// ----- PRIVATE -----
		private:

		// ----- MEMBER TYPES -----
		typedef ft::map< ft::T::first_type, ft::T::second_type >::Node* NodePtr;

		NodePtr ptr;
}

#endif

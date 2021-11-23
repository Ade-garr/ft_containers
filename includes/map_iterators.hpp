/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterators.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:47:11 by ade-garr          #+#    #+#             */
/*   Updated: 2021/11/23 01:59:17 by ade-garr         ###   ########.fr       */
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
		map_iterator(node_ptr node = NULL) : ptr(node) {}
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
		reference operator*() const {
			return (ptr->val);
		}
		pointer operator->() const {
			return (&(ptr->val));
		}
		map_iterator& operator++() {
			if (ptr == NULL) {
				return (*this);
			}
			else if (ptr->right != NULL) {
				ptr = ptr->right;
				while (ptr->left != NULL)
					ptr = ptr->left;
			}
			else {
				node_ptr origin = ptr;
				ptr = ptr->parent;
				while (ptr && ptr->right == origin) {
					origin = ptr;
					ptr = ptr->parent;
				}
			}
			return (*this);
		}
		map_iterator operator++(int) {
			map_iterator tmp(*this);
			++(*this);
			return (tmp);
		}
		map_iterator& operator--() {
			if (ptr == NULL) {
				return (*this);
			}
			else if (ptr->left != NULL) {
				ptr = ptr->left;
				while (ptr->right != NULL)
					ptr = ptr->right;
			}
			else {
				node_ptr origin = ptr;
				ptr = ptr->parent;
				while (ptr && ptr->left == origin) {
					origin = ptr;
					ptr = ptr->parent;
				}
			}
			return (*this);
		}
		map_iterator operator--(int) {
			map_iterator tmp(*this);
			--(*this);
			return (tmp);
		}

		// ----- PRIVATE -----
		private:

		// ----- MEMBER TYPES -----
		typedef ft::map< ft::T::first_type, ft::T::second_type >::Node* node_ptr;

		node_ptr ptr;
	};

	template< typename T >
    class map_const_iterator {

		// ----- PUBLIC -----
        public:

        // ----- MEMBER TYPES -----
        typedef std::bidirectional_iterator_tag	iterator_category;
        typedef T								value_type;
        typedef ptrdiff_t						difference_type;
        typedef const value_type*				pointer;
        typedef const value_type&				reference;

        // ----- ITERATOR PROPERTIES -----
		map_const_iterator(node_ptr node = NULL) : ptr(node) {}
		map_const_iterator(map_const_iterator const &cpy) {
            *this = cpy;
        }
		map_const_iterator(map_iterator< value_type > const &it) : ptr(it.operator->()) {}
		~map_const_iterator() {}
		map_const_iterator &operator=(map_const_iterator const &rhs) {
            if (*this != rhs)
				this->ptr = rhs.ptr;
			return (*this);
		}
		friend bool operator==(map_const_iterator const &lhs, map_const_iterator const &rhs) {
			return (lhs.ptr == rhs.ptr);
		}
		friend bool operator!=(map_const_iterator const &lhs, map_const_iterator const &rhs) {
			return !(lhs._node == rhs._node);
		}
		reference operator*() const {
			return (ptr->val);
		}
		pointer operator->() const {
			return (&(ptr->val));
		}
		map_const_iterator& operator++() {
			if (ptr == NULL) {
				return (*this);
			}
			else if (ptr->right != NULL) {
				ptr = ptr->right;
				while (ptr->left != NULL)
					ptr = ptr->left;
			}
			else {
				node_ptr origin = ptr;
				ptr = ptr->parent;
				while (ptr && ptr->right == origin) {
					origin = ptr;
					ptr = ptr->parent;
				}
			}
			return (*this);
		}
		map_const_iterator operator++(int) {
			map_const_iterator tmp(*this);
			++(*this);
			return (tmp);
		}
		map_const_iterator& operator--() {
			if (ptr == NULL) {
				return (*this);
			}
			else if (ptr->left != NULL) {
				ptr = ptr->left;
				while (ptr->right != NULL)
					ptr = ptr->right;
			}
			else {
				node_ptr origin = ptr;
				ptr = ptr->parent;
				while (ptr && ptr->left == origin) {
					origin = ptr;
					ptr = ptr->parent;
				}
			}
			return (*this);
		}
		map_const_iterator operator--(int) {
			map_const_iterator tmp(*this);
			--(*this);
			return (tmp);
		}

		// ----- PRIVATE -----
		private:

		// ----- MEMBER TYPES -----
		typedef ft::map< ft::T::first_type, ft::T::second_type >::Node* node_ptr;

		node_ptr ptr;
	};
}

#endif

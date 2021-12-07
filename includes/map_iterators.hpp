/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterators.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegarr <adegarr@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:47:11 by ade-garr          #+#    #+#             */
/*   Updated: 2021/12/07 19:57:43 by adegarr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATORS_HPP
# define MAP_ITERATORS_HPP

namespace ft {

    template< typename T, typename Node >
    class map_iterator {

		// ----- PRIVATE -----
		private:

		// ----- MEMBER TYPES -----
		typedef Node* node_ptr;

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
            if (this != &rhs)
				this->ptr = rhs.ptr;
			return (*this);
		}
		friend bool operator==(map_iterator const &lhs, map_iterator const &rhs) {
			return (lhs.ptr == rhs.ptr);
		}
		friend bool operator!=(map_iterator const &lhs, map_iterator const &rhs) {
			return !(lhs.ptr == rhs.ptr);
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
		node_ptr getNode() const { return ptr; }

		// ----- PRIVATE -----
		private:

		node_ptr ptr;
	};

	template< typename T, typename Node >
    class map_const_iterator {

		// ----- PRIVATE -----
		private:

		// ----- MEMBER TYPES -----
		typedef Node* node_ptr;

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
		map_const_iterator(map_iterator< value_type, Node > const &it) : ptr(it.getNode()) {}
		~map_const_iterator() {}
		map_const_iterator &operator=(map_const_iterator const &rhs) {
            if (this != &rhs)
				this->ptr = rhs.ptr;
			return (*this);
		}
		friend bool operator==(map_const_iterator const &lhs, map_const_iterator const &rhs) {
			return (lhs.ptr == rhs.ptr);
		}
		friend bool operator!=(map_const_iterator const &lhs, map_const_iterator const &rhs) {
			return !(lhs.ptr == rhs.ptr);
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

		node_ptr ptr;
	};
}

#endif

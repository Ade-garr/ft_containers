/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:02:38 by ade-garr          #+#    #+#             */
/*   Updated: 2021/10/27 19:30:10 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "vector_iterator.hpp"
# include "ft_reverse_iterator.hpp"
# include "ft_iterator_traits.hpp"

namespace ft {

	template< typename T, typename Alloc = std::allocator< T > >
	class vector {

		// ----- MEMBER TYPES -----
		public :
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef allocator_type::reference					reference;
			typedef const allocator_type::const_reference		const_reference;
			typedef allocator_type::pointer						pointer;
			typedef const allocator_type::const_pointer			const_pointer;
			typedef vector_iterator<T>							iterator;
			typedef vector_const_iterator<T>					const_iterator;
			typedef reverse_iterator<iterator>					reverse_iterator;
			typedef reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t										size_type;

		// ----- ITERATORS -----
		class vector_iterator {

			public:

			// ----- MEMBER TYPES -----
			typedef std::random_access_iterator_tag	iterator_category;
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;

			// ----- ITERATOR PROPERTIES -----
			vector_iterator(pointer ptr = NULL) : v_it(ptr) {};
			vector_iterator(vector_iterator const &cpy) {
				*this = cpy;
			}
			~vector_iterator() {}
			vector_iterator &operator=(vector_iterator const &rhs) {
				if (*this != rhs)
					v_it = rhs.v_it;
				return (*this);
			}
			bool operator==(vector_iterator const &rhs) const {
				if (v_it == rhs.v_it)
					return (true);
				return (false);
			}
			bool operator!=(vector_iterator const &rhs) const {
				if (v_it != rhs.v_it)
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
			bool operator<(vector_iterator const &rhs) const {
				if (v_it < rhs.v_it)
					return (true);
				return (false);
			}
			bool operator>(vector_iterator const &rhs) const {
				if (v_it > rhs.v_it)
					return (true);
				return (false);
			}
			bool operator<=(vector_iterator const &rhs) const {
				if (v_it <= rhs.v_it)
					return (true);
				return (false);
			}
			bool operator>=(vector_iterator const &rhs) const {
				if (v_it >= rhs.v_it)
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
			bool operator==(vector_const_iterator const &rhs) const {
				if (v_it == rhs.v_it)
					return (true);
				return (false);
			}
			bool operator!=(vector_const_iterator const &rhs) const {
				if (v_it != rhs.v_it)
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
			friend vector_const_iterator operator+(difference_type n, vector_const_iterator const &rhs) { // a voir si friend a rajouter
				return (vector_const_iterator(rhs.v_it + n));
			}
			vector_const_iterator operator-(difference_type n) const {
				return (vector_const_iterator(v_it - n));
			}
			difference_type operator-(vector_const_iterator const &rhs) const {
				return (v_it - rhs.v_it);	
			}
			bool operator<(vector_const_iterator const &rhs) const {
				if (v_it < rhs.v_it)
					return (true);
				return (false);
			}
			bool operator>(vector_const_iterator const &rhs) const {
				if (v_it > rhs.v_it)
					return (true);
				return (false);
			}
			bool operator<=(vector_const_iterator const &rhs) const {
				if (v_it <= rhs.v_it)
					return (true);
				return (false);
			}
			bool operator>=(vector_const_iterator const &rhs) const {
				if (v_it >= rhs.v_it)
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

		// ----- MEMBER FUNCTIONS -----
		explicit vector (const allocator_type& alloc = allocator_type()): _size(0), _capacity(1), _alloc(alloc) { 
				_head = _alloc.allocate(1);
		}
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _alloc(alloc) {
			_head = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_head[i], val);
		}
		template <class InputIterator>
		vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type()) {
				this->assign(first, last);
		}
		vector(const vector& x) : _size(x._size), _capacity(x._capacity), _alloc(x._alloc) {
			_head = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _capacity; i++)
				_alloc.construct(&_head[i], x._head[i]);
		}
		~vector() {
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_head[i]);
			_alloc.deallocate(_head, _capacity);
		}
		vector& operator=(const vector& x)
		{
			vector copy(x);
			swap(copy);
			return (*this);
		}
		
		private:

			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
			pointer			_head;

	};
}

#endif
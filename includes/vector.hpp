/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegarr <adegarr@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:02:38 by ade-garr          #+#    #+#             */
/*   Updated: 2021/11/04 16:26:36 by adegarr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

# include <memory>
# include "reverse_iterator.hpp"
# include "vector_iterators.hpp"
# include "iterator_traits.hpp"
# include "lexicographical_compare.hpp"
# include "equal.hpp"
# include "enable_if.hpp"

namespace ft {

	template< typename T, typename Alloc = std::allocator< T > >
	class vector {
		
		// ----- PUBLIC -----

		public :

		// ----- MEMBER TYPES -----
		typedef T													value_type;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef vector_iterator<T>									iterator;
		typedef vector_const_iterator<T>							const_iterator;
		typedef reverse_iterator<const_iterator> 					const_reverse_iterator;
		typedef reverse_iterator<iterator> 							reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t												size_type;

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
		vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc) {
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
			if (_capacity != 0)
				_alloc.deallocate(_head, _capacity);
		}
		vector& operator=(const vector& x) {
			vector tmp(x);
			swap(tmp);
			return (*this);
		}

		// ---------- ITERATORS ----------
		iterator	begin() {
			return (iterator(_head));
		}
		const_iterator	begin() const {
			return const_iterator(_head);
		}
		iterator end() {
			return (iterator(_head + _size));
		}
		const_iterator end() const {
			return (const_iterator(_head + _size));
		}
		reverse_iterator rbegin() {
			return (reverse_iterator(_head + _size));
		}
		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(_head + _size));
		}
		reverse_iterator rend()	{
			return (reverse_iterator(_head));
		}
		const_reverse_iterator rend() const {
			return (const_reverse_iterator(_head));
		}
	
		// ---------- CAPACITY ----------
		size_type size() const {
			return (_size);
		}
		size_type max_size() const {
			return (_alloc.max_size());
		}
		void resize (size_type n, value_type val = value_type()) {
			if (n < _size)
				_destroyfrom(n);
			else 
			{
				if (n > _capacity)
					reallocate(std::max(_size * 2, n));
				_fillArray(val, _head + _size, n - _size);
			}
			_size = n;	
		}
		size_type capacity() const {
			return (_capacity);
		}
		bool empty() const {
			
			return (_size == 0);
		}
		void reserve(size_type n) {
			if (n > max_size())
				throw std::length_error("vector::reserve::length_error");
			else if (n > _capacity)
				reallocate(n);
		}

		// ---------- ELEMENT ACCESS ----------
		reference operator[](size_type n) {
			return (_head[n]);
		}
		const_reference operator[](size_type n) const {
			return (_head[n]);
		}
		reference at(size_type n) {
			if (n >= _size)
				throw std::out_of_range("vector::at::out_of_range");
			return (_head[n]);
		}
		const_reference at(size_type n) const {
			if (n >= _size)
				throw std::out_of_range("vector::at::out_of_range");
			return (_head[n]);
		}
		reference front() {
			return(_head[0]);
		}
		const_reference front() const {
			return(_head[0]);
		}
		reference back() {
			return(_head[_size - 1]);
		}
		const_reference back() const {
			return(_head[_size - 1]);
		}

		// ---------- MODIFIERS ----------
		template<class InputIterator>
		void assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
			size_type length = _distance(first, last);
			if (length > _capacity)
				reallocate_raw(length);
			else
				_destroyfrom(0);
			for (int i = 0; first != last; i++, first++)
				_alloc.construct(&_head[i], *first);
			_size = length;
		}
		void assign(size_type n, const value_type& value) {
			if (n > _capacity)
				reallocate_raw(n);
			else
				_destroyfrom(0);
			for (size_type i = 0; i != n; i++)
				_alloc.construct(&_head[i], value);
			_size = n;
		}
		void push_back(const value_type& val) {
			if (_size ==_capacity)
				reallocate(find_new_capacity(_size + 1));
			_alloc.construct(&_head[_size++], val);
		}
		void pop_back() {
			if (_size > 0)
				_alloc.destroy(&_head[--_size]);
		}
		iterator insert(iterator position, const value_type& val) {
			difference_type start = position - begin();
			if (_size == _capacity) {
				reallocate(find_new_capacity(_size + 1));
				position = begin() + start;
			}
			_alloc.construct(this->_head + _size, 0);
			_size++;
			value_type val_bis = *position;
			*position = val;
			for (iterator it = position + 1; it != end(); it++) {
				value_type tmp = *it;
				*it = val_bis;
				val_bis = tmp;
			}
			return (position);
		}
		void insert(iterator position, size_type n, const T& value) {
			difference_type start = position - begin();
			if (n + _size > _capacity) {
				reallocate(find_new_capacity(_size + n));
				position = begin() + start;
			}
			for (size_type i = 0; i < n ; i++) {
				_alloc.construct(this->_head + _size + i, 0);
			}
			_size = _size + n;
			for (size_type i = 0; i < n; i++) {
				right_shift(position);
			}
			for (size_type i = 0; i < n; i++) {
				*(position + i) = value;
			}
		}
		template <class InputIterator>
		void insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
			size_type length = _distance(first, last);
			difference_type start = position - begin();
			if (length + _size > _capacity) {
				reallocate(find_new_capacity(_size + length));
				position = begin() + start;
			}
			for (size_type i = 0; i < length ; i++) {
				_alloc.construct(this->_head + _size + i, 0);
			}
			_size = _size + length;
			iterator it = end() - 1;
			iterator end_swap = position + length;
			for (; it >= end_swap; it--) {
				*it = *(it - length);
			}
			for (size_type i = 0; i < length; i++, first++) {
				*(position + i) = *(first);
			}
		}
		iterator erase(iterator position) {
			return (erase(position, position + 1));
		}
		iterator erase(iterator first, iterator last) {
			for (size_type i = 0; last + i != end(); i++)
				*(first + i) = *(last + i);
			for (difference_type i = 0; i < _distance(first, last); i++) {
				_alloc.destroy(&_head[_size - 1 - i]);
			}
			_size -= _distance(first, last);
			return (first);
		}
		void swap(vector &x) {
			value_type	*tmp;
			size_type	tmp_size;
			size_type	tmp_capacity;
			

			tmp = x._head;
			tmp_size = x._size;
			tmp_capacity = x._capacity;
			x._head = _head;
			x._size = _size;
			x._capacity = _capacity;
			_head = tmp;
			_size = tmp_size;
			_capacity = tmp_capacity;
		}
		void clear() {
			for (size_t i = 0; i < _size; ++i)
				_alloc.destroy(&_head[i]);
			_size = 0;
		}

		// ---------- ALLOCATOR ----------
		allocator_type get_allocator() const {
			return (_alloc);
		}

		// ----- PRIVATE -----

		private:

		void right_shift(iterator position) {
			for (iterator it = end() - 1; it > position; it--) {
				value_type tmp = *it;
				*it = *(it - 1);
				*(it - 1) = tmp;
			}
		}
		size_type find_new_capacity(size_type new_size) {
			size_type	new_capacity = (_capacity > 0 ? _capacity : 1);
			while (new_capacity < new_size)
				new_capacity *= 2;
			return (new_capacity);
		}
		template<class inputIter>
		difference_type _distance(inputIter first, inputIter last) { 
			difference_type n = 0;
			while (first != last) {
				n++;
				first++;
			}
			return (n);
		}
		void _fillArray(value_type val, pointer from, size_t n) {
			for (size_t i = 0; i < n; i++)
				_alloc.construct(&from[i], val);
		}
		void reallocate(size_type n) {
			pointer new_vector = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(&new_vector[i], _head[i]);
				_alloc.destroy(&_head[i]);
			}
			if (_capacity != 0)
				_alloc.deallocate(_head, _capacity);
			_head = new_vector;
			_capacity = n;
		}
		void reallocate_raw(size_type n) {
			pointer new_vector = _alloc.allocate(n);
			_destroyfrom(0);
			if (_capacity != 0)
				_alloc.deallocate(_head, _capacity);
			_capacity = n;
			_head = new_vector;
			_size = 0;
		}
		void	_destroyfrom(size_type begin) {
			for (size_type i = begin; i < _size; i++)
					_alloc.destroy(_head + i);
		}

			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
			pointer			_head;

	};

	// ----- OVERLOADS -----
	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}
	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif
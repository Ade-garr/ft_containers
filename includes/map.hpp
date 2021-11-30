/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegarr <adegarr@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 02:15:57 by ade-garr          #+#    #+#             */
/*   Updated: 2021/11/30 22:33:57 by adegarr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "reverse_iterator.hpp"
# include "map_iterators.hpp"
# include "iterator_traits.hpp"
# include "lexicographical_compare.hpp"
# include "equal.hpp"
# include "pair.hpp"
# include "enable_if.hpp"
# include <functional>

namespace ft {
	template< class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair< const Key, T > > >
	class map {
		struct Node {
			ft::pair<const Key, T>	val;
			Node*	parent;
			Node*	left;
			Node*	right;
			int		height;
		};

		class value_compare {
			// friend class map; // a voir

			public:

			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			bool operator()(const value_type &x, const value_type &y) const {
				return comp(x.first, y.first);
			}

			protected:

			Compare		comp;
			value_compare(Compare c) : comp(c) {}
		};

		// ----- PUBLIC -----
		public:

		// ----- MEMBER TYPES -----
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef ft::pair<const key_type, mapped_type>				value_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef map_iterator<T>										iterator;
		typedef map_const_iterator<T>								const_iterator;
		typedef reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef reverse_iterator<iterator>							reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t												size_type;
		typedef typename Alloc::template rebind<Node>::other		Node_allocator;

		// ----- MEMBER FUNCTIONS -----
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _lastinsert(NULL), _size(0), _comp(comp), _alloc(alloc) {}
		template <class InputIterator>
		map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _lastinsert(NULL), _size(0), _comp(comp), _alloc(alloc) {
			while (first != last)
				this->insert(*first++);
		}
		map(const map& x) : _root(NULL), _lastinsert(NULL), _size(0), _comp(key_compare()), _alloc(allocator_type()) {
			const_iterator ite = x.end();
			for (const_iterator it = x.begin(); it != ite; it++)
				this->insert(*it);
		}
		~map() {
			this->clear();
		}
		map& operator=(const map& x) {
			map tmp(x);
			this->swap(tmp);
			return (*this);
		}

		// ---------- ITERATORS ----------
		iterator begin() {
			return (iterator(this->minValueNode(_root)));
		}
		const_iterator begin() const {
			return (const_iterator(this->minValueNode(_root)));
		}
		iterator end() {
			if (this->empty())
				return (iterator());
			return (iterator((this->maxValueNode(_root))->right, this->maxValueNode(_root)));
		}
		const_iterator end() const {
			if (this->empty())
				return (iterator());
			return (const_iterator((this->maxValueNode(_root))->right, this->maxValueNode(_root)));
		}
		reverse_iterator rbegin() {
			return (reverse_iterator(this->maxValueNode(_root)));
		}
		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(this->maxValueNode(_root)));
		}
		reverse_iterator rend() {
			if (this->empty())
				return (reverse_iterator(_root));
			return (reverse_iterator((this->minValueNode(_root))->left, this->minValueNode(_root)));
		}
		const_reverse_iterator rend() const {
			if (this->empty())
				return (const_reverse_iterator(_root));
			return (const_reverse_iterator((this->minValueNode(_root))->left,
				this->minValueNode(_root)));
		}

		// ---------- CAPACITY ----------
		bool empty() const {
			return (_size == 0);
		}
		size_type size() const {
			return (_size);
		}
		size_type max_size() const {
			return (Node_allocator(_alloc).max_size());
		}

		// ---------- ELEMENT ACCESS ----------
		mapped_type& operator[](const key_type& k) {
			_root = this->tree_insert(_root, NULL, ft::make_pair(k, mapped_type()));
			// _root = tree_balance(_root); // a voir
			Node* element = _lastinsert;
			_lastinsert = NULL;
			return (element->val.second);
		}

		// ---------- MODIFIERS ----------
		pair<iterator,bool> insert(const value_type& val) {
			size_type size_before = this->size();
			_root = this->tree_insert(_root, NULL, val);
			Node* newnode = _lastinsert;
			_lastinsert = NULL;
			return (ft::pair<iterator, bool>(iterator(newnode), (this->size() > size_before)));
		}
		iterator insert(iterator position, const value_type& val) {
			(void) position;
			return (iterator(insert(val).first));
		}
		template <class InputIterator>
		void insert(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
			while (first != last)
				this->insert(*first++);
		}
		void erase(iterator position) {
			_root = this->tree_delete(_root, position->first);
		}
		size_type erase(const key_type& k) {
			size_type tmp = this->size();
			_root = this->tree_delete(_root, k);
			return ((this->size() == tmp) ? 0 : 1);
		}
		void erase(iterator first, iterator last) {
			map tmp(first, last);
			for (reverse_iterator it = tmp.rbegin(); it != tmp.rend(); ++it)
				this->erase(it->first);
		}
		void swap(map& x) {
			Node*	_root_tmp;
			Node*	_lastinsert_tmp;
			size_type	_size_tmp;
			key_compare	_comp_tmp;
			allocator_type	_alloc_tmp;

			_root_tmp = _root;
			_lastinsert_tmp = _lastinsert;
			_size_tmp = _size;
			_comp_tmp = _comp;
			_alloc_tmp = _alloc;
			_root = x._root;
			_lastinsert = x._lastinsert;
			_size = x._size;
			_comp = x._comp;
			_alloc = x._alloc;
			x._root = _root_tmp;
			x._lastinsert = _lastinsert_tmp;
			x._size = _size_tmp;
			x._comp = _comp_tmp;
			x._alloc = _alloc_tmp;
		}
		void clear() {
			_root = this->tree_clear(_root);
		}
		// ---------- OBSERVERS ----------
		key_compare key_comp() const {
			return (_comp);
		}
		value_compare value_comp() const {
			return (value_compare(_comp));
		}
		// ---------- OPERATIONS ----------
		iterator find(const key_type& k) {
			Node* tmp = this->tree_search(_root, k);

			if (tmp)
				return (iterator(tmp));
			return (this->end());
		}
		const_iterator find(const key_type& k) const {
			Node* tmp = this->tree_search(_root, k);

			if (tmp)
				return (const_iterator(tmp));
			return (this->end());
		}
		size_type count(const key_type& k) const {
			Node* tmp = this->tree_search(_root, k);

			if (tmp)
				return (1);
			return (0);
		}
		iterator lower_bound(const key_type& k) {
			iterator lower = this->begin();
			iterator end = this->end();
			while (lower != end && _comp(lower->first, k))
				lower++;
			return (lower);
		}
		const_iterator lower_bound(const key_type& k) const {
			const_iterator lower = this->begin();
			const_iterator end = this->end();
			while (lower != end && _comp(lower->first, k))
				lower++;
			return (lower);
		}
		iterator upper_bound(const key_type& k) {
			iterator upper = this->begin();
			iterator end = this->end();
			while (upper != end && !_comp(k, upper->first))
				upper++;
			return (upper);
		}
		const_iterator upper_bound(const key_type& k) const {
			const_iterator upper = this->begin();
			const_iterator end = this->end();
			while (upper != end && !_comp(k, upper->first))
				upper++;
			return (upper);
		}
		pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
			pair<const_iterator, const_iterator> range;

			range.first = this->lower_bound(k);
			range.second = this->upper_bound(k);
			return (range);
		}
		pair<iterator,iterator> equal_range(const key_type& k) {
			pair<iterator, iterator> range;

			range.first = this->lower_bound(k);
			range.second = this->upper_bound(k);
			return (range);
		}
		// ---------- ALLOCATOR ----------
		allocator_type get_allocator() const {
			return (_alloc);
		}

		// ----- PRIVATE -----
		private:

			Node*	_root;
			Node*	_lastinsert; // a voir
			size_type	_size;
			key_compare	_comp; // a voir
			allocator_type	_alloc;

			int	height(Node* node) const {
				if (node != NULL)
					return (node->height);
				return (0);
			}
			int	getbalance(Node* node) const {
				if (node == NULL)
					return (0);
				return (height(node->left) - height(node->right));
			}
			Node* tree_rr_rotate(Node* node) {
				Node*	new_parent;
				new_parent = node->right;
				new_parent->parent = node->parent;
				node->parent = new_parent;
				node->right = new_parent->left;
				if (new_parent->left)
					new_parent->left->parent = node;
				new_parent->left = node;
				node->height = std::max(height(node->left), height(node->right)) + 1;
				new_parent->height = std::max(height(new_parent->left), height(new_parent->right)) + 1;
				return (new_parent);
			}
			Node*	tree_ll_rotate(Node* node) {
				Node*	new_parent;
				new_parent = node->left;
				new_parent->parent = node->parent;
				node->parent = new_parent;
				node->left = new_parent->right;
				if (new_parent->right)
					new_parent->right->parent = node;
				new_parent->right = node;
				node->height = std::max(height(node->left), height(node->right)) + 1;
				new_parent->height = std::max(height(new_parent->left), height(new_parent->right)) + 1;
				return (new_parent);
			}
			Node*	tree_lr_rotate(Node* node) {
				node->left = this->tree_rr_rotate(node->left);
				return (this->tree_ll_rotate(node));
			}
			Node*	tree_rl_rotate(Node* node) {
				node->right = this->tree_ll_rotate(node->right);
				return (this->tree_rr_rotate(node));
			}
			Node*	tree_balance(Node* node) { // a voir
				int	factor = getbalance(node);
				if (factor > 1) {
					if (getbalance(node->left) > 0)
						return (this->tree_ll_rotate(node));
					else
						return (this->tree_lr_rotate(node));
				}
				else if (factor < -1) {
					if (getbalance(node->right) < 0)						
						return (this->tree_rr_rotate(node));
					else
						return (this->tree_rl_rotate(node));
				}
				return (node);
			}
			Node*	tree_create_node(const value_type& val, Node* parent) {
				Node*	new_node = Node_allocator(_alloc).allocate(1); // a voir
				new_node->right = NULL;
				new_node->left = NULL;
				new_node->height = 1;
				new_node->parent = parent;
				_alloc.construct(&new_node->val, val);
				_size++;
				_lastinsert = new_node;
				return (new_node);
			}
			Node*	tree_insert(Node* node, Node* parent, const value_type& val) {
				if (node == NULL)
					return (tree_create_node(val, parent));
				if (_comp(val.first, node->val.first))
					node->left = tree_insert(node->left, node, val);
				else if (_comp(node->val.first, val.first))
					node->right = tree_insert(node->right, node, val);
				else
					return (_lastinsert = node);
				node->height = 1 + std::max(height(node->left), height(node->right));
				int	factor = getbalance(node);
				if (factor > 1) {
					if (getbalance(node->left) >= 0)
						return (tree_ll_rotate(node));
					else
						return (tree_lr_rotate(node));
				}
				else if (factor < -1) {
					if (getbalance(node->right) <= 0)
						return (tree_rr_rotate(node));
					else
						return (tree_rl_rotate(node));
				}
				return (node);
			}
			Node*	tree_delete(Node* node, const key_type& key) {
				if (node == NULL)
					return (NULL);
				if (_comp(key, node->val.first))
					node->left = tree_delete(node->left, key);
				else if (_comp(node->val.first, key))
					node->right = tree_delete(node->right, key);
				else {
					if ((node->right == NULL) || (node->left == NULL)) {
						Node* tmp = node->right ? node->right : node->left;
						if (tmp == NULL)
							swap(tmp, node);
						else {
							_alloc.destroy(&node->val);
							_alloc.construct(&node->val, tmp->val);
							node->right = node->left = NULL;
						}
						_alloc.destroy(&tmp->val);
						Node_allocator(_alloc).deallocate(tmp, 1);
						_size--;
					}
					else {
						Node* tmp = this->minValueNode(node->right);
						_alloc.destroy(&node->val);
						_alloc.construct(&node->val, tmp->val);
						node->right = tree_delete(node->right, tmp->val.first);
					}
				}
				if (node == NULL)
					return (node);
				int	factor = getbalance(node);
				if (factor > 1) {
					if (getbalance(node->left) >= 0)
						return (tree_ll_rotate(node));
					else
						return (tree_lr_rotate(node));
				}
				else if (factor < -1) {
					if (getbalance(node->right) <= 0)
						return (tree_rr_rotate(node));
					else
						return (tree_rl_rotate(node));
				}
				return (node);
			}
			Node*	tree_clear(Node* node) {
				if (!node)
					return (NULL);
				if (node->left)
					tree_clear(node->left);
				if (node->right)
					tree_clear(node->right);
				_alloc.destroy(&node->val);
				Node_allocator(_alloc).deallocate(node, 1);
				_size--;
				return (NULL);
			}
			Node*	tree_find(Node* node, const key_type& key) const {
				if (node == NULL)
					return (NULL);
				if (!_comp(node->val.first, key) && !_comp(key, node->val.first))
					return (node);
				if (_comp(key, node->val.first))
					return (tree_find(node->left, key));
				else if (_comp(node->val.first, key))
					return (tree_find(node->right, key));
				return (NULL);
			}
			Node*	minValueNode(Node* node) const {
				while (node && node->left != NULL)
					node = node->left;
				return (node);
			}
			Node*	maxValueNode(Node* node) const {
				while (node && node->right != NULL)
					node = node->right;
				return (node);
			}
	};

	// ----- OVERLOADS -----
	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
			rhs.begin(), rhs.end()));
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return !(lhs == rhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return !(rhs < lhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return (rhs < lhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) {
		return !(lhs < rhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) {
		x.swap(y);
	}
}

#endif
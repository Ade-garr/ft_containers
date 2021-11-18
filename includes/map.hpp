/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 02:15:57 by ade-garr          #+#    #+#             */
/*   Updated: 2021/11/18 02:55:52 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "pair.hpp"
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

		public:


		private:

			Node*	_root;
			Node*	_lastinsert;
			size_type	_size;
			key_compare	_comp;
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
			Node*	tree_balance(Node* node) {
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
				Node*	new_node = Node_allocator(_alloc).allocate(1);
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
}

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:48:07 by ade-garr          #+#    #+#             */
/*   Updated: 2021/11/17 15:01:44 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {
	
	template< class T, class Container = ft::vector< T > >
	class stack {

		// ----- PUBLIC -----
		public:
		
		// ----- MEMBER TYPES -----
		typedef T 							value_type;
		typedef Container					container_type;
		typedef size_t						size_type;

		// ----- MEMBER FUNCTIONS -----
		explicit stack(const container_type& ctnr = container_type()) : _ctnr(ctnr) {}
		bool empty() const {
			return (_ctnr.empty());
		}
		size_type size() const {
			return (_ctnr.size());
		}
		value_type& top() {
			return (_ctnr.back());
		}
		const value_type& top() const {
			return (_ctnr.back());
		} 
		void push (const value_type& val) {
			_ctnr.push_back(val);
			return ;
		}
		void pop() {
			_ctnr.pop_back();
			return ;
		}
		friend bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs._ctnr == rhs._ctnr);
		}
		
		friend bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs._ctnr != rhs._ctnr);
		}

		friend bool operator<  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs._ctnr < rhs._ctnr);
		}
		
		friend bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs._ctnr <= rhs._ctnr);
		}
		
		friend bool operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs._ctnr > rhs._ctnr);
		}
		
		friend bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
			return (lhs._ctnr >= rhs._ctnr);
		}

		// ----- PRIVATE -----
		private:

		container_type 	_ctnr;
	};
}

#endif
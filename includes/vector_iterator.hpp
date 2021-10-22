/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:08:48 by ade-garr          #+#    #+#             */
/*   Updated: 2021/10/22 17:51:26 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

namespace ft {

	template< typename T >
	class vector_iterator {

		public:

		// ----- MEMBER TYPES -----
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef value_type*						pointer;
		typedef const value_type&				reference;

		// ----- ITERATOR TRAITS -----
		vector_iterator() : v_it(NULL) {};
		vector_iterator(vector_iterator const &cpy) {
			*this = cpy;
		}
		// a voir si constructeur avec const iterator necessaire
		~vector_iterator() {}
		vector_iterator &operator=(vector_iterator const &rhs) {
			v_it = rhs.v_it;	// a voir si necessaire de rajouter le if *this != rhs
			return (*this);
		}
		bool operator==(vector_iterator const &rhs) {
			if (v_it == rhs.v_it)
				return (true);
			return (false);
		}
		bool operator!=(vector_iterator const &rhs) {
			if (v_it != rhs.v_it)
				return (true);
			return (false);
		}
		reference operator*() {
			return (*v_it);
		}
		reference operator->() {
			return (*v_it);
		}
		vector_iterator &operator++() {
			v_it++;
			return (*this);
		}
		vector_iterator &operator++(int) {
			vector_iterator tmp = *this;
			v_it++;
			return (tmp);
		}
		vector_iterator &operator--() {
			v_it--;
			return (*this);
		}
		vector_iterator &operator--(int) {
			vector_iterator tmp = *this;
			v_it--;
			return (tmp);
		}
		vector_iterator &operator+(vector iterator const &rhs) {
			return (v_it + );
		}

		protected:

		pointer	v_it;

	};
}

#endif
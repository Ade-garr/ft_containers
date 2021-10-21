/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:02:38 by ade-garr          #+#    #+#             */
/*   Updated: 2021/10/21 18:11:14 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "vector_iterator.hpp"

namespace ft {

	template< typename T, typename Alloc = std::allocator< T > >
	class vector {

		// ----- MEMBER TYPES -----
		public :
			typedef T									value_type;
			typedef Alloc								allocator_type;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef value_type*							pointer;
			typedef const value_type*					const_pointer;
			typedef vector_iterator<T>					iterator;
			typedef vector_const_iterator<T>			const_iterator;
			typedef vector_reverse_iterator<T>			reverse_iterator;
			typedef vector_const_reverse_iterator<T>	const_reverse_iterator;
			typedef ptrdiff_t							difference_type;
			typedef size_t								size_type;

		
	};
}

#endif
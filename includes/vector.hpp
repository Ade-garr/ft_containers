/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:02:38 by ade-garr          #+#    #+#             */
/*   Updated: 2021/10/26 17:12:11 by ade-garr         ###   ########.fr       */
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

		
	};
}

#endif
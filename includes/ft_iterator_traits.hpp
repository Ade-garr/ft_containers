/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator_traits.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:08:10 by ade-garr          #+#    #+#             */
/*   Updated: 2021/10/26 17:02:26 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_TRAITS
# define FT_ITERATOR_TRAITS

# include <iterator>
# include <cstddef>

namespace ft {

	template<typename iterator>
    class iterator_traits {
        typedef typename iterator::iterator_category    iterator_category;
        typedef typename iterator::value_type           value_type;
        typedef typename iterator::difference_type      difference_type;
        typedef typename iterator::pointer              pointer;
        typedef typename iterator::reference            reference;
    };

	template<typename T>
    class iterator_traits<T*> {
      typedef std::random_access_iterator_tag   iterator_category;
      typedef T				                    value_type;
      typedef ptrdiff_t						    difference_type;
      typedef T*								pointer;
      typedef T&								reference;
    };

    template<typename T>
    class iterator_traits<const T*> {
      typedef std::random_access_iterator_tag   iterator_category;
      typedef T						            value_type;
      typedef ptrdiff_t							difference_type;
      typedef const T*							pointer;
      typedef const T&							reference;
    };
}

#endif
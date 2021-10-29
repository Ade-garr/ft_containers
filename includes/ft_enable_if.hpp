/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enable_if.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:39:55 by ade-garr          #+#    #+#             */
/*   Updated: 2021/10/29 17:58:59 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{
    template<bool Cond, class T = void>
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T> { typedef T type; };

	template <typename T >
	struct is_integral<T> : public std::integral_constant<T, false> {};

	template<>
	struct is_integral<char> : public std::integral_constant<char, true> {};

	template<>
	struct is_integral<unsigned char> : public std::integral_constant<unsigned char, true> {};

	template<>
	struct is_integral<signed char> : public std::integral_constant<signed char, true> {};

	template<>
	struct is_integral<bool> : public std::integral_constant<bool, true> {};

	template<>
	struct is_integral<unsigned long int> : public std::integral_constant<unsigned long int, true> {};

	template<>
	struct is_integral<long int> : public std::integral_constant<long int, true> {};

	template<>
	struct is_integral<int> : public std::integral_constant<int, true> {};

	template<>
	struct is_integral<short int> : public std::integral_constant<short int, true> {};

	template<>
	struct is_integral<unsigned short int> : public std::integral_constant<unsigned short int, true> {};

	template<>
	struct is_integral<unsigned int> : public std::integral_constant<unsigned int, true> {};

	template<>
	struct is_integral<long long int> : public std::integral_constant<long long int, true> {};

	template<>
	struct is_integral<unsigned long long int> : public std::integral_constant<unsigned long long int, true> {};
}

#endif
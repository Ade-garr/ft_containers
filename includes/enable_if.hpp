/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:00:49 by ade-garr          #+#    #+#             */
/*   Updated: 2021/11/03 14:00:52 by ade-garr         ###   ########.fr       */
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

	template <typename T, bool B>
	struct integral_constant
	{
		typedef T value_type;
		static const bool value = B;
	};

	template <typename T >
	struct is_integral : public integral_constant<T, false> {};

	template<>
	struct is_integral<char> : public integral_constant<char, true> {};

	template<>
	struct is_integral<unsigned char> : public integral_constant<unsigned char, true> {};

	template<>
	struct is_integral<signed char> : public integral_constant<signed char, true> {};

	template<>
	struct is_integral<bool> : public integral_constant<bool, true> {};

	template<>
	struct is_integral<unsigned long int> : public integral_constant<unsigned long int, true> {};

	template<>
	struct is_integral<long int> : public integral_constant<long int, true> {};

	template<>
	struct is_integral<int> : public integral_constant<int, true> {};

	template<>
	struct is_integral<short int> : public integral_constant<short int, true> {};

	template<>
	struct is_integral<unsigned short int> : public integral_constant<unsigned short int, true> {};

	template<>
	struct is_integral<unsigned int> : public integral_constant<unsigned int, true> {};

	template<>
	struct is_integral<long long int> : public integral_constant<long long int, true> {};

	template<>
	struct is_integral<unsigned long long int> : public integral_constant<unsigned long long int, true> {};
}

#endif
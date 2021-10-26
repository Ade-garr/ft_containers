/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 11:51:19 by ade-garr          #+#    #+#             */
/*   Updated: 2021/10/26 16:08:04 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_iterator.hpp"
#include <iostream>
#include <vector>

int main(){

    ft::vector_iterator<int> it;
    // ft::vector_const_iterator<int> it_const;
    
    int a = 1;
    it = &a;
    *it = 2;
    ft::vector_const_iterator<int> it_const(it);

    std::cout << a << std::endl;

    return (0);
}
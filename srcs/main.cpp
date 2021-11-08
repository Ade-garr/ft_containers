/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegarr <adegarr@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 11:51:19 by ade-garr          #+#    #+#             */
/*   Updated: 2021/11/04 14:16:25 by adegarr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <iostream>
#include <vector>

int main(){

    // ft::vector_iterator<int> it;
    // // ft::vector_const_iterator<int> it_const;
    
    // int a = 1;
    // it = &a;
    // *it = 2;
    // ft::vector_const_iterator<int> it_const(it);

    // std::cout << a << std::endl;

    std::vector<int> v(4, 10);
    std::vector<int>::iterator it3;
    std::vector<int>::const_iterator it;
    // std::vector<int>::iterator it2(it3);

    it3 = v.begin();
    it = v.end();
    it--;
    while (it3 != it)
        it3++;
    return (0);
}
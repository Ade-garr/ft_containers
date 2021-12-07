/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_perf.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegarr <adegarr@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:06:18 by adegarr           #+#    #+#             */
/*   Updated: 2021/12/07 13:13:14 by adegarr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <string>
#include "pair.hpp"
#include <stdio.h>
#include <map>
#include <vector>
#include <unistd.h>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "map.hpp"

int main() {

	double diff_mine1;
	double diff_std1;
	double ratio;
	std::time_t begin;
	

	ft::vector<int>		myvec;
	std::vector<int>	stdvec;

	std::vector<int> vec1;
	srand(time(0));
	for (int i = 5000000; i != 0; i--) {
		vec1.push_back(i);
	}


//////////////////////////////////////////////////////////////


	std::cout << "\npush_back 5 000 000 ordered numbers:       ";


    begin = std::time(0);

	for (std::vector<int>::iterator it = vec1.begin(); it != vec1.end(); it++) {
		myvec.push_back(*it);
	}
	diff_mine1 = std::time(0) - begin;

	begin = std::time(0);
	for (std::vector<int>::iterator it = vec1.begin(); it != vec1.end(); it++) {
		stdvec.push_back(*it);
	}
	diff_std1 = std::time(0) - begin;
	ratio = diff_mine1/diff_std1;
	std::cout << "STD is " << ratio << " times faster" << std::endl;


// //////////////////////////////////////////////////////////////

	std::cout << "\nInsert 3 000 000 numbers in the middle:       ";



	for (int i = 3000000; i != 0; i--) {
		vec1.push_back(rand() % 1000000);
	}

	begin = std::time(0);

	
	myvec.insert(myvec.begin() + 2500000, vec1.begin(), vec1.end());
	
	diff_mine1 = std::time(0) - begin;

	myvec.clear();
	begin = std::time(0);
	stdvec.insert(stdvec.begin() + 2500000, vec1.begin(), vec1.end());
	diff_std1 = std::time(0) - begin;

	// ratio = diff_mine1/diff_std1;
	std::cout << "STD is " << ratio << " times faster" << std::endl;


//////////////////////////////////////////////////////////////

	double diff_mine;
	double diff_std;

	ft::map<int, std::string>	mymap;
	std::map<int, std::string>	stdmap;

	std::vector<int> vec;
	srand(time(0));
	for (int i = 1000000; i != 0; i--) {
		vec.push_back(i);
	}


//////////////////////////////////////////////////////////////


	std::cout << "\nInsert 1 000 000 ordered numbers:       ";


    begin = std::time(0);

	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		mymap.insert(ft::pair<int, std::string>(*it, "salut"));
	}
	diff_mine = std::time(0) - begin;

	begin = std::time(0);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		stdmap.insert(std::pair<int, std::string>(*it, "salut"));
	}
	diff_std = std::time(0) - begin;
	ratio = diff_mine/diff_std;
	std::cout << "STD is " << ratio << " times faster" << std::endl;


// //////////////////////////////////////////////////////////////


	vec.clear();
	mymap.clear();
	stdmap.clear();
	for (int i = 1000000; i != 0; i--) {
		vec.push_back(rand() % 1000000);
	}
	std::cout << "\nInsert 1 000 000 random numbers:       ";

	begin = std::time(0);

	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		mymap.insert(ft::pair<int, std::string>(*it, "salut"));
	}
	diff_mine = std::time(0) - begin;

	begin = std::time(0);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		stdmap.insert(std::pair<int, std::string>(*it, "salut"));
	}
	diff_std = std::time(0) - begin;

	ratio = diff_mine/diff_std;
	std::cout << "STD is " << ratio << " times faster" << std::endl;


//////////////////////////////////////////////////////////////


	vec.clear();
	for (int i = 1000000; i != 0; i--) {
		vec.push_back(rand() % 1000000);
	}
	std::cout << "\nFind 1 000 000 random numbers       ";

	begin = std::time(0);

	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		mymap.find(*it);
	}
	diff_mine = std::time(0) - begin;

	begin = std::time(0);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		stdmap.find(*it);
	}
	diff_std = std::time(0) - begin;
	ratio = diff_mine/diff_std;
	std::cout << "STD is " << ratio << " times faster" << std::endl;


////////////////////////////////////////////////////////////////////

	vec.clear();
	for (int i = 1000000; i != 0; i--) {
		vec.push_back(rand() % 1000000);
	}
	std::cout << "\nDeleting 1 000 000 random numbers:      ";

	begin = std::time(0);

	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		mymap.erase(*it);
	}
	diff_mine = std::time(0) - begin;

	begin = std::time(0);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		stdmap.erase(*it);
	}
	diff_std = std::time(0) - begin;
	ratio = diff_mine/diff_std;
	std::cout << "STD is " << ratio << " times faster" << std::endl;



	std::cout <<  "\nWe are emptying all this data\n";
    return (0);
}
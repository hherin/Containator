/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:31:55 by llefranc          #+#    #+#             */
/*   Updated: 2021/02/16 15:51:16 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TESTS_HPP
#define MAP_TESTS_HPP

#include "../includes_and_utils/tester.hpp"

template <typename T>
void	mapTest_Size(T& cont)
{
	std::string name("size:");
	std::cout << "\n---------------------";
	
	printTestName("24", name);	std::cout << cont.size();
}

template <typename T>
void	mapTest_Empty(T& cont)
{
	std::string name("empty:");
	std::cout << "\n---------------------";
	
	printTestName("33", name);	std::cout << cont.empty();
}

template <typename T>
void	mapTest_Iterators(T& cont)
{
	std::string name("iterators:");
	std::cout << "\n---------------------";
	
	printTestName("42", name, "operator++");
	for (typename T::const_iterator it = cont.begin(); it != cont.end(); it++)
		std::cout << "[" << it->first << "][" << it->second << "] | ";

	printTestName("46", name, "++operator");
	for (typename T::const_iterator it = cont.begin(); it != cont.end(); ++it)
		std::cout << "[" << it->first << "][" << it->second << "] | ";

	if (cont.size())
	{
		printTestName("52", name, "operator--");
		for (typename T::const_iterator it = cont.end(); it != cont.begin(); it--)
			if (it != cont.end())
				std::cout << "[" << it->first << "][" << it->second << "] | ";

		printTestName("57", name, "--operator");
		for (typename T::const_iterator it = cont.end(); it != cont.begin(); --it)
			if (it != cont.end())
				std::cout << "[" << it->first << "][" << it->second << "] | ";
	}
}

template <typename T>
void	mapTest_ReverseIterators(T& cont)
{
	std::string name("reverse iterators:");
	std::cout << "\n---------------------";
	
	printTestName("70", name, "++operator");
	for (typename T::const_reverse_iterator it = cont.rbegin(); it != cont.rend(); ++it)
		std::cout << "[" << it->first << "][" << it->second << "] | ";

	printTestName("74", name, "operator++");
	for (typename T::const_reverse_iterator it = cont.rbegin(); it != cont.rend(); it++)
		std::cout << "[" << it->first << "][" << it->second << "] | ";	

	if (cont.size())
	{
		printTestName("80", name, "operator--");
		for (typename T::const_reverse_iterator it = cont.rend(); it != cont.rbegin(); it--)
			if (it != cont.rend())
				std::cout << "[" << it->first << "][" << it->second << "] | ";

		printTestName("85", name, "--operator");
		for (typename T::const_reverse_iterator it = cont.rend(); it != cont.rbegin(); --it)
			if (it != cont.rend())
				std::cout << "[" << it->first << "][" << it->second << "] | ";
	}
}

template <typename T>
void	mapTest_operatorBracelet(T& cont)
{
	std::string name("operator[]:");
	std::cout << "\n---------------------";

	T tmp = cont;
	printTestName("TOREPLACE", name);	std::cout << "size before modif: " << tmp.size();

	printTestName("TOREPLACE", name);
	for (typename T::const_iterator it = cont.begin(); it != cont.end(); ++it)
		std::cout << "[" << cont[it->first] << "] | ";

	T tmp2;
	for (typename T::const_iterator it = cont.begin(); it != cont.end(); ++it)
		tmp2[it->first] = it->second;

	printMapContainer("TOREPLACE", name, tmp);
	printTestName("TOREPLACE", name);	std::cout << "size after operator[]: " << tmp.size();
}

template <typename T>
void	mapTest_Clear(T& cont)
{
	std::string name("clear:");
	std::cout << "\n---------------------";
	
	T tmp = cont;
	printTestName("TOREPLACE", name);	std::cout << "size before clear: " << tmp.size();
	tmp.clear();
	
	printTestName("TOREPLACE", name);	std::cout << "size after clear: " << tmp.size();

	// Allows to value initialize (case size is 0, we can't insert cont.begin())
	typename T::value_type* x = 0;
	if (cont.size())
		x = new typename T::value_type(*(cont.begin()));
	else
		x = new typename T::value_type();

	tmp.insert(*x);
	printMapContainer("TOREPLACE", name, tmp);
	printTestName("TOREPLACE", name);	std::cout << "size after insert: " << tmp.size();

	delete x;
}

template <typename T>
void	mapTest_Swap(T& cont)
{
	std::string name("swap:");
	std::cout << "\n---------------------";
	
	T tmp(cont);
	T tmp2(cont);

	// Allows to value initialize (case size is 0, we can't insert cont.begin())
	typename T::value_type* x = 0;
	if (cont.size())
		x = new typename T::value_type(*(cont.begin()));
	else
		x = new typename T::value_type();

	tmp.insert(*x);
	
	printTestName("136", name);		std::cout << "size of tmp = " << tmp.size() << " and size of tmp2 = " << tmp2.size();
	tmp2.swap(tmp);
	printMapContainer("138", name, tmp2);

	printTestName("140", name);		std::cout << "size of tmp = " << tmp.size() << " and size of tmp2 = " << tmp2.size();

	swap(tmp2, tmp);
	printTestName("143", name);		std::cout << "size of tmp = " << tmp.size() << " and size of tmp2 = " << tmp2.size();
	printMapContainer("144", name, tmp2);

	delete x;
}

/**
*	Inserts an iterators' range of elements.
*/
template <typename T>
void	mapTest_InsertRange(T& cont)
{
	std::string name("insert iterator range:");
	std::cout << "\n---------------------";

	T tmp = cont;
	printTestName("TOREPLACE", name);	std::cout << "size of tmp = " << tmp.size();

	typename T::value_type* x = new typename T::value_type();
	T tmpToInsert;
	tmpToInsert.insert(*x);

	tmp.insert(tmpToInsert.begin(), tmpToInsert.begin());
	
	printTestName("TOREPLACE", name);	std::cout << "size of tmp = " << tmp.size();
	printMapContainer("TOREPLACE", name, tmp);
	
	tmp.insert(tmpToInsert.begin(), tmpToInsert.end());
	
	printTestName("TOREPLACE", name);	std::cout << "size of tmp = " << tmp.size();
	printMapContainer("TOREPLACE", name, tmp);

	tmp.insert(tmp.begin(), tmp.end());
	
	printTestName("TOREPLACE", name);	std::cout << "size of tmp = " << tmp.size();
	printMapContainer("TOREPLACE", name, tmp);

	T tmp2;
	tmp2.insert(tmp.begin(), tmp.end());

	printTestName("TOREPLACE", name);	std::cout << "size of tmp = " << tmp.size();
	printMapContainer("TOREPLACE", name, tmp);

	delete x;
}

/**
*	Inserts one element to a certain position.
*/
template <typename T>
void	mapTest_InsertToAPosition(T& cont)
{
	std::string name("insert 1 elem with a hint for position:");
	std::cout << "\n---------------------";

	T tmp = cont;
	printTestName("TOREPLACE", name);	std::cout << "size of tmp = " << tmp.size();

	typename T::value_type* x = new typename T::value_type();

	tmp.insert(tmp.begin(), *x);

	printTestName("TOREPLACE", name);	std::cout << "size of tmp = " << tmp.size();
	printMapContainer("TOREPLACE", name, tmp);

	if (cont.size())
	{
		T tmp2 = cont;
		tmp2.insert(--tmp2.end(), *x);

		printTestName("TOREPLACE", name);	std::cout << "size of tmp2 = " << tmp2.size();
		printMapContainer("TOREPLACE", name, tmp2);
	}

	if (cont.size() >= 2)
	{
		T tmp3(++cont.begin(), cont.end());
		tmp3.insert(--tmp3.end(), *cont.begin());

		printTestName("TOREPLACE", name);	std::cout << "size of tmp3 = " << tmp3.size();
		printMapContainer("TOREPLACE", name, tmp3);
	}

	delete x;	
}

/**
*	Inserts one element.
*/
template <typename T>
void	mapTest_Insert1Elem(T& cont)
{
	std::string name("insert 1 elem:");
	std::cout << "\n---------------------";

	T tmp = cont;
	printTestName("TOREPLACE", name);	std::cout << "size of tmp = " << tmp.size();

	// Allows to value initialize (case size is 0, we can't insert cont.begin())
	typename T::value_type* x = new typename T::value_type();

	if (cont.size())
	{
		printTestName("TOREPLACE", name);
		std::cout << "return value (testing boolean): " << tmp.insert(*(tmp.begin())).second;

		typename T::value_type pa(tmp.begin()->first, tmp.begin()->second);
		tmp.erase(tmp.begin());
		std::cout << "return value (testing iterator, the mapped content): " << tmp.insert(pa).first->second;
	}

	printTestName("TOREPLACE", name);
	std::cout << "return value (testing iterator, the key): " << (tmp.insert(*x)).first->first;

	printTestName("TOREPLACE", name);	std::cout << "size of tmp = " << tmp.size();
	printMapContainer("TOREPLACE", name, tmp);

	delete x;	
}

#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-05 12:05:13 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-11-05 12:05:13 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base()
{
	std::cout << RED << "=== Base destructor called ===" << RESET <<std::endl;
}


Base* generate(void)
{
	std::srand((unsigned int)std::time(NULL));
	int random = rand() % 3;

	switch (random)
	{
		case 0:
			std::cout << GREEN << "A instance created" << RESET << std::endl;
			return (new A);

		case 1:
			std::cout << GREEN << "B instance created" << RESET << std::endl;
			return (new B);

		case 2:
			std::cout << GREEN << "C instance created" << RESET << std::endl;
			return (new C);
	}
	return (NULL);
}

/**
 * @brief Identifies the type of the object pointed to by the given pointer.
 *
 * This function attempts to identify the type of the object pointed to by the given pointer `p`.
 * It uses `dynamic_cast` to check if `p` can be cast to a pointer of type `A`, `B`, or `C`.
 * If the cast is successful, it prints the corresponding type (`A`, `B`, or `C`).
 * If none of the casts are successful, it prints "Unknown".
 *
 * @param p The pointer to the base class object to be identified.
 */
void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << CYAN << "A" << RESET << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << CYAN << "B" << RESET << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << CYAN << "C" << RESET << std::endl;
	else
		std::cout << PURPLE << "Unknown" << RESET << std::endl;
}

/**
 * @brief Identifies the type of the object referenced by the given reference.
 *
 * This function attempts to identify the type of the object referenced by the given reference `p`.
 * It uses `dynamic_cast` to check if `p` can be cast to a reference of type `A`, `B`, or `C`.
 * If the cast is successful, it prints the corresponding type (`A`, `B`, or `C`).
 * If none of the casts are successful, it prints "Unknown".
 *
 * @param p The reference to the base class object to be identified.
 */
void identify(Base& p)
{
	try
	{
		dynamic_cast<A&>(p);
		std::cout << PURPLE << "A" << RESET << std::endl;
		return;
	} catch (std::exception &e) {}

	try
	{
		dynamic_cast<B&>(p);
		std::cout << PURPLE << "B" << RESET << std::endl;
		return;
	} catch (std::exception &e) {}

	try
	{
		dynamic_cast<C&>(p);
		std::cout << PURPLE << "C" << RESET << std::endl;
		return;
	} catch (std::exception &e) {}

	std::cout << PURPLE << "Unknown" << RESET << std::endl;
}
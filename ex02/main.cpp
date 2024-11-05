/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-05 13:09:02 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-11-05 13:09:02 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

int main()
{
	std::cout << YELLOW << "=== Generating a random instance ===" << RESET << std::endl;
	Base* base = generate();
	std::cout << std::endl;

	std::cout << YELLOW << "=== Identify the type via pointer ===" << RESET << std::endl;
	identify(base);
	std::cout << std::endl;

	std::cout << YELLOW << "=== Identify the type via reference ===" << RESET << std::endl;
	identify(*base);
	std::cout << std::endl;

	delete (base);
}
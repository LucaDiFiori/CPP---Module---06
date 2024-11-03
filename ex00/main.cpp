/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-03 11:13:50 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-11-03 11:13:50 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << RED << "Error: " << RESET << "Invalid number of arguments" << std::endl;
		return (1);
	}
	ScalarConverter::convert((av[1]));
}
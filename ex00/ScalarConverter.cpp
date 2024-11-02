/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-02 09:59:03 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-11-02 09:59:03 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

//------------------------------------------------------------------------------
//                                 CANONICAL
//------------------------------------------------------------------------------
ScalarConverter::ScalarConverter()
{
	std::cout << "Default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter& other) 
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

ScalarConverter::~ScalarConverter()
{
	std::cout << "Destructor called" << std::endl;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	std::cout << "Assignation operator called" << std::endl;
	if (this == &other)
		return *this;

	_input = other._input;
	_type = other._type;
	_char = other._char;
	_int = other._int;
	_float = other._float;
	_double = other._double;

	return (*this);
}


//------------------------------------------------------------------------------
//                                  UTILS
//------------------------------------------------------------------------------
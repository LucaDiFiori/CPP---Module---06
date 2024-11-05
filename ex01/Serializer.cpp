/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-05 09:11:41 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-11-05 09:11:41 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

//------------------------------------------------------------------------------
//                                 CANONICAL
//------------------------------------------------------------------------------

Serializer::Serializer()
{
	std::cout << GREEN << "Serializer constructor called" << RESET << std::endl;
}

Serializer::Serializer(const Serializer& src)
{
	std::cout << GREEN << "Serializer copy constructor called" << RESET << std::endl;
	(void)src;
	*this = src;
}

Serializer::~Serializer()
{
	std::cout << RED << "Serializer destructor called" << RESET << std::endl;
}

Serializer & Serializer::operator=(const Serializer& src)
{
	(void)src;
	std::cout << GREEN << "Serializer assignation operator called" << RESET << std::endl;
	return (*this);
}

//------------------------------------------------------------------------------
//                               PUBLIC METHODS
//------------------------------------------------------------------------------

uintptr_t Serializer::serialize(Data* ptr)
{
    return (reinterpret_cast<uintptr_t>(ptr));
}

Data * Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-05 10:57:16 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-11-05 10:57:16 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

# ifndef COLORS
#  define COLORS
#  define PURPLE "\033[1;35m"
#  define GREEN "\033[1;32m"
#  define CYAN "\033[1;36m"
#  define RED "\033[1;31m"
#  define YELLOW "\033[1;33m"
#  define RESET "\033[0m"
# endif

#include <iostream>
#include <cstdlib>
#include <ctime>

class Base
{
	public:
		virtual ~Base();
};

class A : public Base {};

class B : public Base {};

class C : public Base {};


Base* generate(void);
void identify(Base* p);
void identify(Base& p);

#endif
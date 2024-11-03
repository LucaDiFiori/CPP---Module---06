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

// Static members initialization
std::string ScalarConverter::_input = "";
check ScalarConverter::_check;
char ScalarConverter::_char = '\0';
int ScalarConverter::_int = 0;
float ScalarConverter::_float = 0;
double ScalarConverter::_double = 0;



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
	_check = other._check;
	_char = other._char;
	_int = other._int;
	_float = other._float;
	_double = other._double;

	return (*this);
}


//------------------------------------------------------------------------------
//                                  UTILS
//------------------------------------------------------------------------------
bool ScalarConverter::isInfNan(std::string& input)
{
	if (input == "nan" || input == "+nan" || input == "-nan" 
		|| input == "inf" || input == "-inf" || input == "+inf" 
		|| input == "inff" || input == "-inff" || input == "+inff")
		return (true);

	return (false);
}

bool ScalarConverter::isValid(std::string& input)
{
    int dotCount = 0;
    bool hasDigit = false;
    bool hasDigitAfterDot = false;
    size_t len = input.length();
    
    // Check if input is inf or nan
    if (isInfNan(input)) {
        ScalarConverter::_check = VALID;
        ScalarConverter::_input = input;
        return true;
    }

    // Check if input is a single character
    if (len == 1 && (isalpha(input[0]) || isdigit(input[0]))) {
        ScalarConverter::_check = VALID;
        ScalarConverter::_input = input;
        return true;
    }

    // Check if input is a valid number (optional sign, decimal, and 'f' suffix for floats)
    size_t start = (input[0] == '+' || input[0] == '-') ? 1 : 0;

    for (size_t i = start; i < len; i++) 
	{
        if (input[i] == '.') 
		{
            dotCount++;
            if (dotCount > 1) return false;  // Only one dot is allowed
        } 
        else if (isdigit(input[i])) 
		{
            hasDigit = true;
            if (dotCount > 0) 
				hasDigitAfterDot = true;  // Set flag for digit after dot
        } 
        else if (input[i] == 'f' && i == len - 1) 
		{
            // 'f' suffix is valid only if it's the last character
            continue;
        } 
        else
            return (false);  // Invalid character
    }

    // Final validation check
    if (!hasDigit || (dotCount == 1 && !hasDigitAfterDot)) 
		return false;

    ScalarConverter::_check = VALID;
    ScalarConverter::_input = input;
    return true;
}



///////////////////////////////////////////////////////////////////////////////
void ScalarConverter::convert(std::string input)
{
	if (ScalarConverter::isValid(input))
		std::cout << "Valid input" << std::endl;
	else
		std::cout << "Invalid input" << std::endl;
}
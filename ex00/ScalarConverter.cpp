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
check ScalarConverter::_type;
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

//___________________________________________________________________check_utils
bool ScalarConverter::isInfNan(std::string& input)
{
	if (input == "nan" || input == "+nan" || input == "-nan" 
        || input == "nanf" || input == "+nanf" || input == "-nanf")
	{
		ScalarConverter::_type = NAN_CONVERSION;
		return (true);
	}
	if (input == "inf" || input == "+inf" || input == "-inf" 
			 || input == "inff" || input == "+inff" || input == "-inff")
	{
		ScalarConverter::_type = INF_CONVERSION;
		return (true);
	}
	return (false);
}

bool ScalarConverter::isValid(std::string& input)
{
    int dotCount = 0;
    bool hasDigit = false;
    bool hasDigitAfterDot = false;
    size_t len = input.length();
    
    // Check if input is inf or nan
    if (isInfNan(input)) 
	{
        ScalarConverter::_input = input;
        return (true);
    }

    // Check if input is a single character
    if (len == 1 && (isalpha(input[0]) || isdigit(input[0]))) 
	{
		ScalarConverter::_type = BASIC_CONVERSION;
        ScalarConverter::_input = input;
        return (true);
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
		return (false);

	ScalarConverter::_type = BASIC_CONVERSION;
    ScalarConverter::_input = input;
    return (true);
}


//_________________________________________________________________convert_utils
void ScalarConverter::toChar()
{
	//if (ScalarConverter::_type == INFNAN_DOUBLE || ScalarConverter::_type == INFNAN_FLOAT)
	//{
	//	std::cout << YELLOW << "char: " << RED << "Impossible" << RESET << std::endl;
	//	return;
	//}

	long long intValue = std::stoll(ScalarConverter::_input);

	if (intValue >= 32 && intValue <= 126)
	{
		ScalarConverter::_char = static_cast<char>(intValue);
		ScalarConverter::printChar(true);
	}
	else
		ScalarConverter::printChar(false);

}

void ScalarConverter::toInt()
{

	//if (ScalarConverter::_type == INFNAN_DOUBLE || ScalarConverter::_type == INFNAN_FLOAT)
	//{
	//	std::cout << PURPLE << "int: " << RED << "Impossible" << RESET << std::endl;
	//	return;
	//}

	long long intValue = std::stoll(ScalarConverter::_input);

	if (intValue >= 2147483647  && intValue <= -2147483648)
	{
		ScalarConverter::_int = intValue;
		ScalarConverter::printInt(true);
	}
	else
		ScalarConverter::printInt(false);
}





//CONTROLLARLE --> misa che sono sbagliati 
/*
	Note: In the if statement, I check if the input is one of the special values 
	      (regardless of whether it's float or double) because:
		- If the input is "nan", "inf", "-inf", or "+inf", I need to convert it 
		  to the corresponding float value using nanf() or infinity().
		- If the input is already a special float value (like "nanf" or "inff"), 
		  I need to convert it from a string to the actual float representation.

	Note: In C++, the functions std::numeric_limits<float>::quiet_NaN() 
	      and std::numeric_limits<double>::quiet_NaN() generate a special 
		  floating-point value called NaN (Not-a-Number) in its "quiet" form 
		  (i.e., without signaling an exception).
*/
void ScalarConverter::toFloatInfNan() 
{
    if (ScalarConverter::_type == NAN_CONVERSION) 
    {
        ScalarConverter::_float = std::numeric_limits<float>::quiet_NaN();
    } 
    else if (ScalarConverter::_type == INF_CONVERSION) 
    {
        if (_input[0] == '-')
            ScalarConverter::_float = -std::numeric_limits<float>::infinity();
        else
            ScalarConverter::_float = std::numeric_limits<float>::infinity();
    }
	std::cout << "float: " << _float << "f" << std::endl;
}


void ScalarConverter::toDoubleInfNan() 
{
    if (ScalarConverter::_type == NAN_CONVERSION) 
	{
        ScalarConverter::_double = std::numeric_limits<double>::quiet_NaN();
	}
    else if (ScalarConverter::_type == INF_CONVERSION) 
	{
        if (_input[0] == '-')
            ScalarConverter::_double = -std::numeric_limits<double>::infinity();
        else
            ScalarConverter::_double = std::numeric_limits<double>::infinity();
	}
    std::cout << "double: " << _double << std::endl;
}








//MANCAQUESTOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
/*void ScalarConverter::toFloat() 
{


	else 
		{

            float floatValue = std::stof(_input);
            if (floatValue >= std::numeric_limits<float>::min() && floatValue <= std::numeric_limits<float>::max()) {
                _float = floatValue;
                std::cout << "float: " << std::fixed << std::setprecision(1) << _float << "f" << std::endl;
            } else {
                std::cout << "float: Impossible" << std::endl;
            }
        } 
    }
*/

//___________________________________________________________________print_utils
void ScalarConverter::printChar(bool isPrintable)
{
	if (isPrintable == true)
		std::cout << YELLOW << "char: '" << RESET << ScalarConverter::_char << "'" << std::endl;
	else
		std::cout << YELLOW << "char: " << RED << "Impossible" << RESET << std::endl;

}

void ScalarConverter::printInt(bool isPrintable)
{
	if (isPrintable == true)
		std::cout << PURPLE << "int: " << RESET << ScalarConverter::_int << std::endl;
	else
	    std::cout << PURPLE << "int: " << RED << "Impossible" << RESET << std::endl;
}

void ScalarConverter::printFloat(bool isPrintable)
{
	if (isPrintable == true)
		std::cout << CYAN << "float: " << RESET << std::fixed << std::setprecision(1) 
		<< ScalarConverter::_float << "f" << std::endl;
	else
		std::cout << CYAN << "float: " << RED << "Impossible" << RESET << std::endl;
}

void ScalarConverter::printDouble(bool isPrintable)
{
	if (isPrintable == true)
		std::cout << GREEN << "double: " << RESET << std::fixed << std::setprecision(1) 
		<< ScalarConverter::_double << std::endl;
	else
		std::cout << GREEN << "double: " << RED << "Impossible" << RESET << std::endl;
}






//------------------------------------------------------------------------------
//                               PUBLIC METHODS
//------------------------------------------------------------------------------
/*
   Note: static_cast is the primary cast type you’ll use for int, float, double, 
         and char conversions in this exercise. It’s safe, well-defined, and works 
		 at compile time, making it ideal for numeric and character conversions.
*/
void ScalarConverter::convert(std::string input)
{
	if (!ScalarConverter::isValid(input))
	{
		std::cout << RED << "Invalid input" << RESET << std::endl;
		return;
	}
	
	switch(ScalarConverter::_type)
	{
		case (BASIC_CONVERSION):
			ScalarConverter::toChar();
			ScalarConverter::toInt();
			ScalarConverter::toFloat();
			ScalarConverter::toDouble();
			break;
		case (INF_CONVERSION || NAN_CONVERSION):
			ScalarConverter::printChar(false);
			ScalarConverter::printInt(false);
			ScalarConverter::toFloatInfNan();
			ScalarConverter::toDoubleInfNan();
			break;
	}


}


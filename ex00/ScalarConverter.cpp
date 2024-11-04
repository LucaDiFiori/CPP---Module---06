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

#include <cstdio> //DA TOGLIERE

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
/**
 * @brief Checks if the input string represents a special floating-point value (NaN or infinity).
 *
 * This method determines if the given input string corresponds to a special floating-point value
 * such as NaN (Not a Number) or infinity (positive or negative). If the input matches one of these
 * special values, it sets the appropriate type (`NAN_CONVERSION` or `INF_CONVERSION`) and stores
 * the input string in the class variables.
 *
 * @param input The input string to be checked.
 * @return true if the input represents NaN or infinity, false otherwise.
 */
bool ScalarConverter::isInfNan(std::string& input)
{
	if (input == "nan" || input == "+nan" || input == "-nan" 
        || input == "nanf" || input == "+nanf" || input == "-nanf")
	{
		ScalarConverter::_type = NAN_CONVERSION;
		ScalarConverter::_input = input;
		return (true);
	}
	if (input == "inf" || input == "+inf" || input == "-inf" 
			 || input == "inff" || input == "+inff" || input == "-inff")
	{
		ScalarConverter::_type = INF_CONVERSION;
		ScalarConverter::_input = input;
		return (true);
	}
	return (false);
}

/**
 * @brief Checks if the input string is a single printable character.
 *
 * This method determines if the given input string consists of a single printable character.
 * If the character is a digit, it sets the type to `BASIC_CONVERSION`, 
 * otherwise it sets the type to `CHAR`.
 * The input string is stored in the class variables.
 *
 * @param input The input string to be checked.
 * @return true if the input is a single printable character, false otherwise.
 */
bool ScalarConverter::isSingleCharacter(std::string& input)
{
    if (input.length() == 1) 
    {
        char ch = input[0];
        if (std::isprint(ch)) 
        {
            ScalarConverter::_type = std::isdigit(ch) ? BASIC_CONVERSION : CHAR;
            ScalarConverter::_input = input;
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks if the input string is a valid number.
 *
 * This method determines if the given input string represents a valid number. 
 * It supports optional sign characters ('+' or '-'), decimal points, and an 'f' suffix for floats.
 * If the input is a valid number, it sets the type to `BASIC_CONVERSION` and stores the input string 
 * in the class variables.
 *
 * @param input The input string to be checked.
 * @return true if the input is a valid number, false otherwise.
 */
bool ScalarConverter::isValidNumber(std::string& input)
{
    bool hasDigit = false;
    bool hasDot = false;
    size_t len = input.length();
    

    size_t start = (input[0] == '+' || input[0] == '-') ? 1 : 0;

    for (size_t i = start; i < len; i++) 
    {
        if (input[i] == '.') 
        {
            if (hasDot) 
                return (false);  // Only one decimal point is allowed
            if (i + 1 >= len || !std::isdigit(input[i + 1]))
                return (false);  // Must have a digit after the decimal point
            hasDot = true;
        } 
        else if (std::isdigit(input[i])) 
        {
            hasDigit = true;
        } 
        else if (input[i] == 'f' && i == len - 1) 
        {
            ScalarConverter::_type = BASIC_CONVERSION;
            ScalarConverter::_input = input;
            return hasDigit;
        } 
        else 
            return (false);  // Invalid character found
    }

    if (hasDigit) 
    {
        ScalarConverter::_type = BASIC_CONVERSION;
        ScalarConverter::_input = input;
        return (true);
    }
    return (false);
}


bool ScalarConverter::checkInput(std::string& input)
{
    if (isInfNan(input)) 
        return (true);

    if (isSingleCharacter(input)) 
        return (true);

    if (isValidNumber(input)) 
        return (true);

    return (false);
}


//_________________________________________________________________convert_utils
/**
 * @brief Converts the input double value to a char.
 *
 * This method converts the given double value to a char. If the double value is within the 
 * printable ASCII range (32-126), it is converted to a char and stored in the class variables.
 * The converted char is then printed to the standard output.
 *
 * @param input_double The double value to be converted to a char.
 */
void ScalarConverter::toChar(double input_double)
{
	if (input_double >= 32 && input_double <= 126)
	{
		ScalarConverter::_char = static_cast<char>(input_double);
		ScalarConverter::printChar(true);
	}
	else
		ScalarConverter::printChar(false);
}

/**
 * @brief Converts the input double value to an int.
 *
 * This method converts the given double value to an int. If the double value is within the 
 * range of an int, it is converted to an int and stored in the class variables.
 * The converted int is then printed to the standard output.
 *
 * @param input_double The double value to be converted to an int.
 */
void ScalarConverter::toInt(double input_double)
{
	if (input_double >= std::numeric_limits<int>::min() 
		&& input_double <= std::numeric_limits<int>::max())
	{
		ScalarConverter::_int = static_cast<int>(input_double);
		ScalarConverter::printInt(true);
	}
	else
		ScalarConverter::printInt(false);
}

/**
 * @brief Converts the input double value to a float.
 *
 * This method converts the given double value to a float. If the double value is within the 
 * range of a float, it is converted to a float and stored in the class variables.
 * The converted float is then printed to the standard output.
 *
 * @param input_double The double value to be converted to a float.
 */
void ScalarConverter::toFloat(double input_double) 
{
	if (input_double >= -std::numeric_limits<float>::max() 
		&& input_double <= std::numeric_limits<float>::max())
	{
		ScalarConverter::_float = static_cast<float>(input_double);
		ScalarConverter::printFloat(true);
	}
	else
		ScalarConverter::printFloat(false);
} 

/**
 * @brief Converts the input double value to a double.
 *
 * This method converts the given double value to a double. If the double value is within the 
 * range of a double, it is stored in the class variables.
 * The converted double is then printed to the standard output.
 *
 * @param input_double The double value to be converted to a double.
 */
void ScalarConverter::toDouble(double input_double) 
{
	if (input_double >= -std::numeric_limits<double>::max() 
		&& input_double <= std::numeric_limits<double>::max())
	{
		ScalarConverter::_double = input_double;
		ScalarConverter::printDouble(true);
	}
	else
		ScalarConverter::printDouble(false);
}


/**
 * @brief Converts the input to a special floating-point value (NaN or infinity) for float type.
 *
 * This method converts the input to a special floating-point value such as NaN (Not a Number) 
 * or infinity (positive or negative) for the float type. If the input type is `NAN_CONVERSION`, 
 * it sets the float value to NaN. If the input type is `INF_CONVERSION`, it sets the float value 
 * to positive or negative infinity based on the input string.
 *
 * Note: In the if statement, I check if the input is one of the special values 
 *       (regardless of whether it's float or double) because:
 *       - If the input is "nan", "inf", "-inf", or "+inf", I need to convert it 
 *         to the corresponding float value using nanf() or infinity().
 *       - If the input is already a special float value (like "nanf" or "inff"), 
 *         I need to convert it from a string to the actual float representation.
 *
 * Note: In C++, the functions std::numeric_limits<float>::quiet_NaN() 
 *       and std::numeric_limits<double>::quiet_NaN() generate a special 
 *       floating-point value called NaN (Not-a-Number) in its "quiet" form 
 *       (i.e., without signaling an exception).
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
	std::cout << CYAN << "float: " << RESET << _float << "f" << std::endl;
}

// Convert the input to an infinite or a NaN double value
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
    std::cout << GREEN << "double: " << RESET << _double << std::endl;
}



//___________________________________________________________________print_utils
void ScalarConverter::printChar(bool isPrintable)
{
	if (isPrintable == true)
	{
		if (ScalarConverter::_type == CHAR)
			std::cout << YELLOW << "char: '" << RESET << ScalarConverter::_input[0] 
				<< "'"  << std::endl;
		else
			std::cout << YELLOW << "char: '" << RESET << ScalarConverter::_char 
				<< "'" << std::endl;
	}
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
/**
 * @brief Converts the input string to various scalar types (char, int, float, double).
 *
 * This method converts the input string to different scalar types based on the determined type.
 * It first checks if the input is valid using `checkInput`. If the input is invalid, it prints an error message.
 * If the input is valid, it converts the input string to a double and then performs the appropriate conversions
 * based on the type (`CHAR`, `BASIC_CONVERSION`, `INF_CONVERSION`, or `NAN_CONVERSION`).
 *
 * Note: static_cast is the primary cast type you’ll use for int, float, double, 
 *       and char conversions in this exercise. It’s safe, well-defined, and works 
 *       at compile time, making it ideal for numeric and character conversions.
 * 
 * Note: The variable input_double is used to store the converted input.
*       A double is chosen here, but you could use long or another large type.
*       I just need a big value to store the input, and ultimately I have to
*       convert it to double anyway.
 *
 * @param input The input string to be converted.
 */
void ScalarConverter::convert(std::string input)
{
	if (!ScalarConverter::checkInput(input))
	{
		std::cout << RED << "Invalid input" << RESET << std::endl;
		return;
	}


	double input_double = atof(ScalarConverter::_input.c_str());
	
	switch(ScalarConverter::_type)
	{
		case (CHAR): 
			ScalarConverter::printChar(true);
			ScalarConverter::_int = static_cast<int>(ScalarConverter::_input[0]);
			ScalarConverter::_float = static_cast<float>(ScalarConverter::_input[0]);
			ScalarConverter::_double = static_cast<double>(ScalarConverter::_input[0]);
			ScalarConverter::printInt(true);
			ScalarConverter::printFloat(true);
			ScalarConverter::printDouble(true);
			break;
		case (BASIC_CONVERSION):
			ScalarConverter::toChar(input_double);
			ScalarConverter::toInt(input_double);
			ScalarConverter::toFloat(input_double);
			ScalarConverter::toDouble(input_double);
			break;
		case (INF_CONVERSION):
		case (NAN_CONVERSION):
			ScalarConverter::printChar(false);
			ScalarConverter::printInt(false);
			ScalarConverter::toFloatInfNan();
			ScalarConverter::toDoubleInfNan();
			break;
	}

}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-02 09:06:22 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-11-02 09:06:22 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# ifndef COLORS
#  define COLORS
#  define PURPLE "\033[1;35m"
#  define GREEN "\033[1;32m"
#  define CYAN "\033[1;36m"
#  define RED "\033[1;31m"
#  define RESET "\033[0m"
# endif

# include <iostream>
# include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <cmath> // Per std::isinf e std::isnan

// Enum for the type of the input (used in the switch case)
enum check
{
	INFNAN,
	VALID
};

class ScalarConverter
{
	private:
		//----------------------------------------------------------------------
		//                               MEMBERS
		//----------------------------------------------------------------------
		//input: the input string to convert
		static std::string _input;
		//type: the type of the input used for the switch case
		static check _check;
		//char: the char value of the input used for the conversion
		static char _char;
		//int: the int value of the input used for the conversion
		static int _int;
		//float: the float value of the input used for the conversion
		static float _float;
		//double: the double value of the input used for the conversion
		static double _double;

		//----------------------------------------------------------------------
		//                               UTILS
		//----------------------------------------------------------------------
		// Check if the input is an infinite or a NaN
		static bool isInfNan(std::string& input); //--> se lo trovo setto _check a INFNAN
		// Check if the input is a valid type
		static bool isValid(std::string& input);  //-->qui controllo se il tipo è valido, se lo è inizializzo _input cosi che tutti gli altri possano prenderlo da li
		//chiamo isInfnNan e nel caso esco, controllo se c'è piu di una lettera, se c'è una lettera sola controllare che sia o singola o una f alla fine, se c'è un punto e se c'è un segno (e ne tengo il conto), 



		// Convert the input to a char
		//static void toChar();
		// Convert the input to an int
		//static void toInt();             //--> Questi fanno eseguono controlli (es per gli int se è un nan o un inf o se è fuori range) e verranno chiamati tutti
		// Convert the input to a float
		//static void toFloat();
		// Convert the input to a double
		//static void toDouble();
		
		// Print the char
		//static void printChar();
		// Print the int
		//static void printInt();
		// Print the float             //--> forse questi non servono
		//static void printFloat();
		// Print the double
		//static void printDouble();
		/* sarebbero cose del genere
			void ScalarConverter::printInt(int value) {
    		std::cout << "int: " << value << std::endl;
			}

			void ScalarConverter::printFloat(float value) {
    		std::cout << "float: " << std::fixed << std::setprecision(1) << value << "f" << std::endl;
			}
		*/


	//--------------------------------------------------------------------------
	//                             CANONICAL
	//--------------------------------------------------------------------------
	public:
		// CAnonical
		ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		~ScalarConverter();
		ScalarConverter &operator=(const ScalarConverter &other);

	//--------------------------------------------------------------------------
	//                           PUBLIC METHODS
	//--------------------------------------------------------------------------
		// Convert the input to the right type
		static void convert(std::string input);
		// Print the result
		//static void print();
};

#endif



/*
#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <cmath> // Per std::isinf e std::isnan

void ScalarConverter::toChar(const std::string& input) {
    try {
        int value = std::stoi(input);
        if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max()) {
            throw std::out_of_range("Value out of char range");
        }
        char c = static_cast<char>(value);
        std::cout << "char: '" << c << "'" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "char: impossible" << std::endl;
    }
}

void ScalarConverter::toInt(const std::string& input) {
    try {
        if (input == "inf" || input == "+inf" || input == "-inf" || input == "nan") {
            throw std::invalid_argument("Special floating-point value");
        }
        int value = std::stoi(input);
        std::cout << "int: " << value << std::endl;
    } catch (const std::exception& e) {
        std::cout << "int: impossible" << std::endl;
    }
}

void ScalarConverter::toFloat(const std::string& input) {
    try {
        float value = std::stof(input);
        if (std::isinf(value)) {
            std::cout << "float: " << (value > 0 ? "+inf" : "-inf") << "f" << std::endl;
        } else if (std::isnan(value)) {
            std::cout << "float: nanf" << std::endl;
        } else {
            std::cout << "float: " << std::fixed << std::setprecision(1) << value << "f" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "float: impossible" << std::endl;
    }
}

void ScalarConverter::toDouble(const std::string& input) {
    try {
        double value = std::stod(input);
        if (std::isinf(value)) {
            std::cout << "double: " << (value > 0 ? "+inf" : "-inf") << std::endl;
        } else if (std::isnan(value)) {
            std::cout << "double: nan" << std::endl;
        } else {
            std::cout << "double: " << value << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "double: impossible" << std::endl;
    }
}
*/
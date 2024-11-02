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
# include <limits>

// Enum for the type of the input (used in the switch case)
enum type
{
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	INVALID
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
		static type _type;
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
		// Check if the input is a valid type
		static bool isValid(std::string input);  //-->qui controllo se il tipo è valido, se lo è inizializzo _input cosi che tutti gli altri possano prenderlo da li

		// Check if the input is a valid char
		static bool _isChar();
		// Check if the input is a valid int
		static bool isInt();
		// Check if the input is a valid float
		static bool isFloat();
		// Check if the input is a valid double
		static bool isDouble();
		// Get the type of the input
		static type getType();            //-->qui gestisco anche i casi degli infiniti e dei nan


		// Convert the input to a char
		static void toChar();
		// Convert the input to an int
		static void toInt();             //-->QUESTI li uso nello switch case
		// Convert the input to a float
		static void toFloat();
		// Convert the input to a double
		static void toDouble();
		
		// Print the char
		static void printChar();
		// Print the int
		static void printInt();
		// Print the float             //--> forse questi non servono
		static void printFloat();
		// Print the double
		static void printDouble();
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
		static void convert(const std::string &input);
		// Print the result
		static void print();
};

#endif

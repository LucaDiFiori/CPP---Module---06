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
#  define YELLOW "\033[1;33m"
#  define RESET "\033[0m"
# endif

# include <iostream>
# include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <cmath>
#include <sstream>

// Enum for the type of the input (used in the switch case)
enum check
{
	CHAR,
	BASIC_CONVERSION,
	INF_CONVERSION,
	NAN_CONVERSION
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
		static check _type;
		//the converted values
		static char _char;
		static int _int;
		static float _float;
		static double _double;


		//----------------------------------------------------------------------
		//                               UTILS
		//----------------------------------------------------------------------
	    //___________________________________________________________check_utils
		static bool isInfNan(std::string& input);
		static bool isValidNumber(std::string& input);
		static bool isSingleCharacter(std::string& input);
		static bool checkInput(std::string& input);


		//_________________________________________________________convert_utils
		// Convert the input to the desired type by performing the cast
		/* Note: The variable input_double is used to store the converted input.
		*       A double is chosen here, but you could use long or another large type.
		*       I just need a big value to store the input, and ultimately I have to
		*       convert it to double anyway.
		*/	
		static void toChar(double input_double);
		static void toInt(double input_double);
		static void toFloat(double input_double);
		static void toDouble(double input_double);
		// Convert the input to an infinite or a NaN double value
		static void toDoubleInfNan();    
		// Convert the input to an infinite or a NaN float value
		static void toFloatInfNan();
		
	    //___________________________________________________________print_utils	
		static void printChar(bool isPrintable);
		static void printInt(bool isPrintable);
		static void printFloat(bool isPrintable);
		static void printDouble(bool isPrintable);


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
		static void convert(std::string input);
};

#endif
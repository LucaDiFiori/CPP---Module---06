/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-05 09:44:15 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-11-05 09:44:15 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main()
{
	// Create a sample Data object
	Data data = {"Hello", 10, "this is my data"};

	//print the data
	std::cout << YELLOW << "=== My data struct contains: ===" << RESET << std::endl;
	std::cout << CYAN << "std::string s1: " << RESET << data.s1 << std::endl;
	std::cout << CYAN << "int n: " << RESET << data.n << std::endl;
	std::cout << CYAN << "std::string s2: " << RESET << data.s2 << std::endl;
	std::cout << std::endl;

	std::cout << YELLOW "=== Serialize the address of the data object ===" << RESET << std::endl;
	uintptr_t raw = Serializer::serialize(&data);
	std::cout << CYAN << "Address data (&Data): " << RESET << &data << std::endl;
	std::cout << CYAN << "Serialized address: " << RESET << raw << std::endl;
	std::cout << std::endl;

	std::cout << YELLOW << "=== Deserialize the address ===" << RESET << std::endl;
	Data* deserializedData = Serializer::deserialize(raw);
	std::cout << CYAN << "Serialized address: " << RESET << raw << std::endl;
	std::cout << CYAN << "Deserialized address: " << RESET << deserializedData << std::endl;
	std::cout << std::endl;

	std::cout << YELLOW << "=== Compare the original and deserialized data ===" << RESET << std::endl;
	if (&data == deserializedData) 
	{
		std::cout << GREEN << "Serialization and deserialization successful!" << std::endl;
        std::cout << "Data values: " << deserializedData->s1 << ", "
                  << deserializedData->n << ", " << deserializedData->s2 << RESET <<std::endl;
    } else {
        std::cout << RED <<"Serialization and deserialization failed." << RESET <<std::endl;
    }
}
/**
* @file				RecordDAO.h
* @author			Chloe Lee-Hone<leeh0002@algonquinlive.com>
* @version			1.0
* @section			The RecordDAO's class header. Defines the class variables and the methods that will be implemented in the source file. 
*					This project contains information licensed under the Open Government Licence – Canada [1][2]. Code structure was informed by the provided example written by Stanley Pieda for CST8333 [3].
* 
* Student Name:     Chloe Lee-Hone
* Student Number:   041023578
* Course:           CST8333_350: Programming Language Research Project
* Professor:        Reg Dyer
* Date:             05/06/2023
* 
* References:
* [1]   T. B. of C. Secretariat and T. B. S. of C. Open Government, “Open Government Licence - Canada.” http://open.canada.ca/en/open-government-licence-canada (accessed May 11, 2023).
* [2]	T. B. of C. Secretariat and Open Government Portal, “Vegetables in cold and common storage,” Oct. 10, 2008. https://open.canada.ca/data/en/dataset/473f9524-45f8-47d0-9a12-537bb7704089 (accessed May 16, 2023).
* [3]	S. Pieda, “CST8333 19F Practical Project 2 Example Layered.” Algonquin College, Algonquin College, Jun. 07, 2022. [Online]. Available: https://brightspace.algonquincollege.com/d2l/le/content/543581/viewContent/8322468/View
*/

#pragma once
#include "RecordDTO.h"
#include <string>
#include <vector>

#ifndef RECORD_DAO_H
#define RECORD_DAO_H

/**
 * @brief Acts as the layer between the data set and the main program.
*/
class RecordDAO
{
/**
 * @brief public declaration of the variables and methods to be implemented in RecordDAO.cpp 
*/
public:
	/** @brief The CSV data set contains 16 columns. Used in getAllRecords() */
	static const int NUM_OF_COLUMNS = 16;
	static const int MAX_LIST_SIZE = 100;

	/** @brief No-argument constructor */
	RecordDAO();

	/**
	 * @brief Retrieves records from CSV file and returns a list of RecordDTO objects. Used in the main method to print results. 
	 * @param filepath is the path to the file containing the CSV data set
	 * @return a vector of RecordDTO objects
	*/
	std::vector<RecordDTO> getAllRecords();

	/**
	 * @brief Opens the specified CSV file and creates a vector of Strings. Each index value represents one row in the CSV file.
	 * @return A vector containing the CSV file's rows
	*/
	std::vector<std::string> openFile();

	/**
	 * @brief Creates vector of RecordDTO instances
	 * @param data A vector of strings containing the data used to create RecordDTO objects
	 * @return A vector of RecordDTO objects
	*/
	std::vector<RecordDTO> createRecordDtoList(std::vector<std::string> data);

	/**
	 * @brief Removes the first RecordDTO, as it contains the original data set's headers
	 * @param recordList the vector of RecordDTOs that contains the data set's headers in its first index
	 * @return a vector of RecordDTOs without the headers
	*/
	std::vector<RecordDTO> removeHeaders(std::vector<RecordDTO> recordList);

	/**
	 * @brief Trims the vector to contain the specified number of objects.
	 * @param recordList The vector of RecordDTO containing all Records from the data set
	 * @param MAX_LIST_SIZE The number of RecordDTOs that the vector should contain
	 * @return A trimmed vector of RecordDTOs of size equal to MAX_LIST_SIZE
	*/
	std::vector<RecordDTO> trimList(std::vector<RecordDTO> recordList, int MAX_LIST_SIZE);

	/**
	 * @brief Splits each record string into multiple parts using the comma delimiter
	 * @param lines contains the records as comma-separated strings
	 * @return a vector of strings. Each string represents one cell of data. Used to create RecordDTO objects.
	*/
	std::vector<std::string> parseRecords(std::vector<std::string> lines);

	/**
	 * @brief Writes the list of RecordDTOs to a file under the name passed as its argument
	 * @param recordsList a vector of RecordDTOs
	 * @param newFileName the file name where the vector of RecordDTOs will be stored
	*/
	void writeToFile(std::vector<RecordDTO> recordsList, std::string newFileName);
};
#endif // !RECORD_DAO_H


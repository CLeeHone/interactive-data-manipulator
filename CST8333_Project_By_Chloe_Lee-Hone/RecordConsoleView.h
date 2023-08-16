/**
* @file				RecordConsoleView.h
* @author			Chloe Lee-Hone<leeh0002@algonquinlive.com>
* @version			1.0
* @section			Header file for RecordConsoleView class. 
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
#include "RecordService.h"
#include "doctest.h"

#ifndef RECORD_CONSOLE_VIEW_H
#define RECORD_CONSOLE_VIEW_H
class RecordConsoleView
{
private:
	RecordService recordService = RecordService();
	bool isContinue{ true };
	int userResponse{};
	static const int DISPLAY_RECORD			= 1;
	static const int CREATE_RECORD			= 2;
	static const int EDIT_RECORD			= 3;
	static const int DELETE_RECORD			= 4;
	static const int SAVE_CHANGES			= 5;
	static const int RELOAD_RECORDS			= 6;
	static const int SORT_RECORDS			= 7;
	static const int EXIT_PROGRAM			= 8;
	static const int PRINT_ONE_RECORD		= 1;
	static const int PRINT_MULTIPLE_RECORDS = 2;
	static const int PRINT_MOST_RECENT		= 3;


public:
	/**
	 * @brief Communicates the user's commands to the Persistence layer
	*/
	RecordConsoleView();

	/**
     * @brief The program's entry point. Continuously prints the menu until the user elects to exit the program.
	*/
	void showMenu();

	/**
	 * @brief Used in the showMenu() method to display the user's options.
    */
	void printMainMenuOptions();

	/**
	 * @brief Used in the showMenu() method to register the user's response and responds accordingly by calling one of the class' other methods.
	 * @param userResponse
	*/
	void processMainResponse(int);

	/**
	 * @brief Uses an instance of the RecordService class to reload the original dataset by communicating with the Persistence layer.
	*/
	void reloadData();

	/**
	 * @brief Prompts the user to enter a file name. This file name will be used to write the vector.
	*/
	void writeToFile(std::string newFileName);

	/**
	 * @brief Uses an instance of the RecordService class to reload the original dataset by communicating with the Persistence layer.
	*/
	void printSaveOptions();

	/**
	 * @brief Prints either a given record, a given number of records, or the most recently added record. This last option is useful for viewing a newly created record.
	*/
	void printRecords();

	void printSortedRecords(std::vector<RecordDTO> sortedRecords, int numRecords);

	/**
	 * @brief Creates a RecordDTO object based on a user's input. Adds the RecordDTO to the vector stored in memory.
	*/
	void createRecord();

	/**
	 * @brief Updates a specific RecordDTO based on user input. Currently only allows one value to be edited per command.
	*/
	void printUpdateOptions();

	/**
	 * @brief Uses an instance of RecordService to process the selected edit on a given record.
	 * @param recordId The RecordDTO's index in the vector stored in memory
	 * @param userSelection The RecordDTO's instance variable to be edited
	*/
	void processUpdateSelection(int recordId, int userSelection);

	/**
	 * @brief Prints the options to guide the user through the process of deleting a RecordDTO from the vector stored in memory
	*/
	void printDeleteOptions();

	/**
	 * @brief Uses an instance of RecordService class to communicate the user's decision to the Persistence layer, which manages the vector stored in memory.
	 * @param recordId The index of the RecordDTO to be deleted in the vector.
	*/
	void deleteRecord(int recordId);

	/**
	 * @brief Processes the user's choice to delete a RecordDTO or not.
	 * @param recordId The index of the RecordDTO to be deleted in the vector
	 * @param userSelection The user's decision to delete the RecordDTO or not. 0 = No, 1 = Yes
	*/
	void processDeleteSelection(int recordId, int userSelection);

	/**
	 * @brief Prompts the user to select the columns they wish to sort by
	*/
	void processSortSelection();

	/**
	 * @brief Uses the RecordService class to sort the records in the data structure stored in memory in either ascending or descending order.
	 * @param numRecords The number of records the user wants displayed following the sort operation
	 * @param order either 0 (ascending) or 1 (descending)
	 * @return the specifie number of RecordDTOs in the specified sorting order
	*/
	std::vector<RecordDTO> sortRecords(int numRecords, int order);

	/**
	 * @brief Checks that the Record selected by the user exists in the vector of RecordDTOs
	 * @param input the index in the vector containing the user's chosen RecordDTO
	 * @return true if the user's input is valid
	*/
	bool isValidRecord(int input);

	/**
	 * @brief Checks that the user selected a valid option to edit a given variable
	 * @param input the user's input representing a variable to edit
	 * @return true if the user's input is valid
	*/
	bool isValidSelection(int input);

	/**
	 * @brief Checks user input. Valid data is either 0 or 1
	 * @param orderSelection The user's input. Must be either 0 or 1
	 * @return true if the user input anything other than 0 or 1
	*/
	bool isInvalid(std::string order);

};
#endif //RECORD_CONSOLE_VIEW_h

/**
* @file				RecordConsoleView.cpp
* @author			Chloe Lee-Hone<leeh0002@algonquinlive.com>
* @version			1.0
* @section			The program's Presentation layer. Displays user options, and registers users' choices. Passes users' commands to an instance of the RecordService class. 
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

#include "RecordConsoleView.h"
#include "doctest.h"
#include <thread>
#include <iostream>
#include <fstream>
#include <type_traits>

const std::string INVALID_INPUT = "Invalid option was selected. Returning to main menu.\n";

/**
 * @brief Communicates the user's commands to the Persistence layer
*/
RecordConsoleView::RecordConsoleView() {}

/**
 * @brief The program's entry point. Continuously prints the menu until the user elects to exit the program. 
*/
void RecordConsoleView::showMenu() {
	while (RecordConsoleView::isContinue) {
		printMainMenuOptions();

		std::cin >> RecordConsoleView::userResponse;
		std::cin.ignore();
		RecordConsoleView::processMainResponse(RecordConsoleView::userResponse);

		if (RecordConsoleView::isContinue == false) {
			std::cout << "\nExiting program. Thank you!" << std::endl;
		}
	}
}

/**
 * @brief Used in the showMenu() method to display the user's options. 
*/
void RecordConsoleView::printMainMenuOptions() {
	std::cout << "\nStudent Name: Chloe Lee-Hone" << std::endl;
	std::cout << "Please select one of the following options by typing its corresponding number:\n1. Display record(s)\n2. Create a new record\n3. Edit a record\n4. Delete a record\n5. Save changes to file\n6. Reload all records\n7. Sort records by date and province\n8. Exit program" << std::endl << std::flush;
}

/**
 * @brief Used in the showMenu() method to register the user's response and responds accordingly by calling one of the class' other methods.
 * @param userResponse 
*/
void RecordConsoleView::processMainResponse(int userResponse) {
	switch (userResponse) {
	case RecordConsoleView::DISPLAY_RECORD:
		RecordConsoleView::printRecords();
		break;
	case RecordConsoleView::CREATE_RECORD:
		RecordConsoleView::createRecord();
		break;
	case RecordConsoleView::EDIT_RECORD:
		RecordConsoleView::printUpdateOptions();
		break;
	case RecordConsoleView::DELETE_RECORD:
		RecordConsoleView::printDeleteOptions();
		break;
	case RecordConsoleView::SAVE_CHANGES:
		RecordConsoleView::printSaveOptions();
		break;
	case RecordConsoleView::RELOAD_RECORDS:
		RecordConsoleView::reloadData();
		break;
	case RecordConsoleView::SORT_RECORDS:
		RecordConsoleView::processSortSelection();
		break;
	case RecordConsoleView::EXIT_PROGRAM:
		RecordConsoleView::isContinue = false;
		break;
	default:
		RecordConsoleView::showMenu();
	}

}

/**
 * @brief Prints either a given record, a given number of records, or the most recently added record. This last option is useful for viewing a newly created record. 
*/
void RecordConsoleView::printRecords() {
	int userResponse{0};
	std::cout << "\nPlease select one of the following options by typing its corresponding number:\n1. Display a record\n2. Display several records\n3. Print most recently added record." << std::endl;
	std::cin >> userResponse;
	std::cin.ignore();

	// Handles of out-of-bounds (>100 or <1) options
	if (userResponse == PRINT_ONE_RECORD) {
		int recordId{};
		
		std::cout << "\nPlease enter the record number you would like to view. Must be between 1 and 100:" << std::endl;
		std::cin >> recordId;
		std::cin.ignore();

		if (recordId > 100 || recordId < 1) {
			std::cout << INVALID_INPUT << "\n" << std::endl;
		}
		else {
			// The user doesn't know the vector's index starts at 0. If they enter 1, they likely want to access the first record. 
			// The recordId must be decremented to access the corresponding RecordDTO in the vector. 
			recordId -= 1;
			RecordConsoleView::recordService.getRecord(recordId).printRecord();
		}
	}
	else if (userResponse == PRINT_MULTIPLE_RECORDS) {
		int numberOfRecords{};
		std::cout << "\nPlease enter the number of records you would like to view. Maximum of 100:" << std::endl;
		std::cin >> numberOfRecords;
		std::cin.ignore();

		// Input validation ensures a valid number passed to the for-loop 
		if (isValidRecord(numberOfRecords)) {
			std::vector<RecordDTO> topRecords = RecordConsoleView::recordService.getTopRecords(numberOfRecords);
			for (int i = 0; i < topRecords.size(); i++) {
				topRecords.at(i).printRecord();
			}
		}
		else {
			std::cout << INVALID_INPUT << std::endl;
		}
	}
	else if (userResponse == PRINT_MOST_RECENT) {
		RecordConsoleView::recordService.getAllRecords().back().printRecord();
	}
	else {
		std::cout << INVALID_INPUT << std::endl;
	}
}

void RecordConsoleView::printSortedRecords(std::vector<RecordDTO> sortedRecords, int numRecords) {
	for (int i = 0; i < sortedRecords.size(); i++) {
		sortedRecords[i].printRecord();
	}
}

/**
 * @brief Creates a RecordDTO object based on a user's input. Adds the RecordDTO to the vector stored in memory. 
*/
void RecordConsoleView::createRecord() {
	std::string refDate{};
	std::string geo{};
	std::string dguid{};
	std::string productType{};
	std::string storageType{};
	std::string uom{};
	std::string uomId{};
	std::string scalarFactor{};
	std::string scalarId{};
	std::string vector{};
	std::string coordinate{};
	std::string value{};
	std::string status{};
	std::string symbol{};
	std::string terminated{};
	std::string decimals{};
	
	std::cout << "To create a record, please enter the answers to the following questions:" << std::endl;
	std::cout << "Ref Date: ";
	std::getline (std::cin, refDate);
	std::cout << "Geo: ";
	std::getline (std::cin, geo);
	std::cout << "DGUID: ";
	std::getline (std::cin, dguid);
	std::cout << "Product Type: ";
	std::getline (std::cin, productType);
	std::cout << "Storage Type: ";
	std::getline (std::cin, storageType);
	std::cout << "Unit of Measurement: ";
	std::getline (std::cin, uom);
	std::cout << "Unit of Measurement's ID: ";
	std::getline (std::cin, uomId);
	std::cout << "Scalar Factor: ";
	std::getline (std::cin, scalarFactor);
	std::cout << "Scalar Factor ID: ";
	std::getline (std::cin, scalarId);
	std::cout << "Vector: ";
	std::getline (std::cin, vector);
	std::cout << "Coordinate: ";
	std::getline (std::cin, coordinate);
	std::cout << "Value: ";
	std::getline (std::cin, value);
	std::cout << "Status: ";
	std::getline (std::cin, status);
	std::cout << "Symbol: ";
	std::getline (std::cin, symbol);
	std::cout << "Terminated: ";
	std::getline (std::cin, terminated);
	std::cout << "Decimals: ";
	std::getline (std::cin, decimals);

	RecordConsoleView::recordService.insertRecord(RecordDTO(refDate, geo, dguid, productType, storageType, uom, uomId, scalarFactor, scalarId, vector, coordinate, value, status, symbol, terminated, decimals));
	std::cout << "\nA new record was successfully created.\n" << std::endl;
}

/**
 * @brief Updates a specific RecordDTO based on user input. Currently only allows one value to be edited per command. 
*/
void RecordConsoleView::printUpdateOptions() {
	int recordId{};
	int userSelection{};

	std::cout << "To edit a record, please enter the ID of the record you would like to edit: " << std::endl;
	std::cin >> recordId;
	std::cin.ignore();

	if (isValidRecord(recordId)) {
		// The user doesn't know the vector's index starts at 0. If they enter 1, they likely want to access the first record. 
		// The recordId must be decremented to access the corresponding RecordDTO in the vector. 
		recordId -= 1;
		std::cout << "Which value would you like to edit?\n1. Ref Date\n2. Geo\n3. DGUID\n4. Product Type\n5. Storage Type\n6. Unit of Measurement\n7. Unit of Measurement ID\n8. Scalar Factor\n9. Scalar Factor ID\n10. Vector\n11. Coordinate\n12. Vaule\n13. Status\n14. Symbol\n15. Terminated\n16. Decimals" << std::endl;
		std::cin >> userSelection;
		std::cin.ignore();

		if (isValidSelection(userSelection)) {
			RecordConsoleView::processUpdateSelection(recordId, userSelection);
		}
		else {
			std::cout << INVALID_INPUT << std::endl;
		}
	}
	else {
		std::cout << INVALID_INPUT << std::endl;
	}
}

/**
 * @brief Uses an instance of RecordService to process the selected edit on a given record.
 * @param recordId The RecordDTO's index in the vector stored in memory
 * @param userSelection The RecordDTO's instance variable to be edited
*/
void RecordConsoleView::processUpdateSelection(int recordId, int userSelection) {
	std::string newValue{};

	switch (userSelection) {
	case 1:
		std::cout << "Please enter the new ref date:" << std::endl;
		std::getline (std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setRefDate(newValue);
		break;
	case 2:
		std::cout << "Please enter the new Geo:" << std::endl;
		std::getline (std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setGeo(newValue);
		break;
	case 3: 
		std::cout << "Please enter the new DGUID:" << std::endl;
		std::getline (std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setDguid(newValue);
		break;
	case 4:
		std::cout << "Please enter the new Product Type:" << std::endl;
		std::getline (std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setRefDate(newValue);
		break;
	case 5:
		std::cout << "Please enter the new Storage Type:" << std::endl;
		std::getline (std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setStorageType(newValue);
		break;
	case 6:
		std::cout << "Please enter the new Unit of Measurement:" << std::endl;
		std::getline (std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setUom(newValue);
		break;
	case 7:
		std::cout << "Please enter the new Unit of Measurement ID:" << std::endl;
		std::getline (std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setUomId(newValue);
		break;
	case 8:
		std::cout << "Please enter the new Scalar Factor:" << std::endl;
		std::getline (std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setScalarFactor(newValue);
		break;
	case 9:
		std::cout << "Please enter the new Scalar ID:" << std::endl;
		std::getline (std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setScalarId(newValue);
		break;
	case 10:
		std::cout << "Please enter the new Vector:" << std::endl;
		std::getline (std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setVector(newValue);
		break;
	case 11:
		std::cout << "Please enter the new Coordinate:" << std::endl;
		std::getline (std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setCoordinate(newValue);
		break;
	case 12:
		std::cout << "Please enter the new Value:" << std::endl;
		std::getline(std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setValue(newValue);
		break;
	case 13: 
		std::cout << "Please enter the new Status:" << std::endl;
		std::getline(std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setStatus(newValue);
		break;
	case 14:
		std::cout << "Please enter the new Symbol:" << std::endl;
		std::getline(std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setSymbol(newValue);
		break;
	case 15:
		std::cout << "Please enter the new Terminated:" << std::endl;
		std::getline(std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setTerminated(newValue);
		break;
	case 16: 
		std::cout << "Please enter the new Decimals:" << std::endl;
		std::getline(std::cin, newValue);
		RecordConsoleView::recordService.getRecord(recordId).setDecimals(newValue);
		break;
	default:
		std::cout << "Invalid option was selected. Returning to menu.\n" << std::endl;
		break;
	} 
}

/**
 * @brief Prints the options to guide the user through the process of deleting a RecordDTO from the vector stored in memory
*/
void RecordConsoleView::printDeleteOptions() {
	int recordId{};
	int userSelection{};

	std::cout << "To delete a record, please enter the ID (1-100) of the record you would like to remove: " << std::endl;
	std::cin >> recordId;
	// Users will likely start indexing at 1, not 0
	recordId -= 1;

	std::cout << "Are you sure you want to remove record #" << recordId << "? Enter 0 for 'No', 1 for 'Yes'" << std::endl;
	std::cin >> userSelection;
	
	std::cin.ignore();
	RecordConsoleView::processDeleteSelection(recordId, userSelection);
}

/**
 * @brief Processes the user's choice to delete a RecordDTO or not.
 * @param recordId The index of the RecordDTO to be deleted in the vector
 * @param userSelection The user's decision to delete the RecordDTO or not. 0 = No, 1 = Yes
*/
void RecordConsoleView::processDeleteSelection(int recordId, int userSelection) {
	switch (userSelection) {
	case(0):
		break;
	case(1):
		RecordConsoleView::deleteRecord(recordId);
		break;
	default:
		std::cout << "Invalid option was selected. Returning to menu.\n" << std::endl;
		break;
	}
}

/**
 * @brief Uses an instance of RecordService class to communicate the user's decision to the Persistence layer, which manages the vector stored in memory. 
 * @param recordId The index of the RecordDTO to be deleted in the vector. 
*/
void RecordConsoleView::deleteRecord(int recordId) {
	RecordConsoleView::recordService.deleteRecord(recordId);
	std::cout << "Record was deleted\n" << std::endl;
}

/**
 * @brief Prompts the user to enter a file name. This file name will be used to write the vector.
*/
void RecordConsoleView::printSaveOptions() {
	std::string newFileName{};
	std::cout << "Please enter the new file's name without the file extension: " << std::endl;
	std::cin >> newFileName;

	RecordConsoleView::writeToFile(newFileName);
}

/**
 * @brief Uses an instance of the RecordService class to write a new file containing the vector of RecordDTOs by communicating with the Persistence layer.
 * @param newFileName The file's name
*/
void RecordConsoleView::writeToFile(std::string newFileName) {
	std::thread writeThread(&RecordService::writeToFile, recordService, newFileName);
	writeThread.detach();
	std::cout << "\nNew file was successfully written to disk" << std::endl;
}

/**
 * @brief Uses an instance of the RecordService class to reload the original dataset by communicating with the Persistence layer. 
*/
void RecordConsoleView::reloadData() {
	RecordConsoleView::recordService.reloadData();
	std::cout << "Record data was reloaded\n" << std::endl;
}

/**
 * @brief Checks that the Record selected by the user exists in the vector of RecordDTOs
 * @param input the index in the vector containing the user's chosen RecordDTO
 * @return true if the user's input is valid
*/
bool RecordConsoleView::isValidRecord(int input) {
	return input > 0 && input <= RecordDAO::MAX_LIST_SIZE;
}

/**
 * @brief Checks that the user selected a valid option to edit a given variable
 * @param input the user's input representing a variable to edit
 * @return true if the user's input is valid
*/
bool RecordConsoleView::isValidSelection(int input) {
	return input > 0 && input <= RecordDAO::NUM_OF_COLUMNS;
}

/**
 * @brief Prompts the user to order by ascending or descending
*/
void RecordConsoleView::processSortSelection() {
	std::string orderSelection{};
	int numRecords{};

	while (RecordConsoleView::isInvalid(orderSelection)) {
		std::cout << "Would you like to sort in ascending or descending order? Please enter 0 for ascentding, or 1 for descending:" << std::endl;
		std::getline(std::cin, orderSelection);
		
		if (RecordConsoleView::isInvalid(orderSelection)) {
			std::cout << "Invalid input. Please enter 0 for ascending order, or 1 for descending order:" << std::endl;
		}
	}
	std::cout << "Please enter the number of records you would like to view (Maximum of 100):" << std::endl;
	std::cin >> numRecords;

	std::vector<RecordDTO> sortedRecords = sortRecords(numRecords, std::stoi(orderSelection));
	printSortedRecords(sortedRecords, numRecords);	
}

/**
 * @brief Checks user input. Valid data is either 0 or 1.
 * @param orderSelection The user's input. Must be either 0 or 1.
 * @return true if the user input anything other than 0 or 1.
*/
bool RecordConsoleView::isInvalid(std::string orderSelection) {
	return orderSelection != "0" && orderSelection != "1";
}

/**
 * @brief Uses the RecordService class to sort the records in the data structure stored in memory in either ascending or descending order.
 * @param numRecords The number of records the user wants displayed following the sort operation
 * @param order either 0 (ascending) or 1 (descending)
 * @return the specifie number of RecordDTOs in the specified sorting order
*/
std::vector<RecordDTO> RecordConsoleView::sortRecords(int numRecords, int order) {
	std::vector<RecordDTO> sortedRecords = recordService.sortRecords(order);
	sortedRecords.resize(numRecords);

	return sortedRecords;
}

/*
* Tests that the thread can write to a file by ascertaining that it can be successfully opened
*/
TEST_CASE("Test thread's writing functionality") {
	RecordService recordService {};
	std::string newFileName = "Testing_Thread_Writing_Functionality";

	std::thread writeThread(&RecordService::writeToFile, recordService, newFileName);
	writeThread.join();

	newFileName.append(".csv");

	std::ifstream file {};
	file.open(newFileName, std::ifstream::in);

	CHECK(file.is_open());
}

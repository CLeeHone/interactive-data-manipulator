/**
* @file				RecordService.h
* @author			Chloe Lee-Hone<leeh0002@algonquinlive.com>
* @version			1.0
* @section			Header file for the RecordService class.
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
#include <string>
#include <vector>
#include "RecordDAO.h"
#include "RecordDTO.h"
#include "doctest.h"

#ifndef RECORD_SERVICE_H
#define RFECORD_SERVICE_H
class RecordService
{
private:
	/** Simple data structure in memory. User interacts with this structure and modifies its contents. */
	std::vector<RecordDTO> recordList{};
	/** Used to persist the data structure or retrieve records from the CSV file*/
	RecordDAO recordAccessor{};

	struct Record {
		std::string RefDate;
		std::string Geo;
		std::string DGUID;
		std::string ProductType;
		std::string StorageType;
		std::string UnitOfMeasurement;
		std::string UnitOfMeasurementID;
		std::string ScalarFactor;
		std::string ScalarFactorID;
		std::string Vector;
		std::string Coordinate;
		std::string Value;
		std::string Status;
		std::string Symbol;
		std::string Terminated;
		std::string Decimals;
	};

public:
	/**
	 * @brief No-argument constructor
	*/
	RecordService();
	
	/**
	 * @brief Retrives the specified record from the RecordService class' vector. This method is used to retrieve
	 * a record from the vector and modify it, so we want to pass by reference, rather than by value.
	 * @param recordId the record's line number
	 * @return the specified RecordDTO
	*/
	RecordDTO &getRecord(int recordId);
	
	/**
	 * @brief Retrieves a given number of RecordDTOs in a vector
	 * @param numberOfRecords The number of RecordDTOs to retrieve
	 * @return a vector containing the specified number of RecordDTOs.
	*/
	std::vector<RecordDTO> getTopRecords(int numberOfRecords);
	
	/**
	 * @brief Returns all the records stored in the RecordService class' vector
	 * @return a list of RecordDTO objects
	*/
	std::vector<RecordDTO> getAllRecords();
	
	/**
	 * @brief Inserts a new record into the RecordService class' vector
	 * @param newRecord
	*/
	void insertRecord(RecordDTO newRecord);

	/**
	 * @brief Deletes a RecordDTO from the RecordService class' vector. Assumes the recordId is
	 * equivalent to its row in the CSV file.
	 * @param recordId the record's row in the CSV file
	*/
	void deleteRecord(int recordId);
	
	/**
	 * @brief Uses the RecordDAO object to write the current list of records to a new file
	*/
	void writeToFile(std::string newFileName);

	/**
	 * @brief Uses the RecordDAO object to reload the data from the original CSV file
	*/
	void reloadData();

	/**
	 * @brief Sorts the RefDate and Geo columns by ascending or descending, depending on the user's input
	 * @param order either 0 (ascending) or 1(descending).
	 * @return the sorted vector of RecordDTOs
	*/
	std::vector<RecordDTO> sortRecords(int order);

};
#endif // RECORD_SERVICE_H

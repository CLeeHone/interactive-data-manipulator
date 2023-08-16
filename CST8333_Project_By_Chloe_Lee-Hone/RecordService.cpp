/**
* @file				RecordService.cpp
* @author			Chloe Lee-Hone<leeh0002@algonquinlive.com>
* @version			1.0
* @section			RecordService class acts as an intermediary layer between the PresentationLayer, with which the user interacts, and the Persistence layer. 
*					Manages the vector of RecordDTOs that is stored in memory and can be modified by the user. 
*					This project contains information licensed under the Open Government Licence – Canada [1][2]. Code structure was informed by the provided example written by Stanley Pieda for CST8333 [3].
*
* Student Name:     Chloe Lee-Hone
* Student Number:   041023578
* Course:           CST8333_350: Programming Language Research Project
* Professor:        Reg Dyer
* Date:            05/06/2023
*
* References:
* [1]   T. B. of C. Secretariat and T. B. S. of C. Open Government, “Open Government Licence - Canada.” http://open.canada.ca/en/open-government-licence-canada (accessed May 11, 2023).
* [2]	T. B. of C. Secretariat and Open Government Portal, “Vegetables in cold and common storage,” Oct. 10, 2008. https://open.canada.ca/data/en/dataset/473f9524-45f8-47d0-9a12-537bb7704089 (accessed May 16, 2023).
* [3]	S. Pieda, “CST8333 19F Practical Project 2 Example Layered.” Algonquin College, Algonquin College, Jun. 07, 2022. [Online]. Available: https://brightspace.algonquincollege.com/d2l/le/content/543581/viewContent/8322468/View
* [4]	E. Laine, “Answer to ‘Sort vector of objects using TWO criteria,’” Stack Overflow, Mar. 22, 2017. https://stackoverflow.com/a/42940557 (accessed Aug. 04, 2023).
* [5]	fabian, “Answer to ‘How to sort an vector based on any column value by passing the column index as input?,’” Stack Overflow, Jun. 01, 2022. https://stackoverflow.com/a/72466036 (accessed Aug. 04, 2023).
* [6]	BTR, “Answer to ‘How to sort with a lambda?,’” Stack Overflow, Feb. 25, 2011. https://stackoverflow.com/a/5123582 (accessed Aug. 03, 2023).
*/

#include "RecordService.h"
#include "doctest.h"
//#include <map>
#include <algorithm>

const int ASCENDING_ORDER = 0;
const int DESCENDING_ORDER = 1;

/**
 * @brief When a RecordService object is created, it reloads the data from the original data source.
*/
RecordService::RecordService() {
	RecordService::reloadData();
}

/**
 * @brief Retrieves the specified record from the RecordService class' vector. This method is used to retrieve 
 * a record from the vector and modify it, so we want to pass by reference, rather than by value. 
 * @param recordId the record's line number
 * @return the specified RecordDTO
*/
RecordDTO &RecordService::getRecord(int recordId) {
	 //assumes the recordId corresponds to a record's row number
	return RecordService::recordList.at(recordId);
}

/**
 * @brief Retrieves a given number of RecordDTOs in a vector
 * @param numberOfRecords The number of RecordDTOs to retrieve
 * @return a vector containing the specified number of RecordDTOs.
*/
std::vector<RecordDTO> RecordService::getTopRecords(int numberOfRecords) {
	std::vector<RecordDTO> topRecords{};
	
	for (int i = 0; i < numberOfRecords; i++) {
		topRecords.push_back(RecordService::recordList.at(i));
	}
	return topRecords;
}

/**
 * @brief Returns all the records stored in the RecordService class' vector
 * @return a list of RecordDTO objects
*/
std::vector<RecordDTO> RecordService::getAllRecords() {
	return RecordService::recordList;
}

/**
 * @brief Inserts a new record into the RecordService class' vector
 * @param newRecord 
*/
void RecordService::insertRecord(RecordDTO newRecord) {
	RecordService::recordList.push_back(newRecord);
}

/**
 * @brief Deletes a RecordDTO from the RecordService class' vector. Assumes the recordId is 
 * equivalent to its row in the CSV file.
 * @param recordId the record's row in the CSV file
*/
void RecordService::deleteRecord(int recordId) {
	RecordService::recordList.erase(RecordService::recordList.begin() + recordId);
}

/**
 * @brief Uses the RecordDAO object to write the current list of records to a new file
*/
void RecordService::writeToFile(std::string newFileName) {
	newFileName.append(".csv");
	recordAccessor.writeToFile(RecordService::recordList, newFileName);
}

/**
 * @brief Uses the RecordDAO object to reload the data from the original CSV file
*/
void RecordService::reloadData() {
	RecordService::recordList = recordAccessor.getAllRecords();
}

/**
 * @brief Sorts the RefDate and Geo columns by ascending or descending, depending on the user's input
 * @param order either 0 (ascending) or 1(descending).
 * @return the sorted vector of RecordDTOs
 * Learned how to use C++ streams in [4][5][6]
*/
std::vector<RecordDTO> RecordService::sortRecords(int order) {
	if (order == ASCENDING_ORDER) {
		std::sort(RecordService::recordList.begin(), RecordService::recordList.end(), [](RecordDTO first, RecordDTO second) {
			if (first.getRefDate() != second.getRefDate()) return first.getRefDate() < second.getRefDate(); return first.getGeo() < second.getGeo();
			});
	}
	if (order == DESCENDING_ORDER) {
		std::sort(RecordService::recordList.begin(), RecordService::recordList.end(), [](RecordDTO first, RecordDTO second) {
			if (first.getRefDate() != second.getRefDate()) return first.getRefDate() > second.getRefDate(); return first.getGeo() > second.getGeo();
			});
	}

	return RecordService::recordList;
}

//STUDENT NAME: CHLOE LEE-HONE
/**
* Tests the process of inserting a RecordDTO into the vector stored in memory. To do so, a RecordDTO is inserted into the RecordService object's vector. 
* Test passes if all data in the vector's most recently added record corresponds to the data from the RecordDTO created for this unit test. 
*/
TEST_CASE("Test that records are inserted into the vector with correct data") {
	RecordService recordService{};
	RecordDTO recordDto("CLH RefDate", 
						"CLH Geo", 
						"CLH DGUID", 
						"CLH Product Type", 
						"CLH Storage Type", 
						"CLH UOM", 
						"CLH UOM ID", 
						"CLH Scalar Factor", 
						"CLH Scalar ID", 
						"CLH Vector", 
						"CLH Coordinate", 
						"CLH Value", 
						"CLH Status", 
						"CLH Symbol", 
						"CLH Terminated", 
						"CLH Decimals");
	
	recordService.insertRecord(recordDto);

	CHECK(recordService.getAllRecords().back().getRefDate()			== "CLH RefDate");
	CHECK(recordService.getAllRecords().back().getGeo()				== "CLH Geo");
	CHECK(recordService.getAllRecords().back().getDguid()			== "CLH DGUID");
	CHECK(recordService.getAllRecords().back().getProductType()		== "CLH Product Type");
	CHECK(recordService.getAllRecords().back().getStorageType()		== "CLH Storage Type");
	CHECK(recordService.getAllRecords().back().getUom()				== "CLH UOM");
	CHECK(recordService.getAllRecords().back().getUomId()			== "CLH UOM ID");
	CHECK(recordService.getAllRecords().back().getScalarFactor()	== "CLH Scalar Factor");
	CHECK(recordService.getAllRecords().back().getScalarId()		== "CLH Scalar ID");
	CHECK(recordService.getAllRecords().back().getVector()			== "CLH Vector");
	CHECK(recordService.getAllRecords().back().getCoordinate()		== "CLH Coordinate");
	CHECK(recordService.getAllRecords().back().getValue()			== "CLH Value");
	CHECK(recordService.getAllRecords().back().getStatus()			== "CLH Status");
	CHECK(recordService.getAllRecords().back().getSymbol()			== "CLH Symbol");
	CHECK(recordService.getAllRecords().back().getTerminated()		== "CLH Terminated");
	CHECK(recordService.getAllRecords().back().getDecimals()		== "CLH Decimals");
}




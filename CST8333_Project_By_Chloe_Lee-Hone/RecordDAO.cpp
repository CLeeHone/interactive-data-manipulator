/**
* @file				RecordDAO.cpp
* @author			Chloe Lee-Hone<leeh0002@algonquinlive.com>
* @version			1.0
* @section			The RecordDAO accesses the database to create a layer of separation between the data set and the main program.
*					Parses data from the CSV file and creates RecordDTO objects. This project contains information licensed under the Open Government Licence – Canada [1][2].
*					Code structure was informed by the provided example written by Stanley Pieda for CST8333 [3].
*					
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
* [4]	cplusplus.com, “std::istream,” cplusplus.com. https://cplusplus.com/reference/fstream/ifstream/ (accessed May 19, 2023).
*/

#include "RecordDAO.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <future>
#include "doctest.h"

const std::string ORIGINAL_FILE_PATH = "32100260.csv";

RecordDAO::RecordDAO() {}

/**
 * @brief Retrieves records from CSV file and returns a list of 100 RecordDTO objects. Used in the main method to print results.
 * @param filepath is the path to the file containing the CSV data set
 * @return a vector of RecordDTO objects
*/
std::vector<RecordDTO> RecordDAO::getAllRecords() {
	// Loads the dataset
	std::future<std::vector<std::string>> future = std::async(std::launch::async, &RecordDAO::openFile, this);
	std::vector<std::string> lines = future.get();

	/** Stores each cell's data, which is then used to create a RecordDTO object */
	std::future<std::vector<std::string>> future2 = std::async(std::launch::async, &RecordDAO::parseRecords, this, lines);
	std::vector<std::string> data = future2.get();

	std::future<std::vector<RecordDTO>> future3 = std::async(std::launch::async, &RecordDAO::createRecordDtoList, this, data);
	std::vector<RecordDTO> recordList = future3.get();

	recordList = removeHeaders(recordList);

	return trimList(recordList, MAX_LIST_SIZE);
}

/**
 * @brief Opens the specified CSV file and creates a vector of Strings. Each index value represents one row in the CSV file.
 * @return A vector containing the CSV file's rows
*/
std::vector<std::string> RecordDAO::openFile() {
	std::vector<std::string> lines{};

	/** Performs the CSV input operation [4] */
	std::ifstream records{};

	try {
		records.open(ORIGINAL_FILE_PATH, std::ifstream::in);
	}
	catch (std::ifstream::failure) {
		throw "Reading the file path caused an error.";
	}

	/**
	 * The CSV's lines are first placed into a vector. It was necessary to to this in two steps, because we can't split on both
	 * a carriage return (\n) as well as a comma. Otherwise, the last column's data will include the next line's cell's data, as they are not
	 * comma separated.
	 */
	try {
		while (records.peek() != EOF) {
			std::string record{};
			std::getline(records, record);
			lines.push_back(record);
		}
	}
	catch (std::ifstream::failure exception) {
		throw "Iterating over the records and adding them to the vector caused an error.";
	}

	return lines;
}

/**
 * @brief Creates vector of RecordDTO instances
 * @param data A vector of strings containing the data used to create RecordDTO objects
 * @return A vector of RecordDTO objects
*/
std::vector<RecordDTO> RecordDAO::createRecordDtoList(std::vector<std::string> data) {
	/** Stores all RecordDTO objects, and is iterated over in the main method */
	std::vector<RecordDTO> recordList{};
	/** Index starts at 1, because otherwise the modulo check will return true when i = 0, and an out of bounds exception will be thrown */
	for (int i = 1; i < data.size(); i++) {
		if (i % RecordDAO::NUM_OF_COLUMNS == 0) {
			RecordDTO recordDto{};

			recordDto.setRefDate(data.at(i - 16));
			recordDto.setGeo(data.at(i - 15));
			recordDto.setDguid(data.at(i - 14));
			recordDto.setProductType(data.at(i - 13));
			recordDto.setStorageType(data.at(i - 12));
			recordDto.setUom(data.at(i - 11));
			recordDto.setUomId(data.at(i - 10));
			recordDto.setScalarFactor(data.at(i - 9));
			recordDto.setScalarId(data.at(i - 8));
			recordDto.setVector(data.at(i - 7));
			recordDto.setCoordinate(data.at(i - 6));
			recordDto.setValue(data.at(i - 5));
			recordDto.setStatus(data.at(i - 4));
			recordDto.setSymbol(data.at(i - 3));
			recordDto.setTerminated(data.at(i - 2));
			recordDto.setDecimals(data.at(i - 1));

			recordList.push_back(recordDto);
		}
	}
	return recordList;
}

/**
 * @brief Removes the first RecordDTO, as it contains the original data set's headers
 * @param recordList the vector of RecordDTOs that contains the data set's headers in its first index
 * @return a vector of RecordDTOs without the headers
*/
std::vector<RecordDTO> RecordDAO::removeHeaders(std::vector<RecordDTO> recordList) {
	// Removes the first RecordDTO, because it contains the CSV headers
	recordList.erase(recordList.begin());
	return recordList;
}

/**
 * @brief Trims the vector to contain the specified number of objects.
 * @param recordList The vector of RecordDTO containing all Records from the data set
 * @param MAX_LIST_SIZE The number of RecordDTOs that the vector should contain
 * @return A trimmed vector of RecordDTOs of size equal to MAX_LIST_SIZE
*/
std::vector<RecordDTO> RecordDAO::trimList(std::vector<RecordDTO> recordList, int MAX_LIST_SIZE) {
	// Trims the vector to only contain the specified number of RecordDTOs
	recordList.resize(MAX_LIST_SIZE);
	return recordList;
}

/**
 * @brief Splits each record string into multiple parts using the comma delimiter
 * @param lines contains the records as comma-separated strings
 * @return a vector of strings. Each string represents one cell of data. Used to create RecordDTO objects.
*/
std::vector<std::string> RecordDAO::parseRecords(std::vector<std::string> lines) {
	std::vector<std::string> data{};
	// Iterate through each string, which corresponds to one entire record, and split on comma

	try {
		for (int j = 0; j < lines.size(); j++) {
			std::stringstream stringStream{ lines.at(j) };
			// Stores the cell data value, which is used to construct the RecordDTo object
			std::string dataPoint{ "" };

			// Split the record string using the comma delimiter
			while (std::getline(stringStream, dataPoint, ',')) {
				data.push_back(dataPoint);
			}
		}
	}
	catch (std::stringstream::failure) {
		throw "Extracting data from the records by splitting them on the comma delimiter caused an error.";
	}
	return data;
}

/**
 * @briefTakes the vector's data and stores it in a new CSV file
 * @param recordsList The vector of RecordDTOs to be stored in a new file
 * @param newFileName The new file's name
*/
void RecordDAO::writeToFile(std::vector<RecordDTO> recordList, std::string newFileName) {
	try {
		std::ofstream newRecordsFile{};
		newRecordsFile.open(newFileName);

		for (int i = 0; i < recordList.size(); i++)
		{
			newRecordsFile << recordList.at(i).getRefDate()		<< ",";
			newRecordsFile << recordList.at(i).getGeo()			<< ",";
			newRecordsFile << recordList.at(i).getDguid()		<< ",";
			newRecordsFile << recordList.at(i).getProductType() << ",";
			newRecordsFile << recordList.at(i).getStorageType() << ",";
			newRecordsFile << recordList.at(i).getUom()			<< ",";
			newRecordsFile << recordList.at(i).getUomId()		<< ",";
			newRecordsFile << recordList.at(i).getScalarFactor()<< ",";
			newRecordsFile << recordList.at(i).getScalarId()	<< ",";
			newRecordsFile << recordList.at(i).getVector()		<< ",";
			newRecordsFile << recordList.at(i).getCoordinate()	<< ",";
			newRecordsFile << recordList.at(i).getValue()		<< ",";
			newRecordsFile << recordList.at(i).getStatus()		<< ",";
			newRecordsFile << recordList.at(i).getSymbol()		<< ",";
			newRecordsFile << recordList.at(i).getTerminated()	<< ",";
			newRecordsFile << recordList.at(i).getDecimals()	<< std::endl;
		}
		newRecordsFile.close();
	}
	catch (std::ofstream::failure) {
		std::cout << "An error occurred while writing the dataset to a new file." << std::endl;
	}
}

TEST_CASE("Test that ifstream successfully opens") {
	std::string filepath = "32100260.csv";
	std::ifstream records{};
	records.open(filepath, std::ifstream::in);
	CHECK(records.is_open());
}

TEST_CASE("Test that ofstream successfully writes to a new file") {
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

	std::vector<RecordDTO> recordList{ recordDto };
	std::string filepath = "docTest_new_file.csv";
	RecordDAO recordDao{};

	recordDao.writeToFile(recordList, filepath);
	std::ifstream records{};
	records.open(filepath, std::ifstream::in);
	CHECK(records.is_open());
}




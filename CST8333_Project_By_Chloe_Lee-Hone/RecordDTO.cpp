/**
 * @file			RecordDTO.cpp
 * @author			Chloe Lee-Hone <leeh0002@algonquinlive.com>
 * @version			1.0
 * @section			This file contains the RecordDTO class used by the RecordDAO class to store a record retrieved from the Open Government database. 
 *					This project contains information licensed under the Open Government Licence – Canada [1][2]. Code structure was informed by the provided example written by Stanley Pieda for CST8333 [3].
 * 
 * Student Name:     Chloe Lee-Hone
 * Student Number:   041023578
 * Course:           CST8333_350: Programming Language Research Project
 * Professor:        Reg Dyer
 * Date:             05/06/2023
 *
 * References:
 * [1]  T. B. of C. Secretariat and T. B. S. of C. Open Government, “Open Government Licence - Canada.” http://open.canada.ca/en/open-government-licence-canada (accessed May 11, 2023).
 * [2]	T. B. of C. Secretariat and Open Government Portal, “Vegetables in cold and common storage,” Oct. 10, 2008. https://open.canada.ca/data/en/dataset/473f9524-45f8-47d0-9a12-537bb7704089 (accessed May 16, 2023).
 * [3]	S. Pieda, “CST8333 19F Practical Project 2 Example Layered.” Algonquin College, Algonquin College, Jun. 07, 2022. [Online]. Available: https://brightspace.algonquincollege.com/d2l/le/content/543581/viewContent/8322468/View
 * [4]	S. C. Government of Canada, “Dictionary, Census of Population, 2021 – Dissemination Geography Unique Identifier (DGUID),” Nov. 17, 2021. https://www12.statcan.gc.ca/census-recensement/2021/ref/dict/az/Definition-eng.cfm?ID=geo055 (accessed May 20, 2023).
 */

#include "doctest.h"
#include <iostream>
#include "RecordDTO.h"

/**
 * @brief No argument constructor. Used in RecordDAO to create a RecordDTO
*/
RecordDTO::RecordDTO() {}

/**
 * @brief				Parameterized constructor
 * @param refDate		The year this record was recorded
 * @param geo			The location, either Canada or a province, where the record was recorded
 * @param dguid			Dissemination Geography Unique Identifier [4]
 * @param productType	Vegetable name
 * @param storageType	Type of storage used for the vegetables
 * @param uom			Unit of Measurement 
 * @param uomId			Unit of Measurement's ID
 * @param scalarFactor	Ratio
 * @param scalarId		Ratio ID
 * @param vector		Spatial representation in vector format
 * @param coordinate	Location of the site where the record was taken
 * @param value			The record's value
 * @param status		The record's status
 * @param symbol		The record's symbol
 * @param terminated	The record's terminated status
 * @param decimals		The number of decimals
*/
RecordDTO::RecordDTO(std::string refDate, std::string geo, std::string dguid, std::string productType, std::string storageType,
						std::string uom, std::string uomId, std::string scalarFactor, std::string scalarId, std::string vector,
						std::string coordinate, std::string value, std::string status, std::string symbol, std::string terminated,
						std::string decimals) {

	RecordDTO::refDate		= refDate;
	RecordDTO::geo			= geo;
	RecordDTO::dguid		= dguid;
	RecordDTO::productType	= productType;
	RecordDTO::storageType	= storageType;
	RecordDTO::uom			= uom;
	RecordDTO::uomId		= uomId;
	RecordDTO::scalarFactor	= scalarFactor;
	RecordDTO::scalarId		= scalarId;
	RecordDTO::vector		= vector;
	RecordDTO::coordinate	= coordinate;
	RecordDTO::value		= value;
	RecordDTO::status		= status;
	RecordDTO::symbol		= symbol;
	RecordDTO::terminated	= terminated;
	RecordDTO::decimals		= decimals;

}

/**
 * @brief the date the record was recorded
 * @return the date the record was recorded
*/
std::string RecordDTO::getRefDate()				{ return RecordDTO::refDate; }
/**
 * @brief the location where the record was recorded
 * @return the location where the record was recorded
*/
std::string RecordDTO::getGeo()					{ return RecordDTO::geo; }
/**
 * @brief the Dissemination Geography Unique Identifier [4]
 * @return the dguid
*/std::string RecordDTO::getDguid()				{ return RecordDTO::dguid; }
/**
 * @brief the type of vegetable
 * @return the type of vegetable
*/
std::string RecordDTO::getProductType()			{ return RecordDTO::productType; }
/**
 * @brief the storage type
 * @return the storage type
*/
std::string RecordDTO::getStorageType()			{ return RecordDTO::storageType; }
/**
 * @brief the unit of measurement
 * @return the unit of measurement 
*/
std::string RecordDTO::getUom()					{ return RecordDTO::uom; }
/**
 * @brief the unit of measurement's ID
 * @return the unit of measurement's ID 
*/
std::string RecordDTO::getUomId()				{ return RecordDTO::uomId; }
/**
 * @brief the record's scalar factor
 * @return the record's scalar factor 
*/
std::string RecordDTO::getScalarFactor()		{ return RecordDTO::scalarFactor; }
/**
 * @brief the record's scalar ID
 * @return the record's scalar ID 
*/
std::string RecordDTO::getScalarId()			{ return RecordDTO::scalarId; }
/**
 * @brief the record's spatial representation in vector format
 * @return the record's spatial representation in vector format 
*/
std::string RecordDTO::getVector()				{ return RecordDTO::vector; }
/**
 * @brief the location where the record was taken 
 * @return the location where the record was taken 
*/
std::string	RecordDTO::getCoordinate()			{ return RecordDTO::coordinate; }
/**
 * @brief the record's value
 * @return the record's value 
*/
std::string	RecordDTO::getValue()				{ return RecordDTO::value; }
/**
 * @brief the record's status
 * @return the record's status 
*/
std::string RecordDTO::getStatus()				{ return RecordDTO::status; }
/**
 * @brief the record's symbol
 * @return the record's symbol 
*/
std::string RecordDTO::getSymbol()				{ return RecordDTO::symbol; }
/**
 * @brief the record's terminated status
 * @return the record's terminated status 
*/
std::string RecordDTO::getTerminated()			{ return RecordDTO::terminated; }
/**
 * @brief the number of decimals in the record
 * @return the number of decimals in the record 
*/
std::string	RecordDTO::getDecimals()			{ return RecordDTO::decimals; }

/**
* Sets a new reference date. Used in RecordDAO to create a RecordDTO.
* @return void
*/
//RecordDTO RecordDTO::setRefDate(std::string date) { refDate = date; return *this; }
void RecordDTO::setRefDate(std::string date)					{ refDate = date; }
/**
* Sets a new geographic location. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setGeo(std::string newGeo)						{ geo = newGeo; };
/**
* Sets a new DGUID. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setDguid(std::string newDguid)					{ dguid = newDguid; }
/**
* Sets a new product type. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setProductType(std::string newProductType)		{ productType = newProductType; }
/**
* Sets a new storage type. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setStorageType(std::string newStorageType)		{ storageType = newStorageType; }
/**
* Sets a new unit of measurement. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setUom(std::string newUom)						{ uom = newUom; }
/**
* Sets a new unit of measurement ID. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setUomId(std::string newUomId)					{ uomId = newUomId; }
/**
* Sets a new scalar factor. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setScalarFactor(std::string newScalarFactor)	{ scalarFactor = newScalarFactor; }
/**
* Sets a new scalar factor ID. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setScalarId(std::string newScalarId)			{ scalarId = newScalarId; }
/**
* Sets a new vector. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setVector(std::string newVector)				{ vector = newVector; }
/**
* Sets a new coordinate. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setCoordinate(std::string newCoordinate)		{ coordinate = newCoordinate; }
/**
* Sets a new value. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setValue(std::string newValue)					{ value = newValue; }
/**
* Sets a new status. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setStatus(std::string newStatus)				{ status = newStatus; }
/**
* Sets a new symbol. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setSymbol(std::string newSymbol)				{ symbol = newSymbol; }
/**
* Sets a new terminated status. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setTerminated(std::string newTerminated)		{ terminated = newTerminated; }
/**
* Sets a new decimals. Used in RecordDAO to create a RecordDTO.
* @return void
*/
void RecordDTO::setDecimals(std::string newDecimals)			{ decimals = newDecimals; }

/** 
 * Prints a formatted RecordDTO's information. Used in main() to print a specified number of records.  
 * @return void
 */
void RecordDTO::printRecord() {
		std::cout << "RefDate:\t\t" << getRefDate() << "\nGeo:\t\t\t" << getGeo() << "\nDGUID:\t\t\t" << getDguid()
			<< "\nProduct Type:\t\t" << getProductType() << "\nStorage Type:\t\t" << getStorageType() << "\nUnit of Measurement:\t"
			<< getUom() << "\nUnit of Measurement ID: " << getUomId() << "\nScalar Factor:\t\t" << getScalarFactor() << "\nScalar ID:\t\t"
			<< getScalarId() << "\nVector:\t\t\t" << getVector() << "\nCoordinate:\t\t" << getCoordinate() << "\nValue:\t\t\t" << getValue()
			<< "\nStatus:\t\t\t" << getStatus() << "\nSymbol:\t\t\t" << getSymbol() << "\nTerminated:\t\t" << getTerminated()
			<< "\nDecimals:\t\t" << getDecimals() << std::endl << std::endl;
}

TEST_CASE("Test parameterized RecordDTO's constructor") {
	/* Check that accessors for parameterized constructor are correctand that parameters are associated with the correct instance variables */
	RecordDTO recordDto("1979-10-01","Canada","","Onions","Cold and common storage","Tonnes","288","units","0","v722359","2.4.1","0","","","","0");
	
	CHECK(recordDto.getRefDate()		== "1979-10-01");
	CHECK(recordDto.getGeo()			== "Canada");
	CHECK(recordDto.getDguid()			== "");
	CHECK(recordDto.getProductType()	== "Onions");
	CHECK(recordDto.getStorageType()	== "Cold and common storage");
	CHECK(recordDto.getUom()			== "Tonnes");
	CHECK(recordDto.getUomId()			== "288");
	CHECK(recordDto.getScalarFactor()	== "units");
	CHECK(recordDto.getScalarId()		== "0");
	CHECK(recordDto.getVector()			== "v722359");
	CHECK(recordDto.getCoordinate()		== "2.4.1");
	CHECK(recordDto.getValue()			== "0");
	CHECK(recordDto.getStatus()			== "");
	CHECK(recordDto.getSymbol()			== "");
	CHECK(recordDto.getTerminated()		== "");
	CHECK(recordDto.getDecimals()		== "0");
}

TEST_CASE("Test parameterized constructor DTO's modifiers") {
	/* Check that modifiers are assigning the correct values to instance variables */
	RecordDTO recordDto("1979-10-01", "Canada", "", "Onions", "Cold and common storage", "Tonnes", "288", "units", "0", "v722359", "2.4.1", "0", "", "", "", "0");
	
	recordDto.setRefDate("Test Ref Date");
	recordDto.setGeo("Test Geo");
	recordDto.setDguid("Test Dguid");
	recordDto.setProductType("Test Product Type");
	recordDto.setStorageType("Test Storage Type");
	recordDto.setUom("Test Unit of Measurement");
	recordDto.setUomId("Test UoM ID");
	recordDto.setScalarFactor("Test Scalar Factor");
	recordDto.setScalarId("Test Scalar Id");
	recordDto.setVector("Test Vector");
	recordDto.setCoordinate("Test Coordinate");
	recordDto.setValue("Test Value");
	recordDto.setStatus("Test Status");
	recordDto.setSymbol("Test Symbol");
	recordDto.setTerminated("Test Terminated");
	recordDto.setDecimals("Test Decimals");

	CHECK(recordDto.getRefDate()		== "Test Ref Date");
	CHECK(recordDto.getGeo()			== "Test Geo");
	CHECK(recordDto.getDguid()			== "Test Dguid");
	CHECK(recordDto.getProductType()	== "Test Product Type");
	CHECK(recordDto.getStorageType()	== "Test Storage Type");
	CHECK(recordDto.getUom()			== "Test Unit of Measurement");
	CHECK(recordDto.getUomId()			== "Test UoM ID");
	CHECK(recordDto.getScalarFactor()	== "Test Scalar Factor");
	CHECK(recordDto.getScalarId()		== "Test Scalar Id");
	CHECK(recordDto.getVector()			== "Test Vector");
	CHECK(recordDto.getCoordinate()		== "Test Coordinate");
	CHECK(recordDto.getValue()			== "Test Value");
	CHECK(recordDto.getStatus()			== "Test Status");
	CHECK(recordDto.getSymbol()			== "Test Symbol");
	CHECK(recordDto.getTerminated()		== "Test Terminated");
	CHECK(recordDto.getDecimals()		== "Test Decimals");
}

TEST_CASE("Test no-argument DTO's default instance variable values") {
	RecordDTO noArgsRecordDto{};

	CHECK(noArgsRecordDto.getRefDate()		== "");
	CHECK(noArgsRecordDto.getRefDate()		== "");
	CHECK(noArgsRecordDto.getGeo()			== "");
	CHECK(noArgsRecordDto.getDguid()		== "");
	CHECK(noArgsRecordDto.getProductType()	== "");
	CHECK(noArgsRecordDto.getStorageType()	== "");
	CHECK(noArgsRecordDto.getUom()			== "");
	CHECK(noArgsRecordDto.getUomId()		== "");
	CHECK(noArgsRecordDto.getScalarFactor()	== "");
	CHECK(noArgsRecordDto.getScalarId()		== "");
	CHECK(noArgsRecordDto.getVector()		== "");
	CHECK(noArgsRecordDto.getCoordinate()	== "");
	CHECK(noArgsRecordDto.getValue()		== "");
	CHECK(noArgsRecordDto.getStatus()		== "");
	CHECK(noArgsRecordDto.getSymbol()		== "");
	CHECK(noArgsRecordDto.getTerminated()	== "");
	CHECK(noArgsRecordDto.getDecimals()		== "");
}

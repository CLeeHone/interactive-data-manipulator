/**
* @file				RecordDTO.h
* @author			Chloe Lee-Hone<leeh0002@algonquinlive.com>
* @version			1.0
* @section			This file contains the RecordDTO class' header. 
					This project contains information licensed under the Open Government Licence – Canada [1][2]. Code structure was informed by the provided example written by Stanley Pieda for CST8333 [3].
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
#include <iostream>
#include <string>
#include <format>
#include "doctest.h"

#ifndef RECORD_DTO_H
#define RECORD_DTO_H
/**
* RecordDTO class is used by the RecordDAO class to store a record retrieved from the Open Government database.
*/
class RecordDTO {
// STUDENT NAME: CHLOE LEE-HONE
private:
	/** @brief stores the reference date */
	std::string refDate{};
	/** @brief stores the record's location */
	std::string geo{};
	/** @brief stores the DGUID */
	std::string dguid{};
	/** @brief stores the product type */
	std::string productType{};
	/** @brief stores the storage type */
	std::string storageType{};
	/** @brief stores the unit of measurement */
	std::string uom{};
	/** @brief stores the unit of measurement's ID */
	std::string uomId{};
	/** @brief stores the record's scalar factor */
	std::string scalarFactor{};
	/** @brief stores the record's scalar ID */
	std::string scalarId{};
	/** @brief stores the record's location as a vector */
	std::string vector{};
	/** @brief stores the record's location as a coordinate */
	std::string coordinate{};
	/** @brief stores the record's value */
	std::string	value{};
	/** @brief stores the record's status */
	std::string	status{};
	/** @brief stores the record's symbol */
	std::string	symbol{};
	/** @brief stores the record's terminated status */
	std::string terminated{};
	/** @brief stores the record's decimals */
	std::string decimals{};

public:
	/**
	 * @brief No-argument constructor
	*/
	RecordDTO();

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
	RecordDTO(std::string refDate, 
				std::string geo, 
				std::string dguid, 
				std::string productType, 
				std::string storageType, 
				std::string uom, 
				std::string uomId,
				std::string scalarFactor, 
				std::string scalarId, 
				std::string vector, 
				std::string coordinate, 
				std::string value,
				std::string status, 
				std::string symbol, 
				std::string terminated, 
				std::string decimal);
	
	/** Accessor declarations */
	std::string getRefDate();
	std::string getGeo();
	std::string getDguid();
	std::string getProductType();
	std::string getStorageType();
	std::string getUom();
	std::string getUomId();
	std::string getScalarFactor();
	std::string getScalarId();
	std::string getVector();
	std::string	getCoordinate();
	std::string	getValue();
	std::string getStatus();
	std::string getSymbol();
	std::string getTerminated();
	std::string	getDecimals();

	/** Modifier declarations */
	void setRefDate			(std::string newRefDate);
	void setGeo				(std::string newGeo);
	void setDguid			(std::string newDguid);
	void setProductType		(std::string newProductType);
	void setStorageType		(std::string newStorageType);
	void setUom				(std::string newUom);
	void setUomId			(std::string newUomId);
	void setScalarFactor	(std::string newScalarFactor);
	void setScalarId		(std::string newScalarId);
	void setVector			(std::string newVector);
	void setCoordinate		(std::string newCoordinate);
	void setValue			(std::string newValue);
	void setStatus			(std::string newStatus);
	void setSymbol			(std::string newSymbol);
	void setTerminated		(std::string newTerminated);
	void setDecimals		(std::string newDecimals);

	/**
	 * @brief Prints a formatted RecordDTO's information. Used in main() to print a specified number of records. 
	*/
	void printRecord();
};
#endif // !RECORD_DTO_H


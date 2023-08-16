/**
* @file             CST8333_Project_By_Chloe_Lee-Hone
* @author			Chloe Lee-Hone<leeh0002@algonquinlive.com>
* @version			1.0
* @section			This file contains the main function. Prints the specified number of records. 
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

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include "RecordDTO.h"
#include "RecordDAO.h"
#include "RecordConsoleView.h"

/**
 * @brief Starts the program using an instance of the Presentation layer's RecordConsoleView.
 */
int main()
{
    /** Necessary to use the doctest unit testing framework */
    doctest::Context context{};

    RecordConsoleView consoleView{};
    consoleView.showMenu();

    int res = context.run();

    return 0;
}

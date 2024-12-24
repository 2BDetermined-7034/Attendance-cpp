#ifndef DATABASE_HPP
#define DATABASE_HPP


#include <cstdint>
#include <vector>
#include <string>
#include <functional>

class Database;

void readV1(std::ifstream&, Database&);

/*
 * The current version of the Database file format has the following layout:
 *  
 * | Key          | Type     | Info
 * |--------------|----------|-------------------------------------------------
 * | header       | char[4]  | Always is equal to "DB2\0".
 * |--------------|----------|-------------------------------------------------
 * | version      | uint32_t | Currently equal to 0. Please make a copy of this 
 * |              |          | doc in Database.cpp when making a new version.
 * |--------------|----------|-------------------------------------------------
 * | dayCount     | uint32_t | Number of days to store data on.
 * |--------------|----------|-------------------------------------------------
 * | studentCount | uint32_t | Number of students.
 * |--------------|------------------------------------------------------------
 * | studentNames | char[32]        | Names of the students stored as
 * |              | [.studentCount] | "First Last"
 * |---------------------------------------------------------------------------
 * | studentTimes | uint16_t        | Time in seconds as an array for each day.
 * |              | [.dayCount]     | Each student has an array.
 * |              | [.studentCount] |
 * ----------------------------------------------------------------------------
 */
class Database {
public:
	Database(const std::string& filepath);

	~Database();

	struct StudentName {
		char name[32];
	};

	std::vector<StudentName> studentNames;
	std::vector<std::vector<uint16_t>> studentTimes;
	uint32_t dayCount;

private:
	std::string filepath;

	friend void readV1(std::ifstream&, Database&);
};

#endif

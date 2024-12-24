#include "../inc/Database.hpp"

#include <cstring>
#include <iostream>
#include <functional>
#include <fstream>

const std::function<void(std::ifstream&, Database&)> readers[] = {
	readV1
};

Database::Database(const std::string& filepath) {
	this->filepath = filepath;

	std::ifstream file(filepath, std::ios::binary);

	if (!file.is_open()) {
		dayCount = 0;
		std::cerr << "\e[33mWarning:\e[0m Could not open file \"" + filepath + "\": " + std::strerror(errno) << std::endl;
		return;
	}

	char header[4];
	file.read(header, 4);

	if (std::strcmp(header, "DB2")) {
		std::cerr << "\e[31mError:\e[0m File is not a DB2 database file" << std::endl;
		return;
	}

	uint32_t version;
	file.read((char*)&version, 4);

	readers[version](file, *this);
}

Database::~Database() {
	std::ifstream inputFile(filepath);
	std::ofstream outputFile(filepath + ".bak", std::ios::trunc);
	outputFile << inputFile.rdbuf();

	std::ofstream file(filepath, std::ios::trunc);

	if (!file.is_open()) {
		std::cerr << "\e[31mError:\e[0m Could not open file \"" + filepath + "\": " + std::strerror(errno) << std::endl;
		return;
	}

	file.write("DB2", 4);
	const uint32_t version = 0;
	const uint32_t studentCount = studentNames.size();
	file.write((char*)&version, 4);
	file.write((char*)&dayCount, 4);
	file.write((char*)&studentCount, 4);

	file.write((char*)studentNames.data(), studentNames.size() * sizeof(StudentName));
	for (auto& i: studentTimes) {
		file.write((char*)i.data(), i.size() * sizeof(uint16_t));
	}
}

void readV1(std::ifstream& file, Database& database) {
	file.read((char*)&database.dayCount, 4);

	uint32_t studentCount;
	file.read((char*)&studentCount, 4);

	database.studentNames.resize(studentCount);
	file.read((char*)database.studentNames.data(), database.studentNames.size() * sizeof(Database::StudentName));

	database.studentTimes.resize(studentCount);
	for (auto& i: database.studentTimes) {
		i.resize(database.dayCount);
	}
}

#include "../inc/Database.hpp"

int main(int argc, char** argv) {
	std::string filepath = "database.db2";

	if (argc > 1) {
		filepath = argv[1];
	}

	Database database(filepath);

	return 0;
}

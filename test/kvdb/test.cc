#include "UnqliteDB.hh"

int main(int argc, char** argv) {
	UnqliteDB db;
	db.open("1.db", true);
	db.store("mis", 3, "zhumm", 5);

	char v[6]; UInt l;
	db.fetch("mis", 3, v, &l);
	db.close();
	return 0;
}


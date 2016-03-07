#include "UnqliteDB.hh"

int main(int argc, char** argv) {
	UnqliteDB db;
	db.open("1.db", true);

	db.store("mis", 3, "zhumm", 5);
	db.store("mis", 3, "xxxx", 4);

	char v[6]; UInt l;
	db.fetch("mis", 3, v, &l);

	KVCursor* c = db.initCursor();
	c->seek("mis", 3, -1);
	c->data(v, &l);
	c->next();
	c->data(v, &l);

	db.releaseCursor(c);

	db.close();
	return 0;
}


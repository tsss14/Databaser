#include "Database.hpp"
#include <iostream>

int main(void) {
    Database db = Database("testDB");
    db.addTable(Table("Test Table"));
    db.addColumn("Test Table", Column("Test Column", INT, 0));
    db.addColumn("Test Table", Column("Test Column 2", VARCHAR, 20));
    db.addColumn("Test Table", Column("Test Column 3", BOOL, 0));
    db.addField("Test Table", 0, 1, "7");
    db.addField("Test Table", 1, 1, "testing");
    db.addField("Test Table", 2, 1, "true");
    for(auto field: db.getRow("Test Table", 1)) {
        cout<<field<<'\n';
    }
    string* stringTest = db.parseQuery("this=that");

    cout<<stringTest[1]<<'\n';
    delete[] stringTest;
    return 0;
}
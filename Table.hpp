#include "Column.hpp"
#include <vector>
using namespace std;

class Table {
    private:
        string table_name;
        vector<Column> cols;
    public:
        Table(string name) {
            table_name = name;
            cols = {};
        }

        Column getCol(int index) {
            return cols[index];
        }

        string getField(int i, int row_id) {
            return cols[i].getField(row_id);
        }

        int getColumnCount() {
            return cols.size();
        }

        void addColumn(Column column) {
            cols.push_back(column);
        }

        void addField(int column_index, int row_id, string field_as_string) {
            cols[column_index].addField(row_id, field_as_string);
        }

        string getName() {
            return table_name;
        }
};
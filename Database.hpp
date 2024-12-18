#include "Table.hpp"

class Database
{
private:
    string database_name;
    vector<Table> tables;
    int findTableIndex(string table_name)
    {
        for (int i = 0; i != tables.size(); i++)
        {
            if (tables[i].getName() == table_name)
            {
                return i;
            }
        }
        return -1;
    }

    int findColumnIndex(string table_name, string column_name)
    {
        int index = findTableIndex(table_name);
        for (int i = 0; i != tables[index].getColumnCount(); i++)
        {
            Column col = tables[index].getCol(i);
            if (col.getName() == column_name)
            {
                return i;
            }
        }
        return -1;
    }

    vector<int> findRowIndexsofColumn(string table_name, int column_index, string column_value_as_string)
    {
        const Datatype dt = tables[findTableIndex(table_name)].getCol(column_index).getDatatype();
        const Column& col = tables[findTableIndex(table_name)].getCol(column_index);
        vector<int> rowids = col.searchColumn(column_value_as_string);
        return rowids;
    }

public:
    Database(string name)
    {
        database_name = name;
        tables = {};
    }

    void addTable(Table table)
    {
        tables.push_back(table);
    }

    vector<string> getRow(string table_name, int row_id)
    {
        int size = tables[findTableIndex(table_name)].getColumnCount();
        vector<string> returnVal = {};
        for (int i = 0; i != size; i++)
        {
            returnVal.push_back(tables[findTableIndex(table_name)].getField(i, row_id));
        }
        return returnVal;
    }

    vector<vector<string>> getRowWithQuery(string table_name, string query)
    {
        vector<vector<string>> rows{};
        string* tokens = parseQuery(query);
        int column_index = findColumnIndex(table_name, tokens[0]);
        vector<int> rowids = findRowIndexsofColumn(table_name, column_index, tokens[1]);
        for(auto row : rowids) {
            rows.push_back(getRow(table_name, row));
        }
        return rows;
    }

    string *parseQuery(string query)
    {
        if (query.find('=') != string::npos)
        {
            string token1 = query.substr(0, query.find('='));
            string token2 = query.substr(query.find('=') + 1, query.length());
            string *strings = new string[2];
            strings[0] = token1;
            strings[1] = token2;
            return strings;
        }
        else if (query.find('>') != string::npos)
        {
            string token1 = query.substr(0, query.find('>'));
            string token2 = query.substr(query.find('>') + 1, query.length());
            string *strings = new string[2];
            strings[0] = token1;
            strings[1] = token2;
            return strings;
        }
        else if (query.find('<') != string::npos)
        {
            string token1 = query.substr(0, query.find('<'));
            string token2 = query.substr(query.find('<') + 1, query.length());
            string *strings = new string[2];
            strings[0] = token1;
            strings[1] = token2;
            return strings;
        }
        else if (query.find("!=") != string::npos)
        {
            string token1 = query.substr(0, query.find("!="));
            string token2 = query.substr(query.find("!=") + 2, query.length());
            string *strings = new string[2];
            strings[0] = token1;
            strings[1] = token2;
            return strings;
        }
        return nullptr;
    }

    string getColumnName(string table_name, int column_index)
    {
        return tables[findTableIndex(table_name)].getCol(column_index).getName();
    }

    string getField(string table_name, int row_id, int column_index)
    {
        return tables[findTableIndex(table_name)].getField(column_index, row_id);
    }

    void addColumn(string table_name, Column column)
    {
        tables[findTableIndex(table_name)].addColumn(column);
    }

    void addField(string table_name, int column_index, int row_id, string field_as_string)
    {
        tables[findTableIndex(table_name)].addField(column_index, row_id, field_as_string);
    }
};
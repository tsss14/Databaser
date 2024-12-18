#include <string>
#include <map>
#include <vector>
using namespace std;

enum Datatype {
    VARCHAR,
    INT,
    BOOL
};

class Column {
    private:
        string field_name;
        Datatype dt;
        int max_varchar_size;
        map<int, int> intMap;
        map<int, string> varcharMap;
        map<int, bool> boolMap;

    public:
        Column(std::string field_name, Datatype dt, int max_varchar_size) {
            this->field_name = field_name;
            this->dt = dt;
            this->max_varchar_size = max_varchar_size;
        }

        vector<int> searchColumn(string val) const{
            vector<int> rowids{};
            switch(dt) {
                case BOOL:
                    bool b = val == "true";
                    for(auto const& [key, mval] : boolMap ) {
                        if (mval == b) rowids.push_back(key);
                    } 
                    break;
                case INT:
                    int i = stoi(val);
                    for(auto const& [key, mval] : intMap ) {
                        if (mval == i) rowids.push_back(key);
                    } 
                    break;
                case VARCHAR:
                    for(auto const& [key, mval] : varcharMap ) {
                        if (mval == val) rowids.push_back(key);
                    }
                    break;
            }
            return rowids;
        }

        string getName() {
            return field_name;
        }

        Datatype getDatatype() {
            return dt;
        }

        string getField(int row_id) {
            if(dt == VARCHAR) {
                return varcharMap.at(row_id);
            } else if (dt == INT) {
                return to_string(intMap.at(row_id));
            } else {
                if(boolMap.at(row_id)) {
                    return "true";
                } else {
                    return "false";
                }
            }
        }

        void addField(int row_id, string field_as_string) {
            if(dt == VARCHAR) {
                varcharMap.insert({row_id, field_as_string});
            } else if(dt == INT) {
                intMap.insert({row_id, stoi(field_as_string)});
            } else {
                if (field_as_string == "true") {
                    boolMap.insert({row_id, true});
                } else {
                    boolMap.insert({row_id,false});
                }
            }
        }
};
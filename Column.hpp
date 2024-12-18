#include <string>
#include <map>
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

        string getName() {
            return field_name;
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
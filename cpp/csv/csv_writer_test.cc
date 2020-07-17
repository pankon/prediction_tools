#include "csv_writer.h"

int main() {
    std::vector<std::string> vec1 {"a", "b", "c"};
    std::vector<std::string> vec2 {"d", "e", "f"};
    CsvWriter file("file.csv");
    file.Write(vec1);
    file.Write(vec2);
}
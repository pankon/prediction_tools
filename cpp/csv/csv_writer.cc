 
#include <ios>

#include "csv_writer.h"

// opens
CsvWriter::CsvWriter(const std::string& filename) : file(filename.c_str(), std::ios_base::out){
}

// closes, also
CsvWriter::~CsvWriter() {
    file.close();
}

/* super basic, you're required
 * to keep track of your columns
 * yourself
 */
bool CsvWriter::Write(std::vector<std::string>& columns) {
    for (std::vector<std::string>::iterator ptr = columns.begin();
        columns.end() > ptr; 
        ++ptr) {
        file << *ptr << ",";
    }
    file << "\n";
    
    return true;
}
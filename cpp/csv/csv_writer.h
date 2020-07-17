#ifndef CPP_CSV_WRITER_H_
#define CPP_CSV_WRITER_H_

#include <vector>
#include <fstream>

class CsvWriter {
public:
    CsvWriter(const std::string& filename); // opens
    ~CsvWriter(); // closes, also

    /* super basic, you're required
     * to keep track of your columns 
     * yourself
     */
    bool Write(std::vector<std::string>& columns); //todo: make const
private:
    std::fstream file;
};

#endif // CPP_CSV_WRITER_H_
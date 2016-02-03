#include <iostream>
#include <fstream>
#include <tuple>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>


using namespace std;

string fasta_parse(const std::string& infile) {
    string line;
    string header;
    string seq;
    tuple outvalue;
    ifstream f (infile);
    if(!f.is_open())
        perror("Error while opening file");
    while(getline(f, line)) {
        if(boost::starts_with(line, ">")) {
            header = line.substr(line.size());
            boost::trim_right(header);
        } else {
            seq = line;
            boost::trim_right(seq);
        }
    }
}


int main() {

    return 0;
}
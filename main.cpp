#include <iostream>
#include <fstream>
#include <unordered_set>
#include <algorithm>


using namespace std;

string infile = "/home/lakinsm/Documents/phd/phdenv/benchmarking_hmm/final_hmmer_templates.fasta";
int kmer = 16;
unordered_set<string> dbhash;

void hash_entry(string dbseq) {
    for( int i=0; i < dbseq.size() - kmer; i++ ) {
        string temp = dbseq.substr(i, i+kmer);
        dbhash.insert(temp);
        reverse(temp.begin(), temp.end());
        dbhash.insert(temp);
    }
}

int main() {
    // This code block parses the input database and hashes each k-mer
    string line, header, seq;
    ifstream f ( infile );
    if( !f.is_open() )
        perror( "Error while opening file" );
    while( getline( f, line ).good() ) {
        if( line.empty() || line[0] == '>' ){
            if( !header.empty() ){
                hash_entry(seq);
                header.clear();
            }
            if( !line.empty() ){
                header = line.substr(1);
            }
            seq.clear();
        } else if( !header.empty() ){
            if( line.find(' ') != std::string::npos ){
                header.clear();
                seq.clear();
            } else {
                seq += line;
            }
        }
    }
    if( !header.empty() ){
        hash_entry(seq);
    }
    cout << dbhash.size() << endl;
    return 0;
}
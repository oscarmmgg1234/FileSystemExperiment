
#pragma once
#include "../LAB03/FileSys.hpp"

using namespace std;
class Table : public Filesys
{
public: 
    Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile);
    int Build_Table(string input_file);
    int Search(string value);
private:
    string flatfile;
    string indexfile;
    int IndexSearch(string value);
};

Table::Table(string diskname, int blocksize, int numberofblocks, string flatfile, string indexfile) : Filesys(diskname, numberofblocks, blocksize)
{
    this->flatfile = flatfile;
    this->indexfile = indexfile;
    if(Build_Table("db.txt") == 1)
        cout << "Table built successfully" << endl;
    else
        cout << "Table build failed" << endl;
}

int Table::Build_Table(string input_file){
    newFile(flatfile);
    newFile(indexfile);
    ifstream infile;
    infile.open(input_file.c_str());
    ostringstream ostream;
    string rec;
    std::getline(infile, rec);
    while (infile.good())
    {
        string key = rec.substr(0, 5);
        vector<string> b = block(rec);
        int n = addBlock(flatfile, b[0]);
        ostream << key << " " << n << " ";
        getline(infile, rec);
    }
    ostream << "kangaroo"
            << " " << 0 << " "; // sentinel
    string ibuffer = ostream.str();
    vector<string> blocks = block(ibuffer);
    for (int i = 0; i < blocks.size(); i++)
    {
        addBlock(indexfile, blocks[i]);
    }
    return 1;
}

int Table::IndexSearch(string value)
{
    string buffer;
    int b = getFirstBlock("indexFile");
    while (b != 0)
    {
        string buff;
        readBlock(indexfile, b, buff);
        buffer += buff;
        b = nextBlock(indexfile, b);

        istringstream istream(buffer);
        string k;
        int bl; // Assuming 'bl' should be an integer
        while (istream >> k >> bl)
        {
            if (k == value)
                return bl;
        }
    }
    return 0; // Return 0 if the value is not found
}

int Table::Search(string value)
{
    int blockNumber = IndexSearch(value);
    if (blockNumber > 0)
    {
        string block;
        readBlock(flatfile, blockNumber, block);
        return blockNumber;
    }
    else
    {
        return -1;
        // Handle the case where the value is not found
    }
    return blockNumber; // Or any other appropriate return value
}
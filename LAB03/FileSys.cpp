#include <iostream>
#include <cmath>
#include "FileSys.hpp"

using namespace std;
int main()
{
       Sdisk disk1("disk1", 256, 128);
       Filesys fsys("disk1", 256, 128);
       fsys.newFile("file1");
       fsys.newFile("file2");

       string bfile1;
       string bfile2;

       for (int i = 1; i <= 1024; i++)
       {
              bfile1 += "1";
       }

       vector<string> blocks = fsys.block(bfile1);

       int blocknumber = 0;

       for (int i = 0; i < blocks.size(); i++)
       {
              blocknumber = fsys.addBlock("file1", blocks[i]);
       }

       fsys.delBlock("file1", fsys.getFirstBlock("file1"));

       for (int i = 1; i <= 2048; i++)
       {
              bfile2 += "2";
       }

       blocks = fsys.block(bfile2);

       for (int i = 0; i < blocks.size(); i++)
       {
              blocknumber = fsys.addBlock("file2", blocks[i]);
       }

       fsys.delBlock("file2", blocknumber);
}

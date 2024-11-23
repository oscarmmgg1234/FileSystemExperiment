#include "sdisk.hpp"

int main()
{
    Sdisk disk1("test1.txt", 16, 32);
    string block1, block2, block3, block4;


    disk1.putBlock(1, block1);
    disk1.getBlock(1, block1);
    cout << "contents of block 1: " << block1 << endl;

    disk1.getBlock(4, block3);
    cout << "Should be 32 1s : " << block3 << endl;

    disk1.getBlock(8, block4);

    cout << "Should be 32 2s : " << block4 << endl;
    cout << "number of blocks: " << disk1.getNumberOfBlocks() << endl;
    cout << "block size: " << disk1.getBlockSize() << endl;

    return 0;
}

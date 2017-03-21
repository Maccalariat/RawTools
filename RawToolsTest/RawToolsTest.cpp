#include "../RawToolsLib/include/RawTools.hpp"

#include <iostream>
#include <memory>
#include <src/ProcessBlock.hpp>

int main(int argc, char *argv[]) {
    std::cout << "started test" << std::endl;
    if (argv[1] == "") {
        std::cout << "no file provided" << std::endl;
        return -1;
    }
    std::cout << "supplied file : " << argv[1] << std::endl;
    RawTools *rt = new RawTools();
    ProcessBlock *pb = rt->getProcessBlock();
    rt->processBlock->filename.assign(argv[1]);
    rt->getMetaData();
    rt->getBeyer();
}

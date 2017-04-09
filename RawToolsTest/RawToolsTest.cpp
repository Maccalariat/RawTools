#include "../RawToolsLib/include/RawTools.hpp"


#include <iostream>
#include <string>
int main(int argc, char *argv[]) {
    std::cout << "started test" << std::endl;
    if (argv[1] == "") {
        std::cout << "no file provided" << std::endl;
        return -1;
    }
    std::string fn(argv[1]);
    std::cout << "supplied file : " << argv[1] << std::endl;
    RawTools *rt = new RawTools();
    rt->setFile(fn);
    rt->getMetaData();
    rt->getBeyer();
    rt->writeFile("sony1.tiff");
    rt->close_file();

}

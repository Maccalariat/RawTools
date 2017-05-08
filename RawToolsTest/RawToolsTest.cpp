#include "../RawToolsLib/include/RawTools.hpp"


#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::cout << "started test" << std::endl;
    /* if (argv[1] == "") {
        std::cout << "no file provided" << std::endl;
        return -1;
    }
    std::string fn(argv[1]);
    std::cout << "supplied file : " << argv[1] << std::endl;
     */
    std::string fn("E:\\projects\\CPP\\RawTools\\sony1.ARW");
    RawTools *rt = new RawTools();
    rt->setFile(fn);
    rt->parseMetaData();
    auto bm = rt->getBeyer();
    rt->getInterpolated(0, bm);
    rt->writeFile("sony1.tiff");
    rt->close_file();
	
}

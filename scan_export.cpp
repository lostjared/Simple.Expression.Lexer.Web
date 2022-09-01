#include<emscripten.h>
#include<emscripten/bind.h>

#include"scan_lex.hpp"
#include<sstream>

class ScanExport {
public:

    ScanExport() {}

    std::string scanLex(std::string src) {
        scan::Scanner scanner(src);
        scan::Token token;
        std::ostringstream stream;
        stream << "<table border=\"1\">\n";
        stream << "<tr><th>Index</th><th>Token</th><th>Type</th></tr>\n";
        int index = 1;
        scanner.scan();
        while(scanner.nextToken(token)) {
            stream << "<tr><th>" << index << "<th>" << token.token << "</th><th>" << token.type << "</th></tr>\n";
            index++;
        }
        stream << "</table>\n";
        return stream.str();
    }

};

using namespace emscripten;
using namespace scan;

EMSCRIPTEN_BINDINGS(my_Scan) {
    class_<ScanExport>("Scan")
        .constructor()
        .function("scanLex", &ScanExport::scanLex)
    ;
}
#include <fstream>
#include <iostream>

#include <md_to_doc/parsers/json/JSONParser.h>

#include "md_to_doc/parsers/md/MDParser.h"

#include <string>
#include <streambuf>
#include <iterator>


bool equal_files(const std::string &a, const std::string &b) {
    std::ifstream stream{a};
    std::string file1{
        std::istreambuf_iterator<char>(stream),
        std::istreambuf_iterator<char>()
    };

    stream = std::ifstream{b};
    std::string file2{
        std::istreambuf_iterator<char>(stream),
        std::istreambuf_iterator<char>()
    };

    return file1 == file2;
}

int main() {
    std::ifstream in("/workspaces/md-to-doc/test.md", std::ios_base::in);
    md_parser::MdParser mparser;
    Document md = mparser.parse(in);
    in.close();

    nlohmann::json json = md.to_json();
    std::ofstream out("/workspaces/md-to-doc/test.json", std::ios_base::out);
    out << json.dump(4);
    out.close();

    std::ifstream in2("/workspaces/md-to-doc/test.json", std::ios_base::in);
    json_parser::JSONParser json_parser;
    Document jd = json_parser.parse(in2);
    in2.close();

    json = jd.to_json();
    std::ofstream out2("/workspaces/md-to-doc/test2.json", std::ios_base::out);
    out2 << json.dump(4);
    out2.close();

    std::cout << equal_files("/workspaces/md-to-doc/test.json", "/workspaces/md-to-doc/test2.json") << std::endl;
    return 0;
}

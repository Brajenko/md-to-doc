#ifndef PARSER_H
#define PARSER_H
#include "md_to_doc/elements/Document.h"


class Parser {
public:
    virtual ~Parser() = default;

    virtual Document parse(std::istream &input_stream) = 0;
};


#endif //PARSER_H

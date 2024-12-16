cmake_minimum_required(VERSION 3.30)
project(md_to_doc)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

include_directories("${CMAKE_SOURCE_DIR}/include")

add_executable(md_to_doc main.cpp
        src/md_to_doc/elements/Element.cpp
        include/md_to_doc/elements/Element.h
        src/md_to_doc/elements/Text.cpp
        include/md_to_doc/elements/Text.h
        include/md_to_doc/elements/Paragraph.h
        include/md_to_doc/elements/CodeBlock.h
        include/md_to_doc/elements/ElementContainer.h
        src/md_to_doc/elements/Header.cpp
        include/md_to_doc/elements/Header.h
        include/md_to_doc/elements/List.h
        include/md_to_doc/elements/Blockquote.h
        src/md_to_doc/elements/Table.cpp
        include/md_to_doc/elements/Table.h
        include/md_to_doc/elements/HorizontalRule.h
        include/md_to_doc/elements/Document.h
        include/md_to_doc/parsers/Parser.h
        src/parsers/md/MDParser.cpp
        include/md_to_doc/parsers/md/MDParser.h
        src/md_to_doc/elements/Paragraph.cpp
        src/md_to_doc/elements/Blockquote.cpp
        src/md_to_doc/elements/CodeBlock.cpp
        src/md_to_doc/elements/Document.cpp
        src/md_to_doc/elements/HorizontalRule.cpp
        src/md_to_doc/elements/List.cpp
        src/md_to_doc/elements/TableHeaders.cpp
        include/md_to_doc/elements/TableHeaders.h
        src/parsers/json/JSONParser.cpp
        include/md_to_doc/parsers/json/JSONParser.h
)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(duckx CONFIG REQUIRED)
target_link_libraries(md_to_doc PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(md_to_doc PRIVATE duckx::duckx)

find_package(Catch2 3 REQUIRED)
include(CTest)
include(Catch)

enable_testing()

add_executable(tests tests/elements/test_text.cpp
        src/md_to_doc/elements/Element.cpp
        include/md_to_doc/elements/Element.h
        src/md_to_doc/elements/Text.cpp
        include/md_to_doc/elements/Text.h
        include/md_to_doc/elements/Paragraph.h
        include/md_to_doc/elements/CodeBlock.h
        include/md_to_doc/elements/ElementContainer.h
        src/md_to_doc/elements/Header.cpp
        include/md_to_doc/elements/Header.h
        include/md_to_doc/elements/List.h
        include/md_to_doc/elements/Blockquote.h
        src/md_to_doc/elements/Table.cpp
        include/md_to_doc/elements/Table.h
        include/md_to_doc/elements/HorizontalRule.h
        tests/elements/test_element.cpp
        tests/elements/test_header.cpp
        tests/elements/test_paragraph.cpp
        include/md_to_doc/elements/Document.h
        tests/elements/test_elementcontainer.cpp
        include/md_to_doc/parsers/Parser.h
        src/parsers/md/MDParser.cpp
        include/md_to_doc/parsers/md/MDParser.h
        tests/parsers/test_mdparser.cpp
        src/md_to_doc/elements/Paragraph.cpp
        src/md_to_doc/elements/Blockquote.cpp
        src/md_to_doc/elements/CodeBlock.cpp
        src/md_to_doc/elements/Document.cpp
        src/md_to_doc/elements/HorizontalRule.cpp
        src/md_to_doc/elements/List.cpp
        src/md_to_doc/elements/TableHeaders.cpp
        include/md_to_doc/elements/TableHeaders.h
        tests/elements/test_horizontalrule.cpp
        tests/elements/test_blockquote.cpp
        tests/elements/test_codeblock.cpp
        tests/elements/test_list.cpp
        tests/elements/test_table.cpp
        src/parsers/json/JSONParser.cpp
        include/md_to_doc/parsers/json/JSONParser.h
        tests/elements/test_document.cpp
        tests/parsers/test_jsonparser.cpp
        tests/test_end2end.cpp

)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(tests PRIVATE duckx::duckx)



catch_discover_tests(tests)

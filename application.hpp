#pragma once
#include <boost/program_options.hpp>

class Application
{
    int _ac;
    char** _av;
    boost::program_options::options_description _desc;
public:
    Application(int argc, char* argv[]);
    int exec();
};

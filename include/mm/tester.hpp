#pragma once

#include "mm/problem/reader.hpp"

#include <stdexcept>


namespace MM
{

namespace TesterImpl
{

struct CommandLineException;
struct BadCommandLineArguments;
struct CommandLineHelp;

}  // namespace TesterImpl


template <class Element>
class Tester
{
public:
    Tester(int argc, char* argv[]);
    virtual ~Tester() = default;

    const Problem::Reader<Element>& problem() const;

    class Timer;
    Timer timer() &;

private:
    std::filesystem::path m_result_path;
    Problem::Reader<Element> m_reader;

    std::chrono::high_resolution_clock::duration m_duration;
};

}  // namespace MM


#include "mm/tester/private/tester.ipp"

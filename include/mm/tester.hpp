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
    std::chrono::high_resolution_clock::duration m_duration;

public:
    Tester(int argc, char* argv[]);
    virtual ~Tester() = default;

    const Problem::Reader<Element>& problem() const;

    class Timer;
    Timer timer() &;

    std::chrono::high_resolution_clock::duration get_duration() const { return m_duration; }

private:
    std::filesystem::path m_result_path;
    Problem::Reader<Element> m_reader;
};

}  // namespace MM


#include "mm/tester/private/tester.ipp"

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
    std::filesystem::path m_problem_path, m_result_path;
    std::chrono::high_resolution_clock::duration m_elapsed;

public:
    Tester(int argc, char* argv[]);
    virtual ~Tester() = default;

    const Problem::Reader<Element>& problem() const;

    class Timer;
    Timer timer() &;

    auto elapsed() const { return m_elapsed; }
    auto problem_file_path() const { return m_problem_path; }
    auto result_file_path() const { return m_result_path; }

private:
    Problem::Reader<Element> m_reader;
};

}  // namespace MM


#include "mm/tester/private/tester.ipp"

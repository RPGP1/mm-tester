#pragma once

#include "mm/tester.hpp"

#include <cmdline.h>

#include <chrono>
#include <filesystem>


namespace MM
{

namespace TesterImpl
{

struct CommandLineException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct BadCommandLineArguments : public CommandLineException {
    explicit BadCommandLineArguments(cmdline::parser const&);
};

struct CommandLineHelp : public CommandLineException {
    explicit CommandLineHelp(cmdline::parser const&);
};

}  // namespace TesterImpl


template <class Element>
class Tester<Element>::Timer final
{
    explicit Timer(Tester<Element>&);
    ~Timer();

    Timer(Timer const&) = delete;
    Timer& operator=(Timer const&) = delete;

    friend class Tester<Element>;

    Tester<Element>& m_tester;
    std::chrono::high_resolution_clock::time_point m_begin_time;
};


template <class Element>
Tester<Element>::Tester(int argc, char* argv[])
    : m_reader{[&] {
          namespace fs = std::filesystem;

          cmdline::parser parser;

          parser.add<fs::path>("problem",
              'p',
              "path to problem file or directory containing some",
              true);
          parser.add<fs::path>("result",
              'r',
              "path to the result file",
              false, "result.dat");

          if (!parser.parse(argc, argv)) {
              throw TesterImpl::BadCommandLineArguments{parser};
          } else if (parser.exist("help")) {
              throw TesterImpl::CommandLineHelp{parser};
          }

          m_result_path = parser.get<fs::path>("result");

          return parser.get<fs::path>("problem");
      }()},
      m_duration{std::chrono::high_resolution_clock::duration::max()}
{
}

template <class Element>
const Problem::Reader<Element>& Tester<Element>::problem() const
{
    return m_reader;
}

template <class Element>
auto Tester<Element>::timer() & -> Timer
{
    return Timer{*this};
}


template <class Element>
Tester<Element>::Timer::Timer(Tester<Element>& tester)
    : m_tester{tester}, m_begin_time{std::chrono::high_resolution_clock::now()}
{
}

template <class Element>
Tester<Element>::Timer::~Timer()
{
    m_tester.m_duration = std::chrono::high_resolution_clock::now() - m_begin_time;
}

}  // namespace MM

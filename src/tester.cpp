#include "mm/tester.hpp"

namespace MM
{

namespace TesterImpl
{

BadCommandLineArguments::BadCommandLineArguments(cmdline::parser const& parser)
    : CommandLineException{parser.error_full() + "\n" + parser.usage()}
{
}

CommandLineHelp::CommandLineHelp(cmdline::parser const& parser)
    : CommandLineException{parser.usage()}
{
}

}  // namespace TesterImpl

}  // namespace MM

# include "utils/io_helpers.hpp"


void clear_line()
{
    std::cout << "\r\x1b[0J";
}

void clear_lines(int line_count)
{
    OUTF("\x1b[{}A", line_count - 1);
    clear_line();
}


std::vector<std::string> splitString(std::string& input, char delimiter)
{
    std::vector<std::string> tokens;
    int tokenStart = 0;

    for (int i = 0; i <= input.size(); i++)
    {
        if (input[i] == delimiter || input[i] == '\0')
        {
            tokens.emplace_back(input.substr(tokenStart, i - tokenStart));
            tokenStart = i + 1;
        }
    }
    return tokens;
}

void removeCharacterInstances(std::string& input, char target)
{
    input.erase(
        std::remove(input.begin(), input.end(), target),
        input.end()
    );
}
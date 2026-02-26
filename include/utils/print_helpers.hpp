# pragma once
# ifndef PRINT_MACROS
# define PRINT_MACROS

# define PRINT(line) std::cout << line << std::endl;
# define PRINTERR(line) std::cerr << line << std::endl;
# define CLEAR_PRINT() std::cout << "\x1b[1A" << "\x1b[2K\r";
# define STR(in) (std::ostringstream() << in).str();

void clear_line()
{
    std::cout << "\r\x1b[K";
}

void clear_lines(int line_count)
{
    std::cout << "\x1b[2K";
    for (int i = 1; i < line_count; i++)
        std::cout << "\x1b[1A" << "\x1b[2K";
    std::cout << "\r";
}

# endif
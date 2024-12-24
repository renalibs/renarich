#include<iostream>

#define RENARICH_USE_ANSI

#include"rena/renarich.h"

int main(){
    std::cout << rena::bcolor::BRIGHTWHITE << rena::fcolor::BLACK << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::BLACK << rena::fcolor::RED << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::RED << rena::fcolor::GREEN << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::GREEN << rena::fcolor::YELLOW << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::YELLOW << rena::fcolor::BLUE << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::BLUE << rena::fcolor::MAGENTA << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::MAGENTA << rena::fcolor::CYAN << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::CYAN << rena::fcolor::WHITE << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::WHITE << rena::fcolor::GRAY << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::GRAY << rena::fcolor::BRIGHTRED << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::BRIGHTRED << rena::fcolor::BRIGHTGREEN << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::BRIGHTGREEN << rena::fcolor::BRIGHTYELLOW << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::BRIGHTYELLOW << rena::fcolor::BRIGHTBLUE << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::BRIGHTBLUE << rena::fcolor::BRIGHTMAGENTA << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::BRIGHTMAGENTA << rena::fcolor::BRIGHTCYAN << "Hello World!" << rena::rich_reset << std::endl;
    std::cout << rena::bcolor::BRIGHTCYAN << rena::fcolor::BRIGHTWHITE << "Hello World!" << rena::rich_reset << std::endl;
    return 0;
}

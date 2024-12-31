#include<iostream>

#include"rena/renarichxx.h"

int main(){
    rena::panel p( "First Line" );
    p.style( rena::panel::s_no_title | rena::panel::s_no_subtitle );
    std::cout << p << std::endl;

    p.style( rena::panel::s_frame_double_line | rena::panel::s_title );
    p.title( "This is a really long example title" );
    p.push_line( "Second line: use double line frame" );
    std::cout << p << std::endl;

    p.style( rena::panel::s_frame_heavy_single_line );
    p.pop_line();
    p.push_line( "[cyan]Second line (new): use heavy single line frame" );
    std::cout << p << std::endl;

    p.style( rena::panel::s_subtitle | rena::panel::s_frame_rounded );
    p.title( "[brightblue,bold]Title" );
    p.subtitle( "[dim]New Rounded Frame" );
    p.frame_color( rena::fcolor::RED );
    p.push_line( "[italic,underline,overline,magenta]Third line: a bit complicated" );
    std::cout << p << std::endl;

    return 0;
}

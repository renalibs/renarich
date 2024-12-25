#include"rena/renarichxx.h"

int main(){
    rena::rprintf( R"([byellow][red]Hello %s![/][illegal tag]Background color should still be yellow![/]
This tag \[red] shouldn't be prased but [brightblue]here should be blue[/].)" , "World" );
    rena::rprintf( R"(
If you're using a terminal supports ANSI escape codes you should see the following styles, which are:
[bold]bold[/],
[dim]dim[/],
[italic]italic[/],
[overline,underline]overline & underline[//],
[strike]strike[/],
and [reverse]reverse[/].
If your terminal doesn't support them, sadly you won't see anything.)" );
    return 0;
}

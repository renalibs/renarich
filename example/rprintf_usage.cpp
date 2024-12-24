#include"rena/renarichxx.h"

int main(){
    rena::rprintf( R"([byellow][red]Hello %s![/][illegal tag]Background color should still be yellow![/]
This tag \[red] shouldn't be prased but [brightblue]here should be blue[/].)" , "World" );
    return 0;
}

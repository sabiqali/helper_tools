#include <iostream>
#include <string>
#include <algorithm>

int main() {

    std::string comp = "*||||||***|***|| *|***||******||*| |  |*|||*|  |||*|**|**||**||  **||  | |*|| |*||||||||||||||| *||*|| |  *|*||| | |||| |**|||  ||*|||**|**|| | || |*|*|  ||*|||*| |||*|*| ||*";

    std::size_t n = std::count(comp.begin(),comp.end(),'|');

    std::cout<<n<<std::endl<<comp.length()<<std::endl<<(n*100/comp.length())<<"%";

    return 0;

}

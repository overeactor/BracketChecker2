#include <iostream>
int main() {
    std::string data = "{[(test)]}";
    /* Block comment with fake brackets {
       still in comment
    } */
    if (data.size() > 0) {
        std::cout << data << std::endl;
    }
    return 0;
}

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

std::vector<std::string> tokenize(std::string const & str, std::string const & delim = " ") {
    std::vector<std::string> tokens;
    size_t last = 0;
    size_t found = str.find(delim);
    while (found != std::string::npos) {
        tokens.push_back(str.substr(last, found - last));
        last = found + 1;
        found = str.find(delim, last);
    }

    tokens.push_back(str.substr(last));

    return tokens;
}

void callback1() {
    std::cout << "callback 1" << std::endl;
}

void callback2(std::string const & str) {
    std::cout << "callback 2 with '" << str << "'" << std::endl;
}

void callbackDemo(
    std::vector<std::string> const & tokens,
    std::string const & target,
    void (*callback1)(),
    void (*callback2)(std::string const &))
{
    for (auto && t : tokens) {
        if (t == target) {
            (*callback1)();
            (*callback2)(t);
        }
    }
}

int main() {

    auto tokens = tokenize("Hello there world, how are you?");

    callbackDemo(tokens, "world,", callback1, callback2);

    return EXIT_SUCCESS;
}

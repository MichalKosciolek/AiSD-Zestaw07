#include <fstream>
#include "Dict.hpp"

int main(int argc, char* argv[]){
    if (argc < 2) {
        std::cerr << "Bledna liczba argumentow" << std::endl;
        return 1;
    }

    Dict<std::string, std::string> dict;
    std::ifstream file (argv[1]);
    std::string key, value;

    if(file.is_open()){
        while(file >> key){
            file >> value;
            std::pair<std::string, std::string> p = std::make_pair(key, value);
            dict.insert(p);
        }
        file.close();
    }

    std::ofstream output ("out.txt");
    if(output.is_open()) {
        while (std::cin >> key) {
            if (dict.find(key)) {
                //std::cout << dict[key] << std::endl;
                output << dict[key] << std::endl;
            } else
                //std::cout << "-" << std::endl;
                output << "-" << std::endl;
        }
    }
    output.close();
    return 0;
}
#include "Program.h"
#include <iostream>


// main.cpp. Inputs .txt file and assigns string file name. Exports data to Prog.cpp. Executes
// error checking to ensure correct file type. Initalise program and catch any errors in the
// program class. Errorneous input BASIC programs are terminated after catching the exception with EXIT_FAILURE.

int main (int argc, char* argv[]) {
    if (argc != 2){
        std::cerr << "Invalid command line arguments" << std::endl;
        std::cerr << "Usage: " << argv[0] << "myBasicProgram.txt" << std::endl;
        return EXIT_FAILURE;
    }
    
    auto filename = argv[1];
    
    try{
        Program program { filename };
        program.Run();
    }
    catch (std::exception const& e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

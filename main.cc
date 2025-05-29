// #include "RedBlackTree.hh"
#include "RBT.h"

//std
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>

//main
int main(int argc, char** argv)
{
    RedBlackTree rbt;

    // // Inserting elements
    // rbt.insert(10);
    // rbt.insert(20);
    // rbt.insert(30);
    // rbt.insert(15);
    
    std::ifstream inputStream("../in.txt");
    std::string line;

    std::string operacao;
    std::string auxValor;
    int valor;


    std::ofstream clearOut;
    clearOut.open("../out.txt", std::ofstream::out | std::ofstream::trunc);
    clearOut.close();

    while (getline(inputStream, line)) 
    {
        if(line.length() < 5)
        {
            std::cerr << "Invalid command! Skipping...\n";
            getline(inputStream, line);
        }

        operacao = line.substr(0, 3);
        auxValor = line.substr(4, line.length()-1);
        valor = std::stoi(auxValor);

        if (operacao=="SUC")
        {
            // std::cout << "SUC is WIP!\n";
            // std::cout << std::numeric_limits<double>::infinity() << std::endl;
            std::cout << rbt.findSuccessor(valor) << "\n";
        }
        else if(operacao=="INC")
        {
            rbt.insert(valor);
        }
        else if(operacao=="REM")
        {
            // if(rbt.RemoveNoArvBMais(valor))
            // {
            //     std::string line;

            //     int numberOperations = 0;
            //     std::string nomeArquivo = std::to_string(valor)+".txt";
            //     std::ifstream textStream(nomeArquivo);

            //     std::ofstream output;
            //     output.open("out.txt",std::ofstream::app);

            //     while (getline(textStream, line)) 
            //     {
            //         numberOperations++;
            //     }
            //     output << "REM:" << numberOperations << std::endl;
            //     output.close();

            //     std::ofstream clearArq;
            //     clearArq.open(nomeArquivo, std::ofstream::out | std::ofstream::trunc);
            //     clearArq.close();

            // }
            rbt.remove(valor);
            std::cout << "REM is WIP!\n";
        }
        else if(operacao=="IMP")
        {
            std::cout << "IMP is WIP!\n";
            std::ofstream output;
            output.open("../out.txt",std::ofstream::app);
            rbt.printTreeWithDepthAndColor(output);
            output.close();
        }
        else 
        {
            std::cerr << "Invalid command! Skipping...\n";
        }
        
    }

    return EXIT_SUCCESS;
}



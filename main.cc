// #include "RedBlackTree.hh"
#include "RBT.h"

//std
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string& s, std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

//main
int main(int argc, char** argv)
{
    RedBlackTree rbt;

    std::ifstream inputStream("../in.txt");
    std::string line;

    std::string operacao;
    std::string auxString;
    std::vector<std::string> auxVec;
    std::string delim = " ";

    int valor;
    int rbtVer;


    std::ofstream clearOut;
    clearOut.open("../out.txt", std::ofstream::out | std::ofstream::trunc);
    clearOut.close();

    std::ofstream output;
    output.open("../out.txt",std::ofstream::app);
    while (getline(inputStream, line)) 
    {
        if(line.length() < 5)
        {
            std::cerr << "Invalid command! Skipping...\n";
            getline(inputStream, line);
        }

        operacao = line.substr(0, 3);
        auxString = line.substr(4, line.length()-1);

        if (operacao=="SUC")
        {
            auxVec = split(auxString,delim);

            valor = std::stoi(auxVec[0]);
            rbtVer = std::stoi(auxVec[1]);

            output << line << "\n";
            rbt.findSuccessor(output, valor, rbtVer);
        }
        else if(operacao=="INC")
        {
            valor = std::stoi(auxString);
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
            valor = std::stoi(auxString);
            rbt.remove(valor);
            // std::cout << "REM is WIP!\n";
        }
        else if(operacao=="IMP")
        {
            // std::cout << "IMP is WIP!\n";
            rbtVer = std::stoi(auxString);
            rbt.printTreeWithDepthAndColor(output, rbtVer);
        }
        else 
        {
            std::cerr << "Invalid command! Skipping...\n";
        }
        
    }

    output.close();
    return EXIT_SUCCESS;
}



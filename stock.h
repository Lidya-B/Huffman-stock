//*******************************************************************************************************
//
//		File:					Huffmanstock.cpp
//
//		This program uses the Huffman Tree to crate and display stocks.
//	
//		
//			
//*******************************************************************************************************

#ifndef STOCK_H
#define STOCK_H

//*******************************************************************************************************

#include <string>
using namespace std;

//*******************************************************************************************************

class Stock {
public:
    string name;
    string symbol;
    double price;
    double frequency;

  
    Stock(const string& n = "", const string& s = "", double p = 0.0, double f = 0.0)
        : name(n), symbol(s), price(p), frequency(f) {}
};

//*****************************************************************************************************

#endif // STOCK_H


//*******************************************************************************************************
//
//		File:					Huffmanstock.cpp
//
//		This program uses the Huffman Tree to crate and display stocks.
//	
//		
//			
//*******************************************************************************************************

#include "node.h"
#include "stock.h"
#include <string>
#include <fstream>
#include <iostream>

//*******************************************************************************************************

using namespace std;

//*******************************************************************************************************

int readStocks(const string& fileName, Stock*& stocks, double*& freqs)
{
    ifstream file(fileName);
    if (!file.is_open()) 
    {
        cerr << "Error opening file " << fileName << endl;
        return 0;
    }

    int numStocks;
    file >> numStocks; 

    
    stocks = new Stock[numStocks];
    freqs = new double[numStocks];

    for (int i = 0; i < numStocks; ++i)
    {
        file.ignore(); 
        getline(file, stocks[i].name);
        file >> stocks[i].symbol >> stocks[i].price >> freqs[i];
    }

    file.close();
    return numStocks;
}

//*******************************************************************************************************

Node<Stock>* createHuffmanTree(Stock stocks[], double freqs[], int size)
{
    Node<Stock>** elements = new Node<Stock>*[size];
    for (int i = 0; i < size; ++i)
    {
        elements[i] = new Node<Stock>(stocks[i], freqs[i]);
    }

    while (size > 1) 
    {
        int min1 = 0, min2 = 1;
        if (elements[min1]->data.frequency > elements[min2]->data.frequency)
        {
            swap(min1, min2);
        }
        for (int i = 2; i < size; ++i) 
        {
            if (elements[i]->data.frequency < elements[min1]->data.frequency) 
            {
                min2 = min1;
                min1 = i;
            }
            else if (elements[i]->data.frequency < elements[min2]->data.frequency) 
            {
                min2 = i;
            }
        }

        Node<Stock>* newNode = new Node<Stock>(Stock(), elements[min1]->data.frequency + elements[min2]->data.frequency);

        newNode->left = elements[min1];
        newNode->right = elements[min2];

        swap(elements[min1], elements[size - 1]);
        swap(elements[min2], elements[size - 2]);
        elements[size - 2] = newNode;

        size--;
    }

    return elements[0];
}

//*******************************************************************************************************

void printArray(int path[], int pathLen, Node<Stock>* leaf) 
{
    cout << "Path: ";
    for (int i = 0; i < pathLen; ++i) 
    {
        cout << path[i];
    }
    cout << ", Stock: " << leaf->data.name << " (" << leaf->data.symbol << ")" << endl;
}

//*******************************************************************************************************

void printPaths(Node<Stock>* node, int path[], int pathLen, int lr) 
{
    if (node == nullptr)
    {
        return;
    }

    path[pathLen] = lr;
    pathLen++;

    if (node->left == nullptr && node->right == nullptr) 
    {
        printArray(path, pathLen, node);
    }
    else 
    {
        printPaths(node->left, path, pathLen, 0);
        printPaths(node->right, path, pathLen, 1);
    }
}

//*******************************************************************************************************

void displayStockList(Node<Stock>* rootPtr, const string& sentence) 
{
    Node<Stock>* curr = rootPtr;
    cout << "Stocks: ";
    for (char bit : sentence)
    {
        if (bit == '0') 
        {
            curr = curr->left;
        }
        else if (bit == '1') 
        {
            curr = curr->right;
        }

        if ((curr->left == nullptr) && (curr->right == nullptr))
        {
            cout << curr->data.symbol << " ";
            curr = rootPtr; 
        }
    }
    cout << endl;
}

//*******************************************************************************************************

int main() 
{
    string fileName = "HuffmanStocks.txt";
    Stock* stocks;
    double* freqs;
    int numStocks = readStocks(fileName, stocks, freqs);

    if (numStocks == 0)
    {
        cout << "No stocks found!" << endl;
        return 1;
    }

    Node<Stock>* root = createHuffmanTree(stocks, freqs, numStocks);

    int path[100]; 
    printPaths(root, path, 0, -1);

    string sentence = "1001010101";
    displayStockList(root, sentence);

    delete[] stocks;
    delete[] freqs;

    return 0;
}

//*******************************************************************************************************
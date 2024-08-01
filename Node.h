//*******************************************************************************************************
//
//		File:					Huffmanstock.cpp
//
//		This program uses the Huffman Tree to crate and display stocks.
//	
//		
//			
//*******************************************************************************************************

#ifndef NODE_H
#define NODE_H

//*******************************************************************************************************

template <class T>
struct Node 
{
    T data;
    double frequency;
    Node<T>* left;
    Node<T>* right;

    
    Node(T d, double freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

//*****************************************************************************************************

#endif // NODE_H

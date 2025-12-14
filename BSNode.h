#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

using namespace std;

template <typename T> 
class BSNode {
    public:
        T* elem;    //Elemento almacenado en el nodo
        BSNode<T>* left;    //Puntero a lado Izq
        BSNode<T>* right;   //Puntero a lado Dch

        BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* right=nullptr):elem(elem),left(nullptr),right(nullptr) {}

        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn){
            out<< bsn.elem;
            return out;
        }
};

#endif
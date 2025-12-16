
#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T> 
class BSTree {
    private:
        int nelem; //Numero de elementos almacenados
        BSNode<T>* root; //Nodo raiz

        //Busqueda
        BSNode<T>* searchNode(BSNode<T>* n, T e) const{
            if (n == nullptr) {
                throw runtime_error("Elemento no encontrado");
            }
            
            if (e == n->elem) {
                return n;
            }

            if(e < n->elem){
                return searchNode(n->left, e);
            }

            return searchNode(n->right, e);

        }

        //Insertar
        BSNode<T>* insert(BSNode<T>* n, T e){
            if(n==nullptr){
                return new BSNode<T>(e);
            }
            if(n->elem==e){
                throw runtime_error("El elemento ya existe");
            }
            if(e < n->elem){
                n->left = insert(n->left, e);
            }
            if(e > n->elem){
                n->right = insert(n->right, e);
            }

            return n;
        }

        //Recorrido
        void print_inorder(ostream &out, BSNode<T>* n) const{
            if(n != nullptr) {
				print_inorder(out, n->left); //Imprimir primero el lado izq
				out << n->elem << " ";
				print_inorder(out, n->right); //Depues imprimie el lado dch
			}
        }
        
        //Eliminacion de elementos

        T max(BSNode<T>* n) const{
            if(n==nullptr){
                throw runtime_error("Árbol vacío");
            }
            if(n->right==nullptr){
                return n->elem;
            }
            return max(n->right);
        }

        BSNode<T>* remove_max(BSNode<T>* n){
            if (n == nullptr) {
                throw runtime_error("Árbol vacío");
            }
            
            if (n->right == nullptr) {
                BSNode<T>* leftChild = n->left;

                delete n;
                return leftChild;
            }

            n->right = remove_max(n->right); //Elimina el max
            return n; //Recoloca el resto
        }

        BSNode<T>* remove(BSNode<T>* n, T e){

            if (n == nullptr) {
                throw runtime_error("Elemento no encontrado");
            }
            
            if (e < n->elem) {
                n->left = remove(n->left, e);
                return n;
            }

            else if (e > n->elem) {
                n->right = remove(n->right, e);
                return n;
            }
            
            else {
                // Encontramos el nodo a eliminar (e == n->elem)
                // Caso 1: Nodo con un solo hijo

                if (n->left == nullptr) {
                    BSNode<T>* rightChild = n->right;

                    delete n;
                    return rightChild;
                } 

                else if (n->right == nullptr) {
                    BSNode<T>* leftChild = n->left;

                    delete n;
                    return leftChild;
                } 
                
                // Caso 2: Nodo con dos hijos
                else {
                    // Reemplazar por el máximo del subárbol izquierdo
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);

                    return n;
                }
            }
        }

        void delete_cascade(BSNode<T>* n){
            if(n!=nullptr){
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }

    public:

        BSTree(): nelem(0),root(nullptr){}

        int size()const{
            return nelem;
        }

        //Busqueda
        T search(T e) const{
            BSNode<T>* aux = searchNode(root, e);
            return aux->elem;
        }

        T operator[](T e) const{
            return search(e);
        }

        //Insertar
        void insert(T e){
            root = insert(root, e);
            nelem++;
        }


        //Recorrido
        friend ostream& operator<<(ostream &out, const BSTree<T> &bst){
            bst.print_inorder(out,bst.root);
            return out;
        }

        //Eliminación de elementos
        void remove(T e){
            root=remove(root,e);
            nelem--;
        }

        //Destrucción
        ~BSTree(){
            delete_cascade(root);
        }
    
};

#endif
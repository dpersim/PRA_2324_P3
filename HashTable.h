#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!

using namespace std;


template <typename V>
class HashTable: public Dict<V> {

    private:
        int n; //elementos almacenados
        int max; //Tamño tabla
        ListLinked<TableEntry<V>>* table; //Tabla que alamcena valores y claves

        //calcula la clave
        int h(string key){
            int ASCIIsum=0;
            for(char c : key){
                ASCIIsum+=int(c);
            }
            return (ASCIIsum % max);
        }

    public:
        HashTable(int size): n(0),max(size),table(new ListLinked<TableEntry<V>>[size]){}
        ~HashTable(){
            delete []table;
        }
        int capacity(){
            return max;
        }
        friend ostream& operator<<(ostream &out, const HashTable<V> &th){
            for(int i=0;i<th.max;i++){
		out<<"=== Cubeta "<< i <<" ==="<<endl;
                out<<th.table[i]<<endl;
            }
            return out;
        }
        V operator[](string key){
            return search(key);
        }
        void insert(string key, V value) override{
            int index = h(key);
            TableEntry<V> newEntry(key, value);
            
            // Buscar si ya existe la clave
            int pos = table[index].search(newEntry);

            if(pos != -1){
                throw runtime_error("Ya hay una entrada con esa clave");
            }
            
            // Insertar en la tabla
            table[index].append(newEntry);
            n++;
        }

        V search(string key) override{
            int index = h(key);
            TableEntry<V> tempEntry(key); // Crea TableEntry solo con la clave para buscar
            
            int pos = table[index].search(tempEntry);
            if(pos == -1){
                throw runtime_error("La clave no existe");
            }
            
            TableEntry<V> foundEntry = table[index].get(pos);
            return foundEntry.value;
        }
        
        V remove(string key) override{
            int index = h(key);
            TableEntry<V> tempEntry(key); // Crea TableEntry solo con la clave para buscar
            
            int pos = table[index].search(tempEntry);
            if(pos == -1){
                throw runtime_error("La clave no existe");
            }
            
            TableEntry<V> removedEntry = table[index].remove(pos);
            n--;
            return removedEntry.value;
        }
        int entries()override{
            return n;
        }
};

#endif

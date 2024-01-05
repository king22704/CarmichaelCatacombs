/*
 * hashmap.h
 * REDACTED
 * REDACTED
 * December 9, 2023
 *
 * Hashmap which lets the user hash arbitrary hashable elements with arbitrary
 * Keys. Indexing syntax identical to std::unordered_map. Uses chaining to deal
 * With collisions.
 */

#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <string>
#include <utility>
#include <iostream>

template<typename K, typename V>
class hashmap {

    private:
        // hashNode keeps track of key and value and next node in chain
        struct hashNode{
            hashNode *next;
            K key;
            V value;
        };

        hashNode **array;
        int size, capacity;
        std::hash<K> getIndex;

        /*
        * name:      addNode
        * purpose:   adds a new node to our hashmap with key, value
        * arguments: Key of type K, value of type V to add
        * returns:   none
        * effects:   adds a
        */
        void addNode(K &key, V &value) {
            // get hashed
            int index = getIndex(key) % capacity;
            // adds (Key, value) with pointer to old first value in chain
            array[index] = makeNode(key, value, array[index]);
            size++;
        }

        /*
        * name:      expand
        * purpose:   expand array when it reaches requisite load factor
        * arguments: none
        * returns:   none
        * effects:   underlying array is now expanded and values are rehashed
        */
        void expand() {
            size = 0;
            capacity = capacity * 2;
            hashNode *temp, *at;
            hashNode **newArray = new hashNode*[capacity]();
            hashNode **oldArray = array;
            array = newArray;

            // looks at all possible indices
            for (int i = 0; i < capacity / 2; i++) {
                // loop through all elements in chain of index i in old array
                at = oldArray[i];
                // TODO: add rehash chain
                while (at != nullptr){
                    // and add them to our new expanded array
                    addNode(at->key, at->value);
                    temp = at;
                    at = at->next;
                    // free heap memory after getting pointer to next
                    delete temp;
                }

            }
            // free memory from old array
            delete [] oldArray;
        }

        /*
        * name:      makeNode
        * purpose:   make a new hashNode with key and value, with next pointer
        * arguments: key, value, next item in chain
        * returns:   new hashnode with proper value
        * effects:   none
        */
        hashNode* makeNode(K &key, V &value, hashNode *next){
            hashNode *node = new hashNode;

            node->key = key;
            node->value = value;
            node->next = next;

            return node;
        }

        /*
        * name:      delete chain
        * purpose:   free all memory associated with chain starting at node
        * arguments: node with associated chain we want to free memory of
        * returns:   none
        * effects:   frees memory of node
        */
        void deleteChain(hashNode *node) {
            // if it's the nullptr, no more memory to free
            if (node == nullptr){
                return;
            }

            hashNode *temp = node->next;
            // free memory
            delete node;
            // whoo, tail recursive, so compiler optimized
            deleteChain(temp);
        }


    public:

        /*
        * name:      hashmap constructor
        * purpose:   create empty hashmap with capacity
        * arguments: none
        * returns:   none
        * effects:   none
        */
        hashmap() {
            size = 0;
            capacity = 1;
            // THANK YOU https://stackoverflow.com/questions/2615071/!!!!!!!!!
            array = new hashNode*[capacity]();
        }

        /*
        * name:      hashmap destructor
        * purpose:   free all memory associated with hashmap
        * arguments: none
        * returns:   none
        * effects:   none
        */
        ~hashmap(){
            // delete all chains in hashmap (including those of size 1)
            for (int i = 0; i < capacity; i++) {
                deleteChain(array[i]);
            }
            // delete underlying array
            delete [] array;
        }

        /*
        * name:      is indexed
        * purpose:   checks if key is in hashmap
        * arguments: key to check
        * returns:   boolean of whether key is in hashmap
        * effects:   none
        */
        bool isIndexed(K &key) {
            // get first element of chain at proper location
            hashNode *node = array[getIndex(key) % capacity];

            while (node != nullptr){
                // if we've found the proper key
                if (node->key == key){
                    return true;
                }
            }
            // otherwise key is not in hashmap
            return false;
        }

        /*
        * name:      fancy schmancy bracket operator
        * purpose:   add key value pairs to hashmap or find a value with a key
        * arguments: key to check
        * returns:   the dereferenced address of the value
        * effects:   none
        */
        V &operator[](K key) {
            int index = getIndex(key) % capacity;

            if (array[index] != nullptr) {
                hashNode *node = array[index];
                // TODO: consider making finding a value given a key a function
                // look for key in hashmap and return value if key exists
                while (node != nullptr){
                    if (node->key == key){
                        return node->value;
                    }
                    node = node->next;
                }
            }

            // TODO: Mess with load-factor maybe to see if it's better
            // otherwise, if we need to expand given load factor, do it
            if ((size / double(capacity)) > 0.75){
                expand();
            }
            // and add node to front of keys chain with uninitialized value
            V value;
            array[index] = makeNode(key, value, array[index]);
            // don't forget to make size bigger!
            size++;
            return array[index]->value;
        }
};

#endif

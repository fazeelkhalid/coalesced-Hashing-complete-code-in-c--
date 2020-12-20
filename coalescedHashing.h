#define coalescedHashing_h
#include<iostream>
using namespace std;

//template for generic type 
template<typename K, typename V>
 
struct HashNode {
	//Hashnode struct data type
	V value;
	K key;
	HashNode<V, K> *next;
	//Constructor of hashnode 
	HashNode(K key, V value) {
		this->value = value;
		this->key = key;
		next = NULL;
	}
};

//template for generic type 
template<typename K, typename V>

//Our own Hashmap class 
class HashMap {
	//hash element array 
	HashNode<K, V> **arr;
	int capacity;
	//current size 
	int size;
	void expand() { // if capacity become full it will expand the table
		capacity = capacity + capacity;
		size = 0;
		HashNode<K, V> **temp = arr;
		arr = new HashNode<K, V>*[capacity];
		//Initialise all elements of array as NULL 
		
		for (int i = 0; i < capacity; i++) {
			arr[i] = NULL;
		}

		for (int i = 0; i < capacity - 20; i++) {
			if (temp[i] != NULL) { // hash index not NULL
				this->insertNode(temp[i]->key, temp[i]->value);
			}
		}

		for (int i = 0; i < capacity - 20; i++) {
			delete temp[i];
		}
		delete temp;
	}
	int emptySpace() { // find empty space from bottom
		int index = capacity - 1;
		int i = 1;
		int j = 0;
		for (; j < capacity && arr[index] != NULL && arr[index]->key >= 0 && index >= 0; j++) {
			index = capacity - (i*i);

			while (index < 0) {
				index = (capacity-1) + index;
			}
			i++;
		}
		if (j != capacity) { // resolve collision
			return index;
		}
		else {
			cout << "\nNot possible to solve collision :( ";
			return - 1;
		}
	}

public:
	HashMap() {
		//Initial capacity of hash array 
		capacity = 20;
		size = 0;
		arr = new HashNode<K, V>*[capacity];

		//Initialise all elements of array as NULL 
		for (int i = 0; i < capacity; i++) {
			arr[i] = NULL;
		}
	}
	// This implements hash function to find index 
	// for a key 
	int hashCode(K key) {
		return key % capacity;
	}

	//Function to add key value
	void insertNode(K key, V value) {
		HashNode<K, V> *temp = new HashNode<K, V>(key, value);

		// Apply hash function to find index for given key 
		int hashIndex = hashCode(key);

		//cout << arr[hashIndex];
		//if current node all ready fill
		if (arr[hashIndex] != NULL && (arr[hashIndex]->key == key || arr[hashIndex]->key != -1)) {
			HashNode<K, V> *tempNode = arr[hashIndex];
			hashIndex = emptySpace(); // find the empty node from the last
			if (hashIndex != -1) { // not possible to enter key or resolve collision
				while (tempNode->next != NULL && tempNode->key >= 0) { // find the last node that empty of the collision;
					tempNode = tempNode->next;
				}
				tempNode->next = temp;
				arr[hashIndex] = temp;
				size++;
			}
		}
		else {
			arr[hashIndex] = temp;
			size++;
		}
		if (size == capacity - 2) {
			expand();
		}
	}

	//Function to delete a key value pair 
	void deleteNode(K key) {
		// Apply hash function to find index for given key 
		int hashIndex = hashCode(key);

		//if node found 
		if (arr[hashIndex] != NULL && arr[hashIndex]->key == key) {
			HashNode<K, V> *temppre = arr[hashIndex];
			HashNode<K, V> *temp = arr[hashIndex];
			
			while (temp->next != NULL && temp->next->key != -1) {
					temppre = temp;
					temp->key = temp->next->key;
					temp->value = temp->next->value;
					temp = temp->next;
			}
			temp->key = -1;
			temp->value = -1;
			temppre->next = NULL;
			temp = NULL;
			// Reduce size s
			size--;
		}
	}

	//Function to search the value for a given key 
	bool search(K key) { // return bool value means present or not
		int hashIndex = hashCode(key);// Apply hash function to find index for given key 
		int counter = 0;
		//finding the node with given key
		HashNode<K, V> *temp = arr[hashIndex];
		if (temp == NULL) {
			return false;
		}
		while (temp->next != NULL) {
			if (temp->key == key) { // if key present in closed Chain
				return true;
			}
			temp = temp->next;
		}
		if (temp->key == key) {
			return true;
		}
		return false;
	}

	void setvalue() {

	}

	//Return current size 
	int sizeofMap()
	{
		return size;
	}

	//Return true if size is 0 
	bool isEmpty()
	{
		return size == 0;
	}

	//Function to display the stored key value pairs 
	void display()
	{
		for (int i = 0; i < capacity; i++)
		{
			if (arr[i] != NULL && arr[i]->key >= 0) {
				cout << "\n___________________________________________________________________________________________\n";
				cout << "Hash index : " << i << "    | Address : " << arr[i];
				cout << "   | key = " << arr[i]->key << "    | value = " << arr[i]->value << "    | next Pointer : " << arr[i]->next << endl;
			}
		}
	}
	~HashMap() {
		for (int i = 0; i < capacity; i++) {
			delete arr[i];
		}
		delete arr;
	}
};

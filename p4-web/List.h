#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  List(){
    listSize = 0;
    first = nullptr;
    last = nullptr;
  }

  List(const List &other){
    listSize = 0;
    first = nullptr;
    last = nullptr;
    copy_all(other);
  }

  ~List(){
    clear();
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    if(first == nullptr){
      return true;
    }
    else{
      return false;
    }
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const{
    return listSize;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    Node* temp = new Node;
    temp->datum = datum;
    temp->next = first;
    temp->prev = nullptr;
    
    if(!empty()){
      first->prev = temp;
      first = temp;
    }
    else{
      first = temp;
      last = temp;
    }
    listSize++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node* temp = new Node;
    temp->datum = datum;
    temp->next = nullptr;
    temp->prev = last;
    
    if(!empty()){
      last->next = temp;
      last = temp;
    }
    else{
      first = temp;
      last = temp;
    }
    listSize++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    assert(!empty());
    Node* temp = new Node;
    if(first == last){
      temp = first;
      first = nullptr;
      last = nullptr;
      
    }
    else{
      temp = first;
      first = first->next;
      first->prev = nullptr;
      
    }
    delete temp;
    listSize--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    assert(!empty());
    Node* temp = new Node;
    if(first == last){
      temp = first;
      first = nullptr;
      last = nullptr;
      
    }
    else{
      temp = last;
      last = last->prev;
      last->next = nullptr;
      
    }
    delete temp;
    listSize--;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    while(!empty()){
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  int listSize;

  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    for(Node* ptr = other.first; ptr != nullptr; ptr = ptr->next){
      push_back(ptr->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.

    Iterator(){
      node_ptr = nullptr;
    }

    Iterator& operator--() {
      
      node_ptr = node_ptr->prev;
      return *this;
    }

    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    T& operator*() const{ 
      assert(node_ptr);
      return node_ptr->datum;
    }

    bool operator==(Iterator rhs) const{
      return node_ptr == rhs.node_ptr;
    }

    bool operator!=(Iterator rhs) const{
      return node_ptr != rhs.node_ptr;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;
    // construct an Iterator at a specific position
    Iterator(Node *p){
      node_ptr = p;
    }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
    if(i == Iterator(first)){
      pop_front();
    }
    else if(i == Iterator(last)){
      pop_back();
    }
    else{
      Node* temp = i.node_ptr;
      i.node_ptr->next->prev = i.node_ptr->prev;
      i.node_ptr->prev->next = i.node_ptr->next;
      delete temp;
      listSize--;
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
    if(i == Iterator(first)){
      push_front(datum);
    }
    else if(i == Iterator()){
      push_back(datum);
    }
    else{
      Node* temp = new Node;
      temp->datum = datum;
      temp->next = i.node_ptr;
      temp->prev = i.node_ptr->prev;
      i.node_ptr->prev->next = temp;
      i.node_ptr->prev = temp;
      listSize++;
    }
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.

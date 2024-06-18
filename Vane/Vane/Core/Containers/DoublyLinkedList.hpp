#pragma once 

namespace Vane {
  template <class T>
  class DoublyLinkedList {
  public: 
    struct Node {
      T data;
      Node* next;
      Node* previous;
    };
    Node* head;

  public: 
    DoublyLinkedList();

    void insert(Node* previousNode, Node* newNode);
    void remove(Node* deleteNode);

  private:
    DoublyLinkedList(DoublyLinkedList &doublyLinkedList);
  };


}

#include "DoublyLinkedListImpl.hpp"
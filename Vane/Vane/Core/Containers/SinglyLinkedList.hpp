#pragma once

namespace Vane {
template <class T>
class SinglyLinkedList {
public: 
  struct Node {
    T data;
    Node* next;
  };

  Node* head;

public: 
  SinglyLinkedList();

  void Insert(Node* previousNode, Node* newNode);
  void Remove(Node* previousNode, Node* deleteNode);
};

#include "SinglyLinkedListImpl.hpp"

}
#pragma once

namespace Vane {
template <class T>
class StackLinkedList {
public:
  struct Node {
    T data;
    Node* next;
  };

  Node* head;

public:
  StackLinkedList() = default;
  StackLinkedList(const StackLinkedList& other) = delete;
  void push(Node* newNode);
  Node* pop();
};

}


#include "StackLinkedListImpl.hpp"
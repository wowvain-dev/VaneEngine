#include "SinglyLinkedList.hpp"

namespace Vane {
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {}

template <class T>
void SinglyLinkedList<T>::Insert(Node* previousNode, Node* newNode) {
  if (previousNode == nullptr){
    // Is the first node?
    if (head != nullptr){
       newNode->next = head;
    } else {
      newNode -> next = nullptr;
    }

    head = newNode;
  } else {
    if (previousNode->next == nullptr) {
      previousNode->next = newNode;
      newNode->next = nullptr;
    } else {
      newNode->next = previousNode->next;
      previousNode->next = newNode;
    }
  }
}

template <class T>
void SinglyLinkedList<T>::Remove(Node* previousNode, Node* deleteNode) {
  if (previousNode == nullptr){
    if (deleteNode->next == nullptr) {
      head = nullptr;
    } else {
      head = deleteNode->next;
    }
  }
}
}
#include "DoublyLinkedList.hpp"

namespace Vane {

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {}


template <class T>
void DoublyLinkedList<T>::insert(Node* previousNode, Node* newNode) {
  if (previousNode == nullptr){
    // Is the first node?
    if (head != nullptr){
       newNode->next = head;
       newNode->next->previous = newNode;
    } else {
      newNode -> next = nullptr;
    }
    head = newNode;
    head->previous = nullptr;
  } else {
    if (previousNode->next == nullptr) {
      previousNode->next = newNode;
      newNode->next = nullptr;
    } else {
      newNode->next = previousNode->next;
      if (newNode->next != nullptr) {
        newNode->next->previous = newNode;
      }
      previouosNode->next = newNode;
      newNode->previous = previousNode;
    }
  }
}

template <class T>
void DoublyLinkedList<T>::remove(Node* deleteNode) {
  if (deleteNode->previous == nullptr){
    if (deleteNode->next == nullptr) {
      head = nullptr;
    } else {
      head = deleteNode->next;
      head->previous = nullptr;
    }
  } else {
    if (deleteNode->next == nullptr) {
      deleteNode->previous->next = nullptr;
    } else {
      deleteNode->previous->next = deleteNode->next;
      deleteNode->next->previous = deleteNode->previous;
    }
  }
}
}
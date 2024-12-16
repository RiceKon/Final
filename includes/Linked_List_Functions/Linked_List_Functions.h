#include <iostream>
#include "../node/node.h"
using namespace std;

// Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE> *head)
{
   while (head != nullptr)
   {
      cout << head->_item << " ";
      head = head->_next;
   }
   cout << endl;
}

// recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head)
{
   if (head == nullptr)
      return;
   _print_list_backwards(head->_next);
   cout << head->_item << " ";
}

// return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_search_list(node<ITEM_TYPE> *head, ITEM_TYPE key)
{
   while (head != nullptr)
   {
      if (head->_item == key)
         return head;
      head = head->_next;
   }
   return nullptr;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this)
{
   return head = new node<ITEM_TYPE>(insert_this, head);
}

// insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_after(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this)
{
   if (after_this == nullptr)
      return _insert_head(head, insert_this);
   return after_this->_next = new node<ITEM_TYPE>(insert_this, after_this->_next, after_this);
}

// insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_before(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *before_this, ITEM_TYPE insert_this)
{
   if (before_this == nullptr)
      return _insert_head(head, insert_this);
   return before_this->_prev = new node<ITEM_TYPE>(insert_this, before_this, before_this->_prev);
}

// ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_previous_node(node<ITEM_TYPE> *head, node<ITEM_TYPE> *prev_to_this)
{
   if (prev_to_this == nullptr)
   {
      cout << "ERROR: _previous_node() with a NULL node" << endl;
      return nullptr;
   }

   return prev_to_this->_prev;
}

// delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *delete_this)
{
   if (delete_this == nullptr)
      return ITEM_TYPE();

   if (head == delete_this)
      head = head->_next;

   if (delete_this->_next != nullptr)
      delete_this->_next->_prev = delete_this->_prev;

   if (delete_this->_prev != nullptr)
      delete_this->_prev->_next = delete_this->_next;

   ITEM_TYPE temp = delete_this->_item;

   delete delete_this;

   return temp;
}

// duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE> *head)
{
   if (head == nullptr)
      return nullptr;

   node<ITEM_TYPE> *temp = new node<ITEM_TYPE>(head->_item);

   node<ITEM_TYPE> *last = temp;

   head = head->_next;

   while (head != nullptr)
   {
      last = last->_next = new node<ITEM_TYPE>(head->_item, nullptr, last);
      head = head->_next;
   }
   return temp;
}

// duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
   if (src == nullptr)
      return nullptr;
   dest = new node<T>(src->_item);
   node<T> *last = dest;
   src = src->_next;
   while (src != nullptr)
   {
      last = last->_next = new node<T>(src->_item, nullptr, last);
      src = src->_next;
   }
   return last;
}

// delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE> *&head)
{
   while (head != nullptr)
   {
      node<ITEM_TYPE> *temp = head;
      head = head->_next;
      delete temp;
   }
}

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE &_at(node<ITEM_TYPE> *head, int pos)
{
   if (pos < 0)
      throw "ERROR: _at() with a negative position";
   while (pos > 0 && head != nullptr)
   {
      head = head->_next;
      pos--;
   }
   if (head == nullptr)
      throw "ERROR: _at() went past the end of the list";
   return head->_item;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE> // insert
node<ITEM_TYPE> *_insert_sorted(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending = true)
{
   node<ITEM_TYPE> *temp = _where_this_goes(head, item, ascending);
   return _insert_before(head, temp, item);
}

// insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted_and_add(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending = true)
{
   node<ITEM_TYPE> *temp = _where_this_goes(head, item, ascending);
   if (temp != nullptr && temp->_item == item)
      return temp;
   return _insert_before(head, temp, item);
}
// node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_where_this_goes(node<ITEM_TYPE> *head, ITEM_TYPE item, bool ascending = true)
{
   if (head == nullptr)
      return nullptr;
   if (ascending)
   {
      while (head->_next != nullptr && head->_next->_item < item)
         head = head->_next;
   }
   else
   {
      while (head->_next != nullptr && head->_next->_item > item)
         head = head->_next;
   }
   return head;
}
// Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_last_node(node<ITEM_TYPE> *head)
{
   if (head == nullptr)
      return nullptr;
   while (head->_next != nullptr)
      head = head->_next;
   return head;
} // never use this function.
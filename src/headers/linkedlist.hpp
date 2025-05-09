#ifndef linkedlist_hpp
#define linkedlist_hpp

#include <stddef.h>

template <class T>
class LinkedListIterator;
template <class T>
class LinkedListType;

template <class T>
class NodeType {
public:
	NodeType * next;
	T data;
	inline NodeType() {
		next = nullptr;
	}
	inline NodeType(T myData) {
		next = nullptr;
		data = myData;
	}
};

template <class T>
class LinkedListType {
private:
	NodeType<T> * head;

public:
	inline LinkedListType() ///< Generates empty linked list
	{ head = nullptr; return; }
	inline LinkedListType(T data) ///< Generates single-entry linked list
	{
		head = new NodeType<T>(data);
		return;
	}
	inline NodeType<T> * find_end() ///< Finds last entry of linked list
	{
		NodeType<T> * end = head;
		///< Find whatever item is directly before the nullptr at the end of the linked list
		if (end != nullptr)
			while (end->next != nullptr) {
				end = end->next;
			}
		return end;
	}
	inline NodeType<T> * find_index(size_t index) ///< Finds entry at index of linked list
	{
		NodeType<T> * node = head;
		///< Iterate to item; if any items till then are null, return nullptr.
		if (node != nullptr) {
			for (size_t i = 0; i < index && node != nullptr; i++) {
				node = node->next;
			}
		}
		return node;
	}
	inline void insert_end(T data) ///< Inserts entry at end of linked list
	{
		NodeType<T> * end = find_end();
		///< Find the end of the list. If end exists, add a new node on top and make it the end.
		if (end != nullptr) {
			end->next = new NodeType<T>(data);
			end = end->next;
		} else if (head == nullptr){
			head = new NodeType<T>(data);
		}
		return;
	}
	inline void insert_head(T data) ///< Inserts entry at head of linked list
	{
		NodeType<T> * oldHead = head;
		head = new NodeType<T>(data);
		head->next = oldHead;
		return;
	}
	inline void delete_index(size_t index) ///< Deletes entry at index of linked list
	{
		NodeType<T> * before = nullptr;
		NodeType<T> * after = nullptr;
		///< Find entry just before index, then entry just after. Delete entry at index, then patch up the hole.
		if (index != 0) {
			before = find_index(index - 1);
			if (before != nullptr && before->next != nullptr) {
				after = before->next->next;
				delete before->next;
				before->next = after;
			}
		} else if (head != nullptr){
			after = head->next;
			delete head;
			head = after;
		}
		return;
	}
	inline void delete_all() ///< Deletes all entries of linked list
	{
		NodeType<T> * newHead = head;
		///< Until the end is reached, delete the head and appoint a new head.
		while (newHead != nullptr) {
			newHead = newHead->next;
			delete head;
			head = newHead;
		}
		return;
	}
	inline ~LinkedListType() ///< Sets off delete_all upon list deletion
	{
		delete_all();
		return;
	}
	inline void delete_head() ///< Deletes entry at head of linked list
	{
		NodeType<T> * after = nullptr;
		///< Delete head and set it to next in line.
		if (head != nullptr) {
			after = head->next;
			delete head;
			head = after;
		}
		return;
	}
	inline void delete_end() ///< Deletes entry at end of linked list
	{
		NodeType<T> * before = head;
		///< Find the node just before last, then delete the last and set next of the new last node to nullptr.
		while (before != nullptr
				&& before->next != nullptr
				&& before->next->next != nullptr) {
			before = before->next;
		}
		if (before != nullptr) if (before->next != nullptr) {
			delete before->next;
			before->next = nullptr;
		} else {
			delete before;
			before = nullptr;
		}
		return;
	}
	inline T& operator[](size_t index) ///< Finds data of entry at index
	{
		return find_index(index)->data;
	}
	inline size_t size() {
		NodeType<T> * node = head;
		size_t i = 0;
		while (node != nullptr) {
			node = node->next;
			i++;
		}
		return i;
	}
	friend LinkedListIterator<T>::LinkedListIterator(LinkedListType<T> &);
};

template <class T>
class LinkedListIterator {
private:
	NodeType<T> * head;
	NodeType<T> * current;
	size_t index;
public:
	inline LinkedListIterator() {
		head = nullptr;
		current = nullptr;
		index = 0;
		return;
	}
	inline LinkedListIterator(LinkedListType<T>& list) {
		head = list.head;
		current = head;
		index = 0;
		return;
	}
	inline ~LinkedListIterator() { return; }
	inline void operator++() {
		if (current != nullptr) {
			current = current->next;
			index++;
		}
		return;
	}
	inline void begin() {
		current = head;
		return;
	}
	inline void end() {
		if (current != nullptr) while (current->next != nullptr) {
			current = current->next;
			index++;
		}
		return;
	}
	inline void setHead(NodeType<T> * newHead) {
		head = newHead;
	}
	inline T getHead() {
		T value;
		current = head;

		if (head != nullptr) value = head->data;
		return value;
	}
	inline T getEnd() {
		T value;
		end();
		if (current != nullptr) value = current->data;
		return value;
	}
	inline T get() {
		T value;
		if (current != nullptr)
			value = current->data;
		return value;
	}
	inline void indexOf(size_t myIndex) {
		current = head;
		for (size_t i = 0; i < myIndex && current != nullptr; i++) {
			current = current->next;
			index++;
		}
		return;
	}
	inline T get(size_t myIndex) {
		T value;
		indexOf(myIndex);
		if (current != nullptr)
			value = current->data;
		return value;
	}
	inline void set(T myData) {
		current->data = myData;
		return;
	}
	inline T& operator[](size_t myIndex) {
		indexOf(myIndex);
		return current->data;
	}
	inline size_t getIndex() {
		return index;
	}
};

#endif

#ifndef linkedlist_hpp
#define linkedlist_hpp

template <class T>
struct NodeType {
	NodeType * next;
	T data;
};

template <class T>
class LinkedListType {
private:
	NodeType<T> * head;

public:
	inline LinkedListType() { head = nullptr; return; }
	inline LinkedListType(T data) {
		head = new NodeType<T>;
		head->data = data;
		head->next = nullptr;
		return;
	}
	inline NodeType<T> find_end() {
		NodeType<T> * end = head;
		if (end != nullptr)
			while (end->next != nullptr) {
				end = end->next;
			}
		return end;
	}
	inline NodeType<T> find_index(size_t index) {
		NodeType<T> * node = head;
		if (node != nullptr) {
			for (size_t i = 0; i < index && node != nullptr; i++) {
				node = node->next;
			}
		}
		return node;
	}
	inline void insert_end(T data) {
		NodeType<T> * end = find_end();
		if (end != nullptr) {
			end->next = new NodeType<T>;
			end = end->next;
			end->next = nullptr;
			end->data = data;
		}
		return;
	}
	inline void insert_head(T data) {
		NodeType<T> * oldHead = head;
		head = new NodeType<T>;
		head->next = oldHead;
		head->data = data;
		return;
	}
	inline void delete_index(size_t index) {
		NodeType<T> * before = nullptr;
		NodeType<T> * after = nullptr;
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
	inline ~LinkedListType() {
		NodeType<T> * oldHead = nullptr;
		NodeType<T> * newHead = head;
		while (newHead != nullptr) {
			oldHead = newHead;
			newHead = newHead->next;
			delete oldHead;
		}
		return;
	}
	inline void delete_head() {
		NodeType<T> * after = nullptr;
		if (head != nullptr) {
			after = head->next;
			delete head;
			head = after;
		}
		return;
	}
	inline void delete_end() {
		NodeType<T> * before = head;
		while (before != nullptr && before->next != nullptr && before->next->next != nullptr) {
			before = before->next;
		}
		delete before->next;
		before->next = nullptr;
		return;
	}

};

#endif

//
// Created by 123yt on 11/06/2018.
//
#ifndef HW3_LIST_H
#define HW3_LIST_H
//TODO: all of this

class ElementNotFound : public std::runtime_error {
public:
    ElementNotFound() : std::runtime_error("Element not found") {}
};

template<class T>
class List {
    class Node{
        T* data;
        Node* next;
        Node* prev;

    public:
        Node();
        Node(const T& data);
        Node(const Node& node);
        //Node& operator=(const Node& node) = delete;
        ~Node();
        void setNext(Node* const node);
        void setPrev(Node* const node);
        Node* getNext() const;
        Node* getPrev() const;
        T& nodeData();
    };

    Node* head;
    Node tail;
    int size;

public:
    //constructors/destructor
    List();
    List(const List& list);
    List& operator=(const List& list);
    ~List();

    //iterator is a pointer to a node
    class Iterator;
    friend class Iterator;
    class Iterator{

        const List* list_ptr;
        List::Node* node_ptr;
        //iterator constructor is hidden as it should only be used
        //by begin() and end()
        Iterator(List<T>::Node* node_ptr, const List* list_ptr);
        friend class List;
    public:
        //constructors/destructor
        //Iterator();
        //Iterator(const Iterator& iter);
        //Iterator& operator=(const Iterator& iter);
        ~Iterator(){}

        //operators for iterator
        Iterator& operator++();
        Iterator& operator--();
        Iterator operator++(int);
        Iterator operator--(int);

        T& operator*();
        const T& operator*() const;

        bool operator==(const Iterator& iter) const;
        bool operator!=(const Iterator& iter) const;
    };

    //returns iterator to the beginning/ending of list
    Iterator begin() const;
    Iterator end() const;

    //add object to position before iterator
    //throw ElementNotFound() if iterator doesnt point to current list
    void insert(const T& data, Iterator iterator);
    //insert to list end
    void insert(const T& data);
    //remove object from list at iterators position
    //throw ElementNotFound if iterator points to list end
    void remove(Iterator iterator);

    //find first object in list for which the predicate()
    //function returns true
    template <typename Predicate>
    Iterator find(const Predicate& predicate) const;

    //sort list according to the compare() function
    template <typename Compare> void sort(const Compare& compare);

    int getSize() const;
    bool operator==(const List& list) const;
    bool operator!=(const List& list) const;

private:
    //swap function swaps between the objects at iterator and iterator 2
    //positions. used by sort.
    //throws ElementNotFound if any iterator is at list end
    //iterators stay at same relative list position after swap
    void swap(Iterator& iterator, Iterator& iterator2);
};


/**Iterator functions*/

template <class T>
List<T>::Iterator::Iterator(List<T>::Node*  node_ptr, const List<T>* list_ptr)
        : list_ptr(list_ptr), node_ptr(node_ptr){

}
template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator++(){

    this->node_ptr = this->node_ptr->getNext();
    return *this;
}
template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator--(){

    this->node_ptr = this->node_ptr->getPrev();
    return *this;
}
template <class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {

    List<T>::Iterator temp = Iterator(*this);
    ++(*this);
    return temp;
}
template <class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {

    List<T>::Iterator temp = Iterator(*this);
    --(*this);
    return temp;
}

template <class T> T& List<T>::Iterator::operator*(){

    return this->node_ptr->nodeData();
}
template <class T> const T& List<T>::Iterator::operator*() const{

    return this->node_ptr->nodeData();
}

template <class T>
bool List<T>::Iterator::operator==(const List<T>::Iterator& iter) const{
    return (this->node_ptr == iter.node_ptr &&
            this->list_ptr == iter.list_ptr);
}
template <class T>
bool List<T>::Iterator::operator!=(const List<T>::Iterator& iter) const{
    return !(*this == iter);
}

/**End of iterator functions*/

/**Node functions*/

template <class T> List<T>::Node::Node()
        :data(nullptr), next(nullptr), prev(nullptr) {}
template <class T> List<T>::Node::Node(const T& data)
        :next(nullptr), prev(nullptr){
    T *value = new T;
    *value = data;
    this->data = value;
}
template <class T> List<T>::Node::Node(const Node& node) {

    this->next = node.next;
    this->prev = node.prev;
    if (node.data != nullptr) {
        T *value = new T;
        *value = *node.data;
        this->data = value;
    }
    else {
        this->data = nullptr;
    }
}

template <class T> List<T>::Node::~Node() {
    if (this->data != nullptr) {
        delete this->data;
    }
}

template <class T> void List<T>::Node::setNext(Node* const node) {
    this->next = node;
}
template <class T> void List<T>::Node::setPrev(Node* const node) {
    this->prev = node;
}

template <class T> typename List<T>::Node* List<T>::Node::getNext() const{
    return this->next;
}
template <class T> typename List<T>::Node* List<T>::Node::getPrev() const{
    return this->prev;
}

template <class T> T& List<T>::Node::nodeData() {

    if (this->data == nullptr) {
        throw ElementNotFound();
    }
    return *(this->data);
}
/**End of Node functions*/

/**List functions*/

template <class T> List<T>::List()
        :tail(Node()), size(0){
    head = &tail;
}

template <class T> List<T>::List(const List& list)
        :tail(Node()), size(0){
    head = &tail;
    for (Iterator iter = list.begin(); iter != list.end(); iter++) {
        insert(&iter, end());
    }
}

template <class T> List<T>& List<T>::operator=(const List& list){

    if (this == &list) {
        return *this;
    }
    while (getSize()>0) {
        remove(begin());
    }
    for (List<T>::Iterator iter = list.begin(); iter != list.end(); iter++) {
        insert (&iter, end());
    }
    return *this;
}

template <class T> List<T>::~List() {

    while (getSize()>0) {
        remove(begin());
    }
}

template <class T> typename List<T>::Iterator List<T>::begin() const {

    return Iterator(this->head, this);
}
template <class T> typename List<T>::Iterator List<T>::end() const {

    Iterator iter = begin();
    while (iter.node_ptr != &this->tail) {
        iter++;
    }
    return iter;
}

template <class T> void List<T>::insert(const T& data,Iterator iterator){
    if (this != iterator.list_ptr) {
        throw ElementNotFound();
    }
    size++;
    Node* node = new Node(data);
    Node* next = iterator.node_ptr;

    if (iterator == begin()) {
        node->setNext(next);
        next->setPrev(node);
        this->head = node;
        return;
    }

    Node* prev = iterator.node_ptr->getPrev();

    node->setNext(next);
    node->setPrev(prev);
    next->setPrev(node);
    prev->setNext(node);
    return;
}
template <class T> void List<T>::insert(const T& data){
    this->insert(data, begin());
}
template <class T> void List<T>::remove(Iterator iterator) {


    if (this != iterator.list_ptr) {
        throw ElementNotFound();
    }
    if(iterator == end()){
        throw ElementNotFound();
    }
    size--;
    Node* next = iterator.node_ptr->getNext();

    if (iterator == begin()) {
        next->setPrev(nullptr);
        this->head = next;
        delete iterator.node_ptr;

        return;
    }

    Node* prev = iterator.node_ptr->getPrev();

    next->setPrev(prev);
    prev->setNext(next);
    delete iterator.node_ptr;
    return;
}

template <class T> template <class Predicate>
typename List<T>::Iterator List<T>::find(const Predicate& predicate) const{

    for (Iterator iter = begin(); iter != end(); iter++) {
        if (predicate(&iter)) {
            return iter;
        }
    }
    return end();
}

template <class T>
void List<T>::swap(Iterator& iterator,Iterator& iterator2){

    if (iterator == end() || iterator2 == end()) {
        throw ;
    }

    T temp=&iterator2;
    iterator2 = iterator;
    iterator = temp;
}

template <class T> template <class Compare>
void List<T>::sort(const Compare& compare){

    Iterator first = begin();
    if (first == end()) {
        return;
    }
    Iterator second = begin();
    second++;
    if (second == end()) {
        return;
    }
    bool switched = true;

    while (switched) {
        first = begin();
        second = begin();
        second++;
        switched = false;
        for (; second!= end() ; first++, second++) {
            if (!compare(&first, &second)) {
                swap(first, second);
                switched = true;
            }
        }
    }
}

template <class T> int List<T>::getSize() const {

    return this->size;
}
template <class T> bool List<T>::operator==(const List &list) const {

    Iterator left = begin();
    Iterator right = list.begin();
    while (left != end() && right != list.end()) {
        if (&left != &right) {
            break;
        }
        left++;
        right++;
    }
    return (left == end() && right == list.end());
}
template <class T> bool List<T>::operator!=(const List &list) const {
    return !(*this == list);
}

#endif //HW3_LIST_H

#include <iostream>
#include <vector>
#include <forward_list>

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType>
struct Node {
    KeyType key;
    ValueType value;
    Node *next;

    Node(KeyType key_, ValueType value_) : key(key_), value(value_), next(nullptr) {}
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType> >
class HashTable {
public:
    HashTable() : HashTable(100, 0.5, Func()) {}
    HashTable(Func func) : HashTable(100, 0.5, func) {}
    HashTable(size_t capacity_, double factor_, Func func = Func()) : 
        _size(0), _capacity(capacity_), fill_factor(factor_), hash(func), 
        table(std::vector<Node<KeyType, ValueType>*>(capacity_)) {
            if( factor_ <= 0 || factor_ > 1)
                fill_factor = 0.5;
            if(_capacity == 0)
                _capacity = 1;
        }

    ~HashTable(){
        for (size_t i = 0; i < _capacity; ++i) {
            Node<KeyType, ValueType>* current = table[i];
            while (current != nullptr) {
                Node<KeyType, ValueType>* next = current->next;
                delete current;
                current = next;
            }
        }
    }

    void insert(KeyType key, ValueType value){
        size_t ind = hash(key) % _capacity;
        Node<KeyType, ValueType>* node = new Node<KeyType,ValueType>(key, value);
        insert_node(node, ind, table);
        if(static_cast<double>(_size)/_capacity > fill_factor){
            _capacity *= 2;
            _size = 0;
            std::vector<Node<KeyType, ValueType>*> newtable(_capacity);
            for(size_t i = 0; i < _capacity/2; ++i){
                Node<KeyType,ValueType>* node = table[i];
                while(node != nullptr){
                    Node<KeyType,ValueType>* nxt = node->next;
                    node->next = nullptr;
                    size_t ind  = hash(node->key) % _capacity;
                    insert_node(node, ind, newtable);
                    node = nxt;
                }
            }
            table = newtable;
        }
    }
    ValueType *find(KeyType key_){
        size_t ind = hash(key_) % _capacity;
        Node<KeyType, ValueType>* node = table[ind];
        while(node != nullptr){
            if(node->key == key_)
                return &node->value;
            node = node->next;
        }
        return nullptr;
    }
    void erase(KeyType key_){
        size_t ind = hash(key_) % _capacity;
        Node<KeyType, ValueType>* node = table[ind];
        if(node == nullptr)
            return;
        if(node->key == key_){
            table[ind] = node->next;
            delete node;
            --_size;
            return;
        }
        Node<KeyType, ValueType>* prev = node;
        node = node->next;
        while(node != nullptr){
            if(node->key == key_){
                prev->next = node->next;
                delete node;
                --_size;
                return;
            }
            node = node->next;
            prev = prev->next;
        }
    }

    Node<KeyType, ValueType> &operator[](uint64_t index){
        if(index >= _capacity)
            throw std::out_of_range("index out of hash table range");
        if(table[index] == nullptr)
            throw std::runtime_error("this index is null");
        return *table[index];
    }
    Node<KeyType, ValueType> at(uint64_t index) {
        return (*this)[index];
    }

    int size() const {
        return _size;
    }
    int capacity() const {
        return _capacity;
    }
    
private:
    int _size;
    int _capacity;
    double fill_factor;
    Func hash;
    std::vector<Node<KeyType, ValueType>*> table;
    void insert_node(Node<KeyType,ValueType>* node, size_t ind, std::vector<Node<KeyType, ValueType>*> &insertion_table){
        Node<KeyType,ValueType>* root = insertion_table[ind];
        if(root == nullptr){
            insertion_table[ind] = node;
            ++_size;
        }
        else{
            if(root->key == node->key){
                root->value = node->value;
                delete node;
                return;
            }
            while(root->next !=nullptr){
                if(root->key == node->key){
                    root->value = node->value;
                    delete node;
                    return;
                }
                root = root->next;
            }
            root->next = node;
            ++_size;
        }
    }
};

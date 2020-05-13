#include<iostream>
#ifndef CONTAINER_H
#define CONTAINER_H
using namespace std;
template<typename T>
//интерфейс
class Container{
public:
    // Виртуальный деструктор
    virtual ~Container(){};
    // Вывод
    virtual void print() const= 0;

    // Вставка элемента
    virtual void insert(const T& value) = 0;

    // Удаление элемента
    virtual void remove(const T& value) = 0;

    // Проверка наличия элемента
    virtual bool exists(const T& value) const = 0;
};

//exeption для обработки попыток взаимодействия (разыменования/инкремента) c nullptr
class IncorrectIndexException: public std::runtime_error
{
public:
    IncorrectIndexException();
};

template<typename TYPE>
class AvlTreeIterator;

template<typename TYPE>
class AvlTree;

// Отдельный элемент дерева
template <typename T>
class node {
    friend class AvlTree<T>;
    friend class AvlTreeIterator<int>;
    friend class AvlTreeIterator<const int>;


private:
    int height;
    T key;         // Значение
    node* left;
    node* right;
    node* next; // Указатель на следующий элемент для итератора
public:

    node(const T& key);
};

/*
 * Реализация итератора
 */
template<typename T>
class AvlTreeIterator {
public:
    // Вид итератора
    // (что конкретно мы намерены реализовать)
    using iterator_category = std::forward_iterator_tag;

    // Типы значения, указателя на значение, референса на значение
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    // Тип вычитания двух итераторов
    using difference_type = std::ptrdiff_t;

    // Конструкторы
    AvlTreeIterator();
    AvlTreeIterator(node<T>* el);

    // Разыменование, получение значения
    // TODO: обработка *list.end() и аналогов
    reference operator*() const;

    // Инкременты итератора
    // (логически -- переход к следующему значению)

    AvlTreeIterator& operator++();
    AvlTreeIterator operator++(int);

    // Сравнение *итераторов*

    bool operator==(const AvlTreeIterator& it) const;
    bool operator!=(const AvlTreeIterator& it) const;

private:
    // Указатель на текущий элемент
    node<T>* p;
};


template<typename T>
class AvlTree: public Container<T>{
    friend class AvlTreeIterator<int>;
    friend class AvlTreeIterator<const int>;
private:

    int height(node<T>* p);
    int bfactor(node<T>* p);
    void fixheight(node<T>* p);
    node<T>* rotateright(node<T>* p); // правый поворот вокруг p
    node<T>* rotateleft(node<T>* q); // левый поворот вокруг q
    node<T>* balance(node<T>* p); // балансировка узла p
    node<T>* insertprivate(node<T>* p, const T& k); // вставка ключа k в дерево с корнем p
    node<T>* findmin(node<T>* p) const; // поиск узла с минимальным ключом в дереве p
    node<T>* removemin(node<T>* p); // удаление узла с минимальным ключом из дерева p
    node<T>* removeprivate(node<T>* p, const T& k); // удаление ключа k из дерева p
    void printPrivate(node<T> *p) const;
    void copy_construct_private(node<T>* p);
    void what_next(node<T>* p);
    void update_all(node<T> *p);

    node<T> *root;
public:
    AvlTree();
    AvlTree<T>(const AvlTree<T>& tree);
    void insert(const T& value);
    void remove(const T& value);
    AvlTree& operator =(const AvlTree &tree);
    bool exists(const T& value) const;
    void print() const;

    ~AvlTree();

    using iterator = AvlTreeIterator<int>;
    using const_iterator = AvlTreeIterator<const int>;

    // Контейнер должен уметь отдавать служебные итераторы:
    // - на первый элемент;
    iterator begin() const;
    // - на позицию "после последнего элемента".
    iterator end() const;

    // А теперь ещё и аналогичные const-овые итераторы
    const_iterator cbegin() const;
    const_iterator cend() const;
};
#endif

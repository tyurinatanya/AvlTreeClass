
template <typename T>
node<T>::node(const T& key) : key(key), left(nullptr), right(nullptr), next(nullptr), height(1) {
}

/*
 * Реализация итератора
 */
template<typename T>
// Конструкторы
AvlTreeIterator<T>::AvlTreeIterator() : p(nullptr) {}

template<typename T>
AvlTreeIterator<T>::AvlTreeIterator(node<T>* el) : p(el) {}

    // Разыменование, получение значения
template<typename T>
using reference = T&;
template<typename T>
reference<T> AvlTreeIterator<T>:: operator*() const {

    if (p==nullptr) throw IncorrectIndexException();
    return p->key;
}

    // Инкременты итератора
    // (логически -- переход к следующему значению)
    // TODO: обработка list.end()++ и аналогов
template<typename T>
AvlTreeIterator<T>& AvlTreeIterator<T>:: operator++() {

    if (p == nullptr) throw IncorrectIndexException();
    p = p->next;
    return *this;
}

template<typename T>
AvlTreeIterator<T> AvlTreeIterator<T>::operator++(int) {

    if (p == nullptr) throw IncorrectIndexException();
    AvlTreeIterator resp = *this;
    if (p!=nullptr) p = p->next;
    return resp;

}

// Сравнение *итераторов*
// (т.е. сравниваем адреса, не значения по адресам)
template<typename T>
bool AvlTreeIterator<T>:: operator==(const AvlTreeIterator& it) const {

    return p == it.p;
}


template<typename T>
bool AvlTreeIterator<T>::operator!=(const AvlTreeIterator& it) const {
    return !(*this == it);
}



template<typename T>
int AvlTree<T>:: height(node<T>* p)
{
    return p?p->height:0;
}

template<typename T>
int AvlTree<T>:: bfactor(node<T>* p)
{
    return height(p->right)-height(p->left);
}

template<typename T>
void AvlTree<T>:: fixheight(node<T>* p)
{
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

template<typename T>
node<T>* AvlTree<T>:: rotateright(node<T>* p) // правый поворот вокруг p
{
    node<T>* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

template<typename T>
node<T>* AvlTree<T>:: rotateleft(node<T>* q) // левый поворот вокруг q
{
    node<T>* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}


template<typename T>
node<T>* AvlTree<T>:: balance(node<T>* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}


template<typename T>
node<T>* AvlTree<T>:: insertprivate(node<T>* p, const T& k) // вставка ключа k в дерево с корнем p
{
    if( !p ) return new node<T>(k);
    if( k<p->key )
        p->left = insertprivate(p->left,k);
    else
        p->right = insertprivate(p->right,k);
    return balance(p);
}

template<typename T>
node<T>* AvlTree<T>:: findmin(node<T>* p) const // поиск узла с минимальным ключом в дереве p
{
    if (p==root && p==nullptr) return root;
    return p->left?findmin(p->left):p;
}


template<typename T>
node<T>* AvlTree<T>:: removemin(node<T>* p) // удаление узла с минимальным ключом из дерева p
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

template<typename T>
node<T>* AvlTree<T>:: removeprivate(node<T>* p, const T& k) // удаление ключа k из дерева p
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = removeprivate(p->left,k);
    else if( k > p->key )
        p->right = removeprivate(p->right,k);
    else //  k == p->key
    {
        node<T>* q = p->left;
        node<T>* r = p->right;
        delete p;
        if( !r ) return q;
        node<T>* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

template<typename T>
void AvlTree<T>:: printPrivate(node<T> *p) const
{
    if (root==nullptr) cout<<"Nothing";
    else
    {
        if (p->left ) printPrivate(p->left);
        if (p->right) printPrivate(p->right);
        cout<<p->key<<"  ";
    }
}

template<typename T>
void AvlTree<T>:: copy_construct_private(node<T>* p)
{
    this->insert(p->key);
    if (p->left) copy_construct_private(p->left);
    if (p->right) copy_construct_private(p->right);
}

template<typename T>
void AvlTree<T>:: what_next(node<T>* p)
{
    if (p==nullptr)
        return;
    if (p==root)
    {
        if(p->left== nullptr && p->right == nullptr) return;
        if (p->right != nullptr)
        {
            node<T>* itog=p->right;
            while (itog->left!=nullptr)
            {
                itog=itog->left;
            }

            p->next=itog;
            return;
        }

    }

    else
    {
        node<T>* q=this->root;
        node<T>* rez=nullptr;

        while(q->left!=p && q->right!=p)
        {

            if (p->key > q->key)
            {
                q=q->right;
            }
            else
            {
                rez=q;
                q=q->left;
            }
        }
        if (q->left == p)
        {
            if (p->right == nullptr)
            {
                p->next = q;
                return;
            }
            node<T>* itog=p->right;
            while (itog->left!=nullptr)
                itog=itog->left;
            p->next=itog;
            return;
        }
        if (p-> right == nullptr)
            {
                p->next=rez;
                return;
            }
        node<T>* itog=p->right;
        while (itog->left!=nullptr)
            itog=itog->left;
        p->next=itog;
        return;
    }
}

template<typename T>
void AvlTree<T>:: update_all(node<T> *p)
{
    what_next(p);
    if(p->right!=nullptr) update_all(p->right);
    if(p->left!=nullptr) update_all(p->left);
}

template<typename T>
AvlTree<T>::AvlTree()
{
    root=nullptr;
}

template<typename T>
AvlTree<T>:: AvlTree(const AvlTree<T>& tree)/*: Container<T>(tree)*/
{
    this->root=nullptr;
    this->copy_construct_private(tree.root);
    update_all(root);

}

template<typename T>
void AvlTree<T>:: insert(const T& value)
{
    if (this->exists(value)) return;
    root=insertprivate(root, value);
    update_all(root);
}

template<typename T>
void AvlTree<T>:: remove(const T& value)
{
    root=removeprivate(root, value);
    if(root==nullptr) return;
    update_all(root);
}

template<typename T>
AvlTree<T>& AvlTree<T>:: operator =(const AvlTree &tree)
{
    if (this == &tree)
        return *this;
    while (root!=nullptr){remove(root->key);}
    this->root=nullptr;
    copy_construct_private(tree.root);
    update_all(root);
}

template<typename T>
bool AvlTree<T>:: exists(const T& value) const
{
    bool done=false;
    node<T> *pointer=root;

    while(!done){
        if (!root) return false;
        if (value<pointer->key && pointer->left==NULL){
            return false;
        }

            else if (value>pointer->key && pointer->right==NULL){
                return false;
            }
            else if (value==pointer->key) return true;

                else if (value<pointer->key)
                    pointer=pointer->left;
                    else pointer=pointer->right;

    }
}

template<typename T>
void AvlTree<T>:: print() const
{
    if (!root) cout<<" Nothing";
    else printPrivate(this->root);
    cout<<"ROOT: "<<root->key<<endl;
}

template<typename T>
AvlTree<T>:: ~AvlTree(){
    while (root) remove(root->key);
}


// Итератор на первый элемент в контейнере
template <typename T>
AvlTreeIterator<int> AvlTree<T>::begin() const {
    return AvlTreeIterator<T>(findmin(root));
}

// Итератор на позицию "после последнего элемента"
template <typename T>
AvlTreeIterator<int> AvlTree<T>::end() const {
    return AvlTreeIterator<T>(nullptr);
}

// И пара аналогичных const-овых итераторов
template <typename T>
AvlTreeIterator<const int> AvlTree<T>::cbegin() const {
    return AvlTreeIterator<const T>(findmin(root));
}

template <typename T>
AvlTreeIterator<const int> AvlTree<T>::cend() const {
    return AvlTreeIterator<const T>(nullptr);
}



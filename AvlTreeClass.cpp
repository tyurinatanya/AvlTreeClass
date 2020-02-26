#include <iostream>
using namespace std;
class Container
{
public:
    // Виртуальные методы, реализованные в классе AvlTree
    virtual void insert(int value) = 0;

    // Вывод
    virtual void print() = 0;

    virtual void remove(int value) = 0;

    virtual bool exists(int value) = 0;

    virtual ~Container() {};
};


class AvlTree: public Container{
private:

struct node // структура для представления узлов дерева
{
	int key;
	int height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; height = 1; }
};

int height(node* p)
{
	return p?p->height:0;
}

int bfactor(node* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
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

node* insertprivate(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if( !p ) return new node(k);
	if( k<p->key )
		p->left = insertprivate(p->left,k);
	else
		p->right = insertprivate(p->right,k);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p
{
	return p->left?findmin(p->left):p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* removeprivate(node* p, int k) // удаление ключа k из дерева p
{
	if( !p ) return 0;
	if( k < p->key )
		p->left = removeprivate(p->left,k);
	else if( k > p->key )
		p->right = removeprivate(p->right,k);
	else //  k == p->key
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if( !r ) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

    void printPrivate(node *p){
        if (!root) cout<<"Nothing";
    else{
            if (p->left ) printPrivate(p->left);
    if (p->right) printPrivate(p->right);
    cout<<p->key<<"  ";
   } }

node *root;
public:
    AvlTree(){
    root=NULL;

    }

    void insert(int value){
        root=insertprivate(root, value);
    }


    void remove(int value){
        root=removeprivate(root, value);
    }

    bool exists(int value){
        bool done=false;
        node *pointer=root;

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

    void print(){
        if (!root) cout<<" Nothing";
        else printPrivate(this->root);

    }

    ~AvlTree(){
        while (root) remove(root->key);

    }
};

int main()
{
    Container* c = new AvlTree();

    for(int i = 1; i < 10; i++)
        c->insert(i*i);

    cout << "Container after creation:" << endl;
    c->print();

    if(c->exists(25))
        cout << "Search for value 25: found" << endl;

    if(!c->exists(111))
        cout << "Search for value 111: not found" << endl;

    c->remove(25);
    cout << "Container after deletion of the element:" << endl;
    c->print();

    delete c;
    return 0;
}

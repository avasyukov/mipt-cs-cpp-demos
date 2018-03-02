#include <iostream>
  
using namespace std;

// Интерфейс
class Container
{
public:
    // Виртуальные методы, будут реализованы далее 
    virtual void insert(int value) = 0;
    virtual bool exists(int value) = 0;
    virtual void remove(int value) = 0;
    // Это потом заменим на перегруженный оператор <<
    virtual void print() = 0;

    // Виртуальный деструктор
    virtual ~Container();
};

Container::~Container() { }

// Реализация интерфейса

// TODO

int main()
{
    Container* c = new SimpleList();

    for(int i = 1; i < 10; i++)
        c->insert(i*i);

    printf("List after creation:\n");
    c->print();

    if(c->exists(25))
        cout << "Search for value 25: found" << endl;

    if(!c->exists(111))
        cout << "Search for value 111: not found" << endl;

    c->remove(25);
    cout << "List after deletion of the element:" << endl;
    c->print();

    delete c;
    return 0;
}

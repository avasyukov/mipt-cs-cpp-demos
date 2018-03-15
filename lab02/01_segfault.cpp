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

// Struct to store list element
typedef struct list_element {
    int value;			// Element value
    struct list_element* next;	// Pointer to next element
} list_element;

class SimpleList: public Container
{
public:
    SimpleList();
    ~SimpleList();
    void insert(int value);
    bool exists(int value);
    void remove(int value);
    void print();

protected:
    list_element* create(int i);
    list_element* find(int i);

    list_element* root;
};

SimpleList::SimpleList()
{
    this->root = NULL;
};

SimpleList::~SimpleList()
{
    list_element* cur_elem = this->root;
    while(cur_elem != NULL)
    {
        list_element* next = cur_elem->next;
        free(cur_elem);
        cur_elem = next;
        cout << "Element deleted" << endl;
    }
};

// Create new element, set its value to 'i', return pointer to new element
list_element* SimpleList::create(int value)
{
    // Allocate memmory
    list_element* elem = (list_element*)malloc(sizeof(list_element));
    // Set value
    elem->value = value;
    // There is no next element, so set next to NULL
    elem->next = NULL;

    return elem;
}

// Insert element 'elem' into list 'root' (on the 1st position),
// calls 'create' under the hood
void SimpleList::insert(int value)
{
    // Создали элемент физически
    list_element* elem = this->create(value);
    // Вставили в список
    elem->next = this->root->next;
    this->root->next = elem;
}

bool SimpleList::exists(int value)
{
    list_element* cur_element = this->find(value);
    return cur_element != NULL;
}

list_element* SimpleList::find(int value)
{
    list_element* cur_element = this->root;
    while(cur_element != NULL) {
        if(cur_element->value == value)
            return cur_element;
        cur_element = cur_element->next;
    }
    return NULL;
}

void SimpleList::remove(int value)
{
    list_element* elem = this->find(value);

    if(elem == NULL)
    {
        return;
    }
    // Special case - we are to delete the first element
    else if(this->root == elem)
    {
        // remember new root element
        list_element* new_root = root->next;
        // free memory
        free(root);
        // return new root
        this->root = new_root;
    }
    else
    {
        list_element* cur_elem = this->root;
        // Loop through the list.
        // Stop if when the next element is the one to delete.
        while(cur_elem->next != elem)
        {
            cur_elem = cur_elem->next;
        }

        // - change pointers
        cur_elem->next = elem->next;
        // - free memory
        free(elem);
    }
}

void SimpleList::print()
{
    list_element* cur_element = this->root;
    // Iterate through elements while NULL is not found
    while(cur_element != NULL) {
        printf("Element: %d\n", cur_element->value);
        // Go to next element
        cur_element = cur_element->next;
    }
}


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

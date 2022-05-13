#pragma once

//linked list

template <typename dataclass>

class linkClass {
public:
    class nodeClass {// node general structure
    public:
        dataclass data;
        nodeClass* next = nullptr;// point to the next node
        nodeClass* previous = nullptr;// point to the previous node
    };

    nodeClass* last = nullptr;// points to the last node
    nodeClass* first = nullptr;// points to the first node

    // CRUD
    void addTofirst(dataclass data);// create some node at first
    void addToEnd(dataclass data);// create some node at first

    nodeClass* get(int index) {// read a node
        if (first != nullptr) {
            if (index == 0) return first;
            else {
                nodeClass* current = first;
                while (current != nullptr && index > 0) {
                    index -= 1;
                    current = current->next;
                }
                return current;
            };
        }
        else return nullptr;
    };;

    void updNode(int index, dataclass data);// update a node
    void delNode(int index);// delete a node
    void purgeAll(); // delete all nodes

    dataclass operator[](int index) {
        return get(index)->data;
    };
};

    template <typename dataclass>
    void linkClass<dataclass>::addTofirst (dataclass data) {
        nodeClass* z = new (nodeClass);
        z->data = data;
        if (first != nullptr) {
            first->next = z;
            z -> next = first;
        }
        else {
            z -> previous = NULL;
            last = z;
        }
        first = z;
    };

    template <typename dataclass>
    void linkClass<dataclass>::addToEnd(dataclass data) {
        nodeClass* z = new (nodeClass);
        if (first != nullptr) {
            last->next = z;
            z->previous = last;
        }
        else {
            z->previous = nullptr;
            first = z;
        }
        last = z;
        z->data = data;
    };

    template <typename dataclass>
    void linkClass<dataclass>::updNode(int index, dataclass data) {
        nodeClass* find = get(index);
        if (find != nullptr) {
            find->data = data;
            cout << "\n Update Succesfull \n";
        }
    };

    template <typename dataclass>
    void linkClass<dataclass>::delNode(int index) {
        nodeClass* find = get(index);
        if (find != nullptr) {
            find->next->previous = find->previous;
            find->previous->next = find->next;
            delete find;
            cout << "\n Delete Succesfull \n";
        }
    };
    template <typename dataclass>
    void linkClass<dataclass>::purgeAll() {
        nodeClass* current = first;
        nodeClass* temp;
        while (current != nullptr) {
            temp = current->next;
            delete current;
            current = temp;
        }
        cout << "\n Purge Succesfull \n";
    };

//end of linked list


//Binary Trees

template <typename dataclass>
class treeClass {
public:
    class nodeClass {// node general structure
    public:
        int id = nullptr;
        bool isRoot = false;
        bool isParent = false;
        bool isLeaf = true;
        bool isNode = false;
        dataclass data;
        nodeClass* left = nullptr;// point to the next node
        nodeClass* father = nullptr;// point to the father node
        nodeClass* right = nullptr;// point to the previous node
    };
    nodeClass* root = nullptr;// points to the last node

    // CRUD
    void addToTree(dataclass from, int index);// create a new node on the tree
    
    dataclass get(nodeClass from, linkClass<dataclass>& data);// read a node
    
    nodeClass* search(nodeClass* from, int index, int dir)// search a node of the tree, starting from some point
    {
        nodeClass* cursor = from;
        if (cursor != nullptr) {
            if (cursor->id != index) {
                if (cursor->id > index) {
                    if (cursor->left != nullptr)
                        cursor = search(cursor->left, index);
                    else
                        dir = 1;

                }
                if (cursor->id < index) {
                    if (cursor->right != nullptr)
                        cursor = search(cursor->right, index);
                    else
                        dir = 2;

                }
                if (cursor->id == index) {
                    dir = 3;
                }
            }
        }
        else dir = 0;
        return cursor;
    };
    void purgeAll(); // delete all nodes
    

    dataclass operator[](int param) {
        return get(param)->data;
    };
};

template <typename dataclass>
void treeClass<dataclass>::addToTree(dataclass data, int id) {
    int dir = 0;
    nodeClass* father = search(root,id, dir);
    nodeClass* z = new (nodeClass);
    z->data = data;
    if (root != nullptr) {
        z->father = father;
        switch(dir) 
        {
        case 1:
            father->left = z;
            break;
        case 2:
            father->right = z;
            break;
        }
        father->isParent = true;
        father->isLeaf = false;
    }
    else {
        root = z;
    }
};

template <typename dataclass>
dataclass treeClass<dataclass>::get(treeClass::nodeClass from, linkClass<dataclass>& data)// read a node
{
    nodeClass* cursor = from;
    if (cursor != nullptr) {
        if (cursor->left != nullptr) {
            data.addToFirst(get(cursor->left));// la izquierda del arbol
        }
        data.addToEnd(cursor->data);
        if (cursor->left != nullptr) {
            data.addToEnd(get(cursor->right));// la izquierda del arbol
        }
    }
    else return nullptr;
};

template <typename dataclass>
void treeClass<dataclass>::purgeAll() {
    nodeClass* current = root;
    nodeClass* temp;
    while (current != nullptr) {
        temp = current->next;
        delete current;
        current = temp;
    }
    cout << "\n Purge Succesfull \n";
};

//end of Binary trees
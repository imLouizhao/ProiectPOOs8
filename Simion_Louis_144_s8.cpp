#include <iostream>
#include <vector>

using namespace std;

class IntSet {
private:
    int* vector;
    int size;

public:
    IntSet() {
        vector = nullptr;
        size = 0;
    }

    IntSet(int* vector_in, int size_in) {
        size = size_in;
        vector = new int[size_in];
        for (int i = 0; i < size; i++) {
            vector[i] = vector_in[i];
        }
    }

    IntSet(IntSet *obj) {
        size = obj->size;
        vector = new int[size];
        for (int i = 0; i < size; i++) {
            vector[i] = obj->vector[i];
        }
    }

    void afisare() {
        if (size == 0) {
            cout << "Vectorul este gol." << endl;
            return;
        }

        for (int i = 0; i < size; i++) {
            cout << vector[i] << " ";
        }
        cout << endl;
    }

    void adauga(int element) {
        int cont = 0;
        int* vector2;
        // for(int i = 0; i < size; i++) {
        //     if(vector[i] == element) {
        //         cont = 1;
        //     }
        // }
        vector2 = new int[size];
        for(int i = 0; i < size; i++) {
            vector2[i] = vector[i];
        }
        delete[] vector;
        vector = new int[size+1];
        for(int i = 0; i < size; i++) {
            vector[i] = vector2[i];
        }
        vector[size] = element;
        size++;
    }

    void sterge(int element) {
        for(int i = 0; i < size; i++) {
            if(vector[i] == element) {
                for(int j = i; j < size-1; j++) {
                    vector[j] = vector[j+1];
                }
                size--;
                i = size;
            }
        }
    }

    void multime() {
        for(int i = 0; i < size-1; i++) {
            for(int j = i+1; j < size; j++) {
                if(vector[i] == vector[j]) {
                    for(int x = j; x < size; x++) {
                        vector[x] = vector[x+1];
                    }
                    size--;
                }
            }
        }
    }

    IntSet* operator+ (IntSet obj) {
        IntSet *c = new IntSet(this);
        size += obj.size;
        for(int i = 0; i < obj.size; i++) {
            c->adauga(obj.vector[i]);
        }
        c->multime();
        return c;
    }

    IntSet* operator* (IntSet obj) {
        IntSet *c = new IntSet();
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < obj.size; j++) {
                if(vector[i] == obj.vector[j]) {
                    c->adauga(vector[i]);
                }
            }
        }
        c->multime();
        return c;
    }

    IntSet* operator- (IntSet obj) {
        IntSet *c = new IntSet();
        int cont;
        for(int i = 0; i < size; i++) {
            cont = 0;
            for(int j = 0; j < obj.size; j++) {
                if(vector[i] == obj.vector[j]) {
                    cont = 1;
                }
            }
            if(cont == 0) {
                c->adauga(vector[i]);
            }
        }
        c->multime();
        return c;
    }

};


int main() {
    int v[10] = {1, 2, 3};

    IntSet *obj1 = new IntSet();
    IntSet *obj2 = new IntSet(v, 3);
    cout << "Obiect 1 initial: ";
    obj1->afisare();
    cout << "Obiect 2 initial: ";
    obj2->afisare();
    cout << endl << "Obiect 2 dupa operatii: ";
    obj2->adauga(3);
    obj2->adauga(2);
    obj2->adauga(5);
    obj2->adauga(1);
    obj2->afisare();
    cout << "Obiect 2 transformat in multime: ";
    obj2->multime();
    obj2->afisare();

    int v2[10] = {2, 3, 6, 7};
    IntSet *obj3 = new IntSet(v2, 4);

    IntSet *obj4 = *obj2 + *obj3;
    cout << "Reuniune: ";
    obj4->afisare();
    IntSet *obj5 = *obj2 * *obj3;
    cout << "Intersectie: ";
    obj5->afisare();
    IntSet *obj6 = *obj4 - *obj5;
    cout << "Diferenta: ";
    obj6->afisare();

    return 0;
}
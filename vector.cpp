#include <iostream>

using namespace std;

template <typename T>
class Vec {
    private:
    T* data;            //array de elementos de tipo T
    size_t count;       //numero de elementos insertados
    size_t capacity;    //Numero de elementos que data puede almacenar
    public:
    Vec() : data(nullptr), count(0), capacity(0) {}
    Vec(size_t c) : data(new T[c]), count(0), capacity(c) {}
    ~Vec() {delete [] data;}

    size_t size() const {return count;}
    size_t cap() const {return capacity;}

    void push_back(const T& x){
        if (count == capacity){
            grow();
        }
        data[count] = x;
        count++;
    }

    void reserve(size_t newcap) {
        if (newcap <= capacity) return;
        T* nd = new T[newcap];
        for (size_t i = 0; i < count; i++) {
            nd[i] = data[i];
        }
        delete [] data;
        data = nd;
        capacity = newcap;
    }

    void grow() {
        size_t newcap = 1;
        if (capacity != 0) {
            newcap = capacity * 2;
        }
        reserve(newcap);
    }
};

int main() {
    cout << "Vectors!" << endl;
    Vec<char> p(1000);
    for (int i = 0; i < 10; i++){
        p.push_back('a');
    }
    cout <<p.size() << endl;

    return 0;
}
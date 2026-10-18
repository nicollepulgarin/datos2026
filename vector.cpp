#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

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

    //Access operations (unchecked bonds)
    size_t size() const {return count;}
    size_t cap() const {return capacity;}

    T& operator [] (size_t i) {return data[i];}
    const T& operator [] (size_t i) const {return data[i];}

    T& at(size_t i){
        if(i >= size()) throw out_of_range("Invalid index");
        return data[i];
    }

    const T& at(size_t i) const{
        if(i >= size()) throw out_of_range("Invalid index");
        return data[i];
    }

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

    void printVec(){
        for (size_t i = 0; i < capacity; i++){
            if(i < count) cout << data[i] << "  ";
            else
            cout << " " << "*";
        }
        cout << endl;
    }

    void erase(size_t pos){
        if (pos < size()){
            for(size_t i = pos; i < count; i++){
                data[i] = data[i+1];
            }
            count--;
        }else{
            throw out_of_range("Invalid position");
        }
    }

    void pop_front(){
        erase(0);
    }

    void pop_back(){
        size_t back = count - 1;
        erase(back);
    }

    void insert(size_t pos, const T& num){
        if (count == capacity) grow();
        for(size_t i = count; i > pos; i--){
            data[i] = data[i - 1];
        }
        data[pos] = num;
        count++;
    }

    T& front() {
        if(count == 0) throw out_of_range("Empty vector");
        return data[0];
    }
    T& back() {
        if(count == 0) throw out_of_range("Empty vector");
        return data [size() - 1];
    }

    void erase_range(size_t from, size_t to){
        size_t pos_erase = to - from; 
        for(size_t i = from; i < count - pos_erase; i++){
            data[i] = data[i + pos_erase];
        }
        count = count - pos_erase;
        printVec();
    }

    void clear(){
        count = 0;
    }

    //First vertion of contains
    // bool contains(const T &elem) const {
    //     for(size_t i = 0; i < count; i++){
    //         if(data[i] == elem) return true;
    //     }
    //     return false;
    // }

    //second vertion of contains
    bool contains(const T &elem) const {
        pair<size_t, bool> res = find(elem);

        if (res.second == true) return true;
        else return false;
    }

    pair<size_t, bool> find(const T &elem) const{
        for(int i = 0; i < count; i++){
            if (data[i] == elem) return make_pair(i, true);
        }
        return make_pair(0, false);
    }

    void remove(const T &elem){
        pair<size_t, bool> res = find(elem);

        if (res.first > 0){
            for(size_t i = res.first; i < count; i++){
                data[i] = data[i+1];
            }
            count--;
        }
    }

    void replace(const T &oldVal, const T &newVal){
        pair<size_t, bool> res = find(oldVal);

        if(res.second){
            data[res.first] = newVal;
        }
    }

    void remove_all(const T &elem){
        size_t w = 0;

        for(size_t i = 0; i < count; i++){
            if(elem != data[i]){
                data[w] = data[i];
                w++;
            }
        }
        count = w;
    }

    void replace_all(const T &oldVal, const T &newVal){
        for(size_t i = 0; i < count; i++){
            if(oldVal == data[i]){
                data[i] = newVal;
            }
        }
    }

    size_t count_elem(const T &elem) const{
        size_t counter = 0;
        for(size_t i= 0; i < count; i++){
            if(elem == data[i]){
                counter++;
            }
        }
        return counter;
    }

};

int main() {
    cout << "Vectors!" << endl;

    cout << "Vector p:" << endl;
    Vec<int> p(10);
    for (size_t i = 1; i <= 10; i++){
        p.push_back(i);
    }cout <<endl;

    p.printVec();
    cout << "Size: " <<p.size() << endl;
    cout << "Capacity: " <<p.cap() << endl;

    //cout <<p[3] << endl; // Utilizar desde main operacion operator no constante

    p.pop_front();
    p.printVec();
    p.pop_back();
    p.printVec();

    p.insert(2, 99);
    p.printVec();

    p.erase_range(2, 5);

    cout << p.contains(99) << endl;

    p.push_back(6);
    p.printVec();

    pair<size_t, bool> res = p.find(6);

    if(res.second) cout << res.first <<endl;
    else cout << "Element was not found." << endl;

    p.remove(67);
    p.printVec();

    p.replace(6, 10);
    p.printVec();

    p.insert(1, 8);
    p.insert(2, 6);
    p.insert(4, 8);
    p.printVec();

    p.remove_all(8);
    p.printVec();

    p.replace_all(6, 1);
    p.printVec();

    cout<< "Element appears: "<< p.count_elem(1) << endl;
    
    

    /*p.clear();
    p.printVec();
    cout << "Size: " <<p.size() << endl;
    cout << "Capacity: " <<p.cap() << endl;*/  


    /*cout << "Vector q:" << endl;
    Vec<int> q(5);
    q.push_back(5);
    q.push_back(10);
    q.push_back(15);
    q.push_back(20);
    q.push_back(25);

    q.printVec();
    cout<< "First element of the vector: " << q.front() <<endl;
    cout<< "Last element of the vector: " << q.back() <<endl;
    cout << "The middle element of the vector is: " << q.at(2) << endl;

    q[1] = 100;

    q.printVec();

    Vec<string> s(5);
    cout << "Vector s" << endl;

    s.push_back("the");
    s.push_back("quick");
    s.push_back("brown");
    s.push_back("fox");
    s.push_back("jumps");

    s.printVec();
    cout << "Size: " <<s.size() << endl;
    cout << "Capacity: " <<s.cap() << endl;

    s.insert(1, "system");
    s.printVec();

    cout << "Size: " <<s.size() << endl;
    cout << "Capacity: " <<s.cap() << endl;

    s.pop_front();
    s.printVec();
    s.pop_back();
    s.printVec();

    s.erase(2);
    s.printVec();
    */

    return 0;
}
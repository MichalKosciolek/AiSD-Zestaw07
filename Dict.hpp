#include <iostream>
#include <utility>
#include <string>
#include "LinkedList.hpp"

unsigned int hash(const std::string& str){
    char* c = new char[str.length()+1];
    strcpy(c, str.c_str());
    unsigned int h = 0;
    for (int i=0; c[i]; i++)
        h = (h << 3) ^ c[i];
    delete[] c;
    return h%100;
}

template<class K, class V>
class Dict {
    using Pair = std::pair<K, V>;
public:
    Dict(): size_(0), classes_counter(0) {}

    void clear(){
        for(auto & i : array){
            i.clear();
        }
    }

    bool insert(const Pair& p){
        unsigned int k = hash(p.first);
        if(!array[k].find(p))
            return false;
        if(array[k].find_pair(p.first) != nullptr && p.first == array[k].find_pair(p.first)->first){
            Pair tmp = std::make_pair(p.first, array[k].find_pair(p.first)->second);
            int index = array[k].find(tmp);
            array[k].insert(index, p);
            array[k].erase(index+1);
        }
        if(array[k].empty())
            classes_counter++;
        array[k].push_back(p);
        size_++;
        return true;
    }

    bool find(const K& k){
        return array[hash(k)].find_pair(k) != nullptr;
    }

    V& operator[](const K& k){
        return array[hash(k)].find_pair(k)->second;
    }

    //TODO
    bool erase(const K& k){
        if(array[k].empty())
            return false;
        size_ -= array[k].size();
        array[k].clear();
        return true;
    }

    int size(){
        return size_;
    }

    bool empty(){
        return !size();
    }

    void buckets(){
        int max = 0;
        int min = array[0].size();
        for(auto & i : array){
            if(i.size() > max)
                max = i.size();
            if(i.size() < min)
                min = i.size();
        }
        std::cout << "#" << " " << size() << " " << classes_counter << " " << min << " " << max << std::endl;
    }

    ~Dict(){
        clear();
    }
private:
    List<Pair> array[101];
    int size_;
    int classes_counter;
};
#include <list>
#include <unordered_map>


using namespace std;

class RLUCache {
    public:
    list<int> cache;
    unordered_map<int, pair<list<int>::iterator, int>> map;
    size_t size;
    RLUCache(size_t _size) {
        size = _size;
        map.reserve(_size);
    }
    void move_up(pair<list<int>::iterator, int> &kv) {
        cache.erase(kv.first);
        cache.push_front(kv.second);
        kv.first = cache.begin();
    }
    void max_reached() {
        cache.erase(cache.end());
    }
    void set(int key, int val) {

    }
    int get(int key) {
        if (map.at(key) == map.end()) {
            return -1;
        }

        auto kv = map[key];
        if (kv.first == cache.end()) { // Trying to access an element that has already been removed.
            map.erase(key);
            return -1;
        }
        
        move_up(kv);
        return kv.second;
    }
};
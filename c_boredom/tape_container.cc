#include <list>

using namespace std;

template<typename T>
struct List {
    T value;
    List<T> *prev;
    List<T> *prev;
};

#define self Tape
typedef int index_t;

template<typename T>
class self {
    public:
    List<T> *list;
    unordered_map<index_t, List<T>*> cache;
    struct Bounds { index_t min, max; } bounds;

    self(self *tape) {
        list   = tape->list;
        cache  = tape->cache;
        bounds = tape->bounds;
    }

    self(index_t size) {
        reserve(size);
    }

    void reserve(index_t idx) {
        find(idx);
    }

    List<T>* find(index_t idx) {
        assert(list != nullptr);
        index_t i;
        i = 0;
        List<T> *curr;
        curr = list;
        
        if (idx < 0) {
            while (i > idx) {
                if (curr->prev == nullptr) {
                    curr->prev = new List<T>; // (List<T>*)malloc(sizeof(List<T>));
                    curr->prev->next = curr;
                }
                curr = curr->prev;
                --i;
            }
            bounds.min = i;
            return curr;
        }
        if (idx > 0) {
            while (i < idx) {
                if (curr->next == nullptr) {
                    curr->next = new List<T>; // (List<T>*)malloc(sizeof(List<T>));
                    curr->next->prev = curr;
                }
                curr = curr->next;
                ++i;
            }
            bounds.max = i;
            return curr;
        }

        return curr;
    }

    T& operator[](index_t idx) {
        List<T> *curr;
        curr = cache[idx];
        if (curr == nullptr) {
            curr = find(idx);
            cache[idx] = curr;
        }
        return curr->value;
    }
};
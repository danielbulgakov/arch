#ifndef DRAWPOOL
#define DRAWPOOL

#include "core/visualize/interfaces/IDrawable.hh"
#include <map>
#include <memory>
#include <cstddef>

using IDrawablePtr = std::unique_ptr<IDrawable>;

class DrawPool {
private:
    std::map<size_t, IDrawablePtr> pool;
    size_t next_id = 0;

public:
    template<typename T = IDrawable, typename... Args>
    size_t create(Args&&... args) {
        size_t id = next_id++;
        pool[id] = std::make_unique<T>(std::forward<Args>(args)...);
        return id;
    }

    size_t add(IDrawablePtr obj) {
        size_t id = next_id++;
        pool[id] = std::move(obj);
        return id;
    }

    template<typename T = IDrawable>
    T* get(size_t id) {
        auto it = pool.find(id);
        if (it == pool.end()) return nullptr;
        return dynamic_cast<T*>(it->second.get());
    }

    bool remove(size_t id) {
        return pool.erase(id) > 0;
    }
};

#endif  // DRAWPOOL

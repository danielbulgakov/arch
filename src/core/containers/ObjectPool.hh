#ifndef OBJECTPOOL
#define OBJECTPOOL

#include <cstddef>
#include <memory>
#include <map>
#include "core/visualize/interfaces/IDrawable.hh"

using IDrawablePtr = std::unique_ptr<IDrawable>;

class ObjectPool
{
  protected:
    std::map<size_t, IDrawablePtr> pool;
    std::vector<IEventable*> eventables;
    size_t next_id = 0;

  public:
    template<typename T = IDrawable, typename... Args>
    size_t create(Args&&... args)
    {
        static_assert(std::is_base_of<IDrawable, T>::value, "T must inherit from IDrawable");
        auto obj = std::make_unique<T>(std::forward<Args>(args)...);

        IEventable* eventable = dynamic_cast<IEventable*>(obj.get());
        if (eventable)
            eventables.push_back(eventable);

        size_t id = next_id++;
        pool[id] = std::move(obj);
        return id;
    }

    size_t add(IDrawablePtr obj)
    {
        IEventable* eventable = dynamic_cast<IEventable*>(obj.get());
        if (eventable)
            eventables.push_back(eventable);

        size_t id = next_id++;
        pool[id] = std::move(obj);
        return id;
    }

    template<typename T = IDrawable>
    T* get(size_t id)
    {
        auto it = pool.find(id);
        if (it == pool.end())
            return nullptr;
        return dynamic_cast<T*>(it->second.get());
    }

    bool remove(size_t id)
    {
        auto it = pool.find(id);
        if (it != pool.end()) {
            IEventable* eventable = dynamic_cast<IEventable*>(it->second.get());
            if (eventable) {
                auto ev_it = std::remove(eventables.begin(), eventables.end(), eventable);
                eventables.erase(ev_it, eventables.end());
            }

            pool.erase(it);
            return true;
        }
        return false;
    }

    const std::vector<IEventable*>& getEventables() const {
        return eventables;
    }
};

#endif  // OBJECTPOOL

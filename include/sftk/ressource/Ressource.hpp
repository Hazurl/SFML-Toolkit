#pragma once

#include <functional>
#include <memory>
#include <string>

namespace sftk {

template<typename T>
using Loader = std::function<bool(T&)>;

template<typename T>
Loader<T> load_from_file(std::string const& path) {
    return [path] (T& res) {
        return res.loadFromFile(path);
    };
}

template<typename T>
Loader<T> backup(Loader<T> const& fa, Loader<T> const& fb) {
    return [fa, fb] (T& res) {
        return fa(res) || fb(res);
    };
}

template<typename T>
class Ressource {
public:

    Ressource(Loader<T> const& _load_func)
        : load_func(_load_func) {}
    
    std::shared_ptr<T> get() {
        if (is_loaded())
            return res.lock();

        std::shared_ptr<T> r = std::make_shared<T>();
        if (load_func(*r)) {
            res = r;
            return r;
        }

        return nullptr;
    }

    bool is_loaded() const {
        return !res.expired();
    }

    operator bool() const {
        return is_loaded();
    }

protected:

    std::weak_ptr<T> res;
    Loader<T> load_func;

};

}
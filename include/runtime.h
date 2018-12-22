#pragma once

/**
 *  @brief  a functional library for cpp
 *  @author Nicekingwei(Long Jinwei)
 */
#include <iostream>
#include <exception>
#include <functional>
#include <string>
#include <memory>
#include <variant>
#include <type_traits>
#include <future>
#include "ret_type_impl.h"

namespace steak {

/**
 *  @class ghost_t
 *  @brief attach a ghost type G to a base type
 */
template<typename G, typename B>
struct ghost_t {
    B data;     // store the value
    ghost_t(const B& x) : data(x) {}
};

template<typename G, typename B>
inline auto attach_ghost(const B& v) {
    return static_cast<ghost_t<G, B>>(v);
}


/**
 *  @class place_holder_t
 *  @brief placeholder for pattern matching
 */
struct place_holder_t {
    char ch;
    template<typename T>
    bool operator==(T) { return true; }
};

place_holder_t _;


/**
 *  @class lazy_type_t
 *  @brief data block to postpone uation(not thread-safe)
 */

template<typename T>
struct lazy_type_t;


template<typename T>
lazy_type_t<return_type_t<T>> lazy_call(const T& f) {
    using R = return_type_t<T>;
    using L = lazy_type_t<R>;
    using S = typename L::store_t;
    return lazy_type_t<R>(std::make_shared<S>(f));
}

template<typename T>
struct lazy_type_t {

    using block_t = std::function<T()>;
    using data_t = T;
    using future_t = std::future<T>;
    using store_t = std::variant<block_t, data_t, future_t>;

    template<typename Y> friend
    class lazy_type_t;

private:
    std::shared_ptr<store_t> ptr_data;

public:
    lazy_type_t() : ptr_data(std::make_shared<store_t>()) {}

    lazy_type_t(const data_t& v) : ptr_data(std::make_shared<store_t>(v)) {}

    lazy_type_t(const lazy_type_t<T>& x) : ptr_data(x.ptr_data) {}

    explicit lazy_type_t(std::shared_ptr<store_t> p) : ptr_data(std::move(p)) {}

    const T& get() const {
        store_t* p = ptr_data.get();

        if (auto p_block = std::get_if<block_t>(p)) {
            *ptr_data = (*p_block)();
        } else if (auto p_future = std::get_if<future_t>(p)) {
            *ptr_data = p_future->get();
        }

        return std::get<data_t>(*p);
    }

    lazy_type_t<T>& async() {
        auto p = ptr_data.get();

        if (auto p_block = std::get_if<block_t>(p)) {
            *ptr_data = std::async(*p_block);
        }

        return *this;
    }

    operator const T&() const {
        return get();
    }

    bool operator==(const lazy_type_t<T>& x) const {
        return x.get() == get();
    }

    template<typename Y>
    lazy_type_t<return_type_t<Y>> transform(const Y& fun) const {
        auto copy = *this;
        return lazy_call([=]() {
            auto x = copy.get();
            return fun(x);
        });
    }

    template<typename Y>
    lazy_type_t<return_type_t<Y>> operator|(const Y& fun) const {
        auto copy = *this;
        return lazy_call([=]() {
            auto x = copy.get();
            return fun(x);
        });
    }
};



/**
 * @class zipped_pair_t
 */
template<class... T>
struct zipped_pair_t {
    template<typename...K>
    bool match(K...) {
        return true;
    }
};


template<typename T1>
struct zipped_pair_t<T1> {
    lazy_type_t<T1> data;

    zipped_pair_t() {}

    zipped_pair_t(const T1& x) { data = x; }

    zipped_pair_t(const lazy_type_t<T1>& x) { data = x; }

    bool operator==(const zipped_pair_t<T1>& x) const {
        return x.data == data;
    }

    bool match(std::pair<T1&, place_holder_t> v1) {
        v1.first = data.get();
        return true;
    }

    bool match(std::pair<T1&&, place_holder_t> v1) {
        return v1.first == data.get();
    }

    bool match(T1& v1) {
        v1 = data.get();
        return true;
    }

    bool match(T1&& v1) {
        return v1 == data.get();
    }

    bool match(lazy_type_t<T1>& f1) {
        f1 = data.get();
        return true;
    }

    bool match(lazy_type_t<T1>&& f1) {
        return f1.get() == data.get();
    }

    bool match(std::pair<lazy_type_t<T1>&, place_holder_t> f1) {
        f1.first = data.get();
        return true;
    }

    bool match(std::pair<lazy_type_t<T1>&&, place_holder_t> f1) {
        return f1.first.get() == data.get();
    }

    template<typename G, typename K>
    bool match(ghost_t<G, K>&& tp) {
        auto m = data.get();
        return m.match(tp);
    }

    bool match(place_holder_t) {
        return true;
    }

    template<typename...K>
    bool match(K...) {
        return false;
    }
};

template<typename T1, typename... T>
struct zipped_pair_t<T1, T...> : public std::pair<lazy_type_t<T1>, zipped_pair_t<T...>> {
    zipped_pair_t() {}

    zipped_pair_t(const zipped_pair_t<T1, T...>& x) {
        this->first = x.first;
        this->second = x.second;
    }

    template<typename Tx, typename...Ts>
    zipped_pair_t(const Tx& v1, const Ts& ...args) {
        this->first = v1;
        this->second = zipped_pair_t<T...>(args...);
    }

    bool operator==(const zipped_pair_t<T1, T...>& x) const {
        return x.first == this->first && x.second == this->second;
    }


    template<typename Tx, typename Ts>
    bool match(std::pair<Tx, Ts>& tp) {
        if (zipped_pair_t<T1>(this->first).match(std::forward<Tx>(tp.first)))
            return this->second.match(std::forward<Ts>(tp.second));
        else
            return false;
    }


    template<typename...K>
    bool match(K...) {
        return false;
    }
};


/**
 *  @brief forward and zip
 */
inline auto forward_and_zip() {
    return _;
}

template<typename T1>
inline auto forward_and_zip(T1&& v1) {
    auto sec = _;
    return std::pair<T1, decltype(sec)>(std::forward<T1>(v1), std::forward<decltype(sec)>(sec));
}

template<typename T1, typename...Ts>
inline auto forward_and_zip(T1&& v1, Ts&& ...vs) {
    auto sec = forward_and_zip<Ts...>(std::forward<Ts>(vs)...);
    return std::pair<T1, decltype(sec)>(std::forward<T1>(v1), std::forward<decltype(sec)>(sec));
}


/**
 *  @class case_class_t
 */
template<typename G, class... T>
struct case_class_t {
    using D=zipped_pair_t<T...>;
    D data;
    const char* name = G::consname;
    static const G constype;

    case_class_t() {}

    case_class_t(const case_class_t<G, T...>& x) : data(x.data) {}

    case_class_t(const T& ... args) : data(args...) {}

    template<typename K>
    bool unapply(K& args) {
        return data.match(args);
    }

    bool operator==(const case_class_t<G, T...>& x) const {
        return x.data == this->data;
    }
};

template<typename G>
struct case_class_t<G> {
    char data = 0;
    const char* name = G::consname;
    static const G constype;

    case_class_t() {}

    template<typename K>
    bool unapply(K) {
        return true;
    }

    bool operator==(const case_class_t<G>&) const {
        return true;
    }
};


template<typename T>
struct is_data_class {
    template<typename _T>
    static auto check(_T) -> typename std::decay<typename _T::data_class_label>::type;

    static void check(...);

    using type=decltype(check(std::declval<T>()));
    enum {
        value = !std::is_void<type>::value
    };
};

template<typename G>
struct cal_cons_type {
    template<typename...T>
    using R=case_class_t<G, T...>;
};

template<typename T1>
std::ostream& operator<<(std::ostream& out, const zipped_pair_t<T1>& tp) {
    if constexpr(is_data_class<std::decay_t<T1>>::value) out << '(';
    out << tp.data.get();
    if constexpr(is_data_class<std::decay_t<T1>>::value) out << ')';
    return out;
}

template<typename T1, typename T2, typename...T>
std::ostream& operator<<(std::ostream& out, const zipped_pair_t<T1,T2,T...>& tp) {
    if constexpr(is_data_class<std::decay_t<T1>>::value) out << '(';
    out << tp.first;
    if constexpr(is_data_class<std::decay_t<T1>>::value) out << ')';
    out << " " << tp.second;
    return out;
}


template<typename G, typename...T>
std::ostream& operator<<(std::ostream& out, const case_class_t<G, T...>& x) {
    if constexpr(std::is_same_v<char, std::decay_t<decltype(x.data)>>) {
        return out << x.name;
    } else {
        return (out << x.name << " " << x.data);
    }
}

template<int index, typename V>
struct search_t {
    template<typename G, typename S>
    static bool search(ghost_t<G, S>* t, V* var) {
        try {
            auto data = std::get<index>(*var);
            if constexpr(std::is_same_v<G, std::decay_t<decltype(data.constype)>>) {
                return data.unapply(t->data);
            } else {
                return search_t<index - 1, V>::search(t, var);
            }
        }
        catch (std::bad_variant_access&) {
            return search_t<index - 1, V>::search(t, var);
        }
    }

    static bool compare(V* var1, V* var2) {
        try {
            auto v1 = std::get<index>(*var1);
            auto v2 = std::get<index>(*var2);
            return v1 == v2;
        }
        catch (std::bad_variant_access&) {
            return search_t<index - 1, V>::compare(var1, var2);
        }
    }

    static std::ostream& show(std::ostream& out, const V* var) {
        try {
            auto& data = std::get<index>(*var);
            out << data;
            return out;
        }
        catch (std::bad_variant_access&) {
            return search_t<index - 1, V>::show(out, var);
        }
    }
};

template<typename V>
struct search_t<-1, V> {
    template<typename G, typename S>
    static bool search(ghost_t<G, S>*, V*) {
        return false;
    }

    static std::ostream& show(std::ostream& out, const V*) {
        return out;
    }

    static bool compare(V*, V*) { return false; }
};

template<typename...T>
struct data_class_t : public std::variant<T...> {
    using data_class_label=char;

    data_class_t() {}

    template<typename K>
    data_class_t(const K& x):std::variant<T...>(x) {}

    template<typename G, typename S>
    inline bool match(ghost_t<G, S> t) {
        return search_t<sizeof...(T) - 1, std::variant<T...>>::search(&t, this);
    }

    bool operator==(const data_class_t<T...>& x) const {
        return search_t<sizeof...(T) - 1, std::variant<T...>>::compare(&x, this);
    }

    std::ostream& show(std::ostream& out) const {
        return search_t<sizeof...(T) - 1, std::variant<T...>>::show(out, this);
    }

    auto eval() {
        return *this;
    }
};

template<typename T1, typename...T>
std::ostream& operator<<(std::ostream& out, const data_class_t<T1, T...>& d) {
    return d.show(out);
}
};

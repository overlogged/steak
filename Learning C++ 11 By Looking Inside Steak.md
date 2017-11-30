# Learning C++ 11 By Looking Inside Steak

## Time for advertisement

### Steak 1.0
### A programming language which provides generalized algebraic data types, pattern matching and lazy evaluation based on C++17.

### Installation

* As a domain specific language powered by C++ macros

Just copy include/runtime.h and include/steak.h into your project and #include "steak.h". Be sure your C++ compiler support C++17 standard.

* As a programming language powered by a compiler with C++17 backend.

    1. install `haskell-stack`
    1. clone this repository
    1. run `stack install`

### Steak Language Documentation

Steak programming language inherits C++17 completely except that `match` and `dataclass` are keywords.

The extension names of Steak are `.stk.cpp`,`.stk.hpp` or `.stk.h`. The compiler will compile source files to c++17 code.

#### Usage

* steak file: compile the source file and print the object code to stdout
* steak dirctory: search the directory recursively and compile all `*.stk.cpp`,`*.stk.h`,`*.stk.hpp` to `*.cpp`,`*.h`,`*.hpp`
* steak --version: version and license
* steak --help: help

#### Language Specification
* `dataclass` is for defining generalized algebraic data types.
Usage:
`[]` means optional

```c++
[template<...>] dataclass adt
{
    return_type constructor1(...);
    return_type constructor2(...);
    ...   
};
```

* `match` is for pattern matching. It's similar to `switch` expression.
Usage:

```c++
match(var)
{
    case Cons1(...):
        ...
    case Cons2(...):
        ...
    default:
        ...
}
```

Examples are available at `examples/`

#### Warnings

* Remember that compiler won't deal with macros. As a result, don't use macros in `dataclass` or `match` expressions.
* In the `case Cons(...)` expression, only literals and identifiers are allowed, operators and function call are not allowed.For example,`Just(x)` and `Just(1)` are valid, while `Just(x.c)` or `Just(1+3)` are invalid. Constructor with no paramenter also need to be followed by `()`, for example, `case Nothing()`.
* If you know the implementations of the library and the compiler, you will understand all the strange things.

# Let's go to our topic

* topics we will cover
    * Points
        * reinterpret_cast
        * using
        * variadic template
        * rvalue reference
        * perfect forwarding
        * reference folds
        * decltype
        * fold expression
        * SFINAE
        * if constexpr
    * Tricks
        * currying template
        * dependent type
        * macro tricks


* ghost_type_t

    attch a ghost type to a certain type.
```C++
template<typename G,typename B>
struct ghost_type_t
{
    B data;     /* Point 0. reinterpret_cast */
    ghost_type_t(const B& x):data(x){}
};
```

* place_holder_t

```C++
struct place_holder_t{char c;};
place_holder_t _;
```

* lazy_type_t

    Use function to put off evaluation and `shared_ptr` to manage memory. After `eval()` is called, the function will be replaced by a function that returns the result directly.
```C++
template<typename T>
struct lazy_type_t
{
    /* Point 1. using */
    using B=std::function<T()>;
    std::shared_ptr<B> data;
    T eval() const;
};
```

* zipped_pair_t

    Use `std::pair` to construct tuple for convenience of pattern matching. All types in `zipped_pair_t` are lazy. use lvalue reference and rvalue reference to distinguish lvalue and rvalue. `std::pair<T,place_holder_t>` is equivalent to T. `ghost_type_t<G,K>` is for nested patterning.

```C++
/* Point 2. variadic template */
template<class... T> struct zipped_pair_t;

/* Point 3. specializations */
template<typename T>
struct zipped_pair_t<T>
{
    bool match(T1& v1);
    /* Point 4. rvalue reference (can be mutable) */
    bool match(T1&& v1);
    bool match(lazy_type_t<T1>& f1);
    bool match(lazy_type_t<T1>&& f1);
    bool match(std::pair<T1&,place_holder_t> v1);
    bool match(std::pair<T1&&,place_holder_t> v1);
    bool match(std::pair<lazy_type_t<T1>&,place_holder_t> f1);
    bool match(std::pair<lazy_type_t<T1>&&,place_holder_t> f1);
    template<typename G,typename K>
    bool match(ghost_type_t<G,K>&& tp);
    bool match(place_holder_t);

    template<typename...K>
    bool match(K...)
};
```

```C++
template<typename T1,typename... T>
struct zipped_pair_t<T1,T...>:public std::pair<lazy_type_t<T1>,zipped_pair_t<T...>>
{
    zipped_pair_t();
    zipped_pair_t(const zipped_pair_t<T1,T...>&x);

    template<typename Tx,typename...Ts>
    zipped_pair_t(const Tx& v1,const Ts&...args);

    bool operator == (const zipped_pair_t<T1,T...>& x) const;


    template<typename Tx,typename Ts>
    bool match(std::pair<Tx,Ts>& tp)
    {  
        if(zipped_pair_t<T1>(this->first).match(std::forward<Tx>(tp.first)))
            /* Point 5. perfect forwarding(skip) */
            return this->second.match(std::forward<Ts>(tp.second));
        else
            return false;
    }

    template<typename...K>
    bool match(K...);
};
```

* forward_and_zip

    forward some arguments and zip them into nested `std::pair` in a similar way of `zipped_pair_t`.
```C++
auto forward_and_zip()
{
    return _;
}

template<typename T1>
/* Point 6. reference folds */
// & && == && & == &
// T & &x == T &x
// T && && x == T &&x
auto forward_and_zip(T1&& v1)
{
    auto sec=_;
    /* Point 6. decltype */
    return std::pair<T1,decltype(sec)>(std::forward<T1>(v1),std::forward<decltype(sec)>(sec));
}

template<typename T1,typename...Ts>
auto forward_and_zip(T1&& v1,Ts&&...vs)
{
    /* Point 7. fold expression */
    auto sec = forward_and_zip<Ts...>(std::forward<Ts>(vs)...);
    return std::pair<T1,decltype(sec)>(std::forward<T1>(v1),std::forward<decltype(sec)>(sec));
}
```

* case_class_t

    Just attach a ghost type to `zipped_pair_t`.If we discard the ghost type, B and C in `data A = B Int | C Int` are both `case_class<int>`.
    
    `unapply` just calls `data`'s `match` function.
```C++
template<typename G,class... T>
struct case_class_t
{
    using D=zipped_pair_t<T...>;
    D data;
    
    template<typename K>
    bool unapply(K& args);
};
```

* data_class_t

    The base class of all generalized algebraic data types.
```C++
template<typename...T>
struct data_class_t:public std::variant<T...>
{
    using data_class_label=char;
};

#define Data(T,name,...) T struct name;T struct name:public data_class_t<__VA_ARGS__>{};

/* Point 8. SFINAE */
template<typename T>
struct is_data_class
{
    template <typename _T>static auto check(_T)->typename std::decay<typename _T::data_class_label>::type;
    static void check(...);
    using type=decltype(check(std::declval<T>()));
    enum{value=!std::is_void<type>::value};
};
```

* pattern matching
    * `With`, `Case`, `EndWith` are all macros , they can form a complete if block.
    * Perfect forwarding is important.

* constructor

    Constructor is a function which returns adt or the lazy type of it.
```C++
inline lazy_type_t<adt> construtor_(const t1& v1);
inline lazy_type_t<adt> construtor_(steak::lazy_type_t<t1> v1);
inline adt construtor(const t1& v1);
inline adt construtor(steak::lazy_type_t<t1> v1);
```

* more details
```c++
/* Trick 0. currying template */
template<typename G>
struct cal_cons_type
{
    template<typename...T>
    using R=case_class_t<G,T...>;
};

/* Point 9. if constexpr */
template<typename T1>
std::ostream& operator << (std::ostream& out,const zipped_pair_t<T1>& tp)
{
    if constexpr(is_data_class<std::decay_t<T1>>::value) out<<'(';
    out<<tp.data;
    if constexpr(is_data_class<std::decay_t<T1>>::value) out<<')';
    return out;
}

/* Trick 1. dependent types for visiting std::variant */
template<int index,typename V>
struct search_t
{
    template<typename G,typename S>
    static bool search(ghost_type_t<G,S>* t,V* var)
    {
        try
        {
            auto data = std::get<index>(*var);
            if constexpr(std::is_same_v<G,std::decay_t<decltype(data.constype)>>)
            {
                return data.unapply(t->data); 
            }
            else
            {
                return search_t<index-1,V>::search(t,var);
            }
        }
        catch(std::bad_variant_access&)
        {
            return search_t<index-1,V>::search(t,var);
        }
    }
};

template<typename V>
struct search_t<-1,V>
{
    template<typename G,typename S>
    static bool search(ghost_type_t<G,S>*,V*);
};

/* Trick 2. macro tricks */
#define With(x) if(1){auto match_var=x.eval();if(0){;
#define Case(name,...) }else if(match_var.match(steak::attach_ghost<steak_constructors::name>(steak::forward_and_zip(__VA_ARGS__)))){;
#define Default }else{;
#define EndWith() }}
```

# Note
The compiler and the library works well with `GCC 7.2.0`

Feel free to contact me if you want to know more about Steak.
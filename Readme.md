# Steak 1.0
### A programming language which provides generalized algebraic data types, pattern matching and lazy evaluation based on C++17.

# Installation

* As a domain specific language powered by C++ macros

Just copy include/runtime.h and include/steak.h into your project and #include "steak.h". Be sure your C++ compiler support C++17 standard.

* As a programming language powered by a compiler with C++17 backend.

    1. install `haskell-stack`
    1. clone this repository
    1. run `stack install`

# Steak Language Documentation

Steak programming language inherits C++17 completely except that `match` and `dataclass` are keywords.

The extension names of Steak are `.stk.cpp`,`.stk.hpp` or `.stk.h`. The compiler will compile source files to c++17 code.

## Usage

* steak file: compile the source file and print the object code to stdout
* steak dirctory: search the directory recursively and compile all `*.stk.cpp`,`*.stk.h`,`*.stk.hpp` to `*.cpp`,`*.h`,`*.hpp`
* steak --version: version and license
* steak --help: help

## Language Specification
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

## Warnings

* Remember that compiler won't deal with macros. As a result, don't use macros in `dataclass` or `match` expressions.
* In the `case Cons(...)` expression, only literals and identifiers are allowed, operators and function call are not allowed.For example,`Just(x)` and `Just(1)` are valid, while `Just(x.c)` or `Just(1+3)` are invalid. Constructor with no paramenter also need to be followed by `()`, for example, `case Nothing()`.
* If you know the implementations of the library and the compiler, you will understand all the strange things.

# C++ DSL Documentation

* generalized algebraic data types

    Generalized algebraic data types can be defined via C++ macros.

    Let's take 
    ```haskell
    data List a = Cons a (List a) deriving Show
    ``` 
    as an example:
    ```C++
    RegCons(Nil) RegCons(Cons)
    Data(Va,List,RealType(Nil),RealType(Cons,a,List<a>))
        Cons0(Va,Nil,List<a>)
        Cons2(Va,Cons,a,List<a>,List<a>)
    DerivingShow(Va,List<a>)
    ```
    Another example :
    ```haskell
    data Peano = Z | S Peano deriving Show
    ```
    ```C++
    RegCons(Z) RegCons(S)
    Data(V,Peano,RealType(Z),RealType(S,Peano))
        Cons0(V,Z,Peano)
        Cons1(V,S,Peano,Peano)
    DerivingShow(V,Peano)
    ```
    * At first, you should register the constructors' name using `RegCons`.
    * macro Data is for defining the data structure in C++, and macro RealType is for inferencing the actual type of case classes.
    * Va is short for `template<typname a>`, while V means Nothing. If you want to use 2 type variables,you can use Vab. 
    * Cons[d] can be used to define constructors,d is the number of parameters. `Cons2(Va,Cons,a,List<a>,List<a>)` means `Cons::a->List a->List a`
    * DerivingShow is not necessary.

* pattern matching
    ```C++
    int maybe_sum(steak::lazy_type_t<List<Maybe<int>>> l)
    {
        int x=0,y=0;
        while(1)
        {
            With(l)
                Case(Cons,UnZip(Just,y),l)
                    x+=y;
                Case(Nil)
                    break;  /* break while(1) */
                Case(Cons,UnZip(Nothing),l)
                    ;            
            EndWith()
        }
        return x;
    }
    ```
    * With(x) starts a pattern matching for x and x must be `lazy_type_t<adt>` or `adt`
    * Case(constructor name,parameters...) is for matching, {} and break is not necessary. You can also use Unzip for nested pattern matching.

* lazy evaluation
    * `lazy_type_t` is a template class to seal data types in C++. Constructor functions with the actual name returns a `adt` value, while functions followed by `_` returns a `lazy_type_t<adt>` value. For example, `Cons` is a strict constructor and `Cons_` is a lazy constructor. **warning**: If the constructor takes more than 5 parameters, the parameters must be all instant values or all `lazy_type_t` s.
    * Apply[d] are macros for calling function and putting off evaluation. Similarly, they only receieve all instant values or all `lazy_type_t` s as parameters.
* currying functions
    * use `std::bind` to construct paritial applied functions.

# Runtime Implementations
If you want to know the implementation of steak, you can read this part for more details. The code below are refined.

* ghost_type_t

    attch a ghost type to a certain type.
```C++
template<typename G,typename B>
struct ghost_type_t
{
    B data;     // just for reinterpret_cast
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
    using B=std::function<T()>;
    std::shared_ptr<B> data;
    T eval() const;
};
```

* zipped_pair_t

    Use `std::pair` to construct tuple for convenience of pattern matching. All types in `zipped_pair_t` are lazy. use lvalue reference and rvalue reference to distinguish lvalue and rvalue. `std::pair<T,place_holder_t>` is equivalent to T. `ghost_type_t<G,K>` is for nested patterning.

```C++
template<class... T> struct zipped_pair_t;
template<typename T>
struct zipped_pair_t<T>
{
    bool match(T1& v1);
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

* forward_and_zip

    forward some arguments and zip them into nested `std::pair` in a similar way of `zipped_pair_t`.
```C++
auto forward_and_zip()
{
    return _;
}

template<typename T1>
auto forward_and_zip(T1&& v1)
{
    auto sec=_;
    return std::pair<T1,decltype(sec)>(std::forward<T1>(v1),std::forward<decltype(sec)>(sec));
}

template<typename T1,typename...Ts>
auto forward_and_zip(T1&& v1,Ts&&...vs)
{
    auto sec = forward_and_zip<Ts...>(std::forward<Ts>(vs)...);
    return std::pair<T1,decltype(sec)>(std::forward<T1>(v1),std::forward<decltype(sec)>(sec));
}
```

* case_class_t

    Just attach a ghost type to `zipped_pair_t`.If we discard the ghost type, B and C in `data A = B Int | C Int` are both `case_class<int>`.
    
    `unapply` just calls `data`'s `match` function.
```C++
template<uint64_t L,uint64_t H,class... T>
struct case_class_t
{
    using D=zipped_pair_t<T...>;
    D data;

    static constexpr uint64_t id_l=L,id_h=H;
    
    template<typename K>
    bool unapply(K& args);
};
```

* data_class_t

    The base class of all generalized algebraic data types.
```C++
template<typename...T>
struct data_class_t:public std::variant<T...>{};

#define Data(T,name,...) T struct name;T struct name:public data_class_t<__VA_ARGS__>{};
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

# Note
The compiler and the library works well with `GCC 7.2.0`

Feel free to contact me if you want to know more about Steak.
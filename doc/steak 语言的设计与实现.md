# Steak 语言的设计与实现

阅读本系列文章需要读者了解一些基本的函数式语言概念和 C++ 11 知识。

Steak 语言是我两年前写的一个项目，最近又翻出来优化了一下，早就说要写篇文章总结一下，结果一直咕咕咕（

[steak](https://github.com/nicekingwei/steak)

Steak 语言设计的初衷是把 GADT、惰性求值、模式匹配等函数式语言特性引入 C++。C++ 11 以后，语言里逐渐出现了一些支持函数式编程的特性，例如 lambda 表达式，但他们用起来又不是特别好用（等以后有了 Ranges，情况会好转一些）。因此我想设计一个库或语言，让 C++ 使用者能更舒服地编写函数式程序。当然目前的结果只是个玩具，因为编译太慢了：）。



## 惰性求值

C++11 原生支持了 lambda 表达式，因此我们可以用一个 lambda 闭包来表达一个待求值的块，例如


```c++
auto lazy_double = []() { return sqrt(2.0); };
```
这时的 lazy_double 即是一个惰性求值的块，`sqrt(2.0)` 只有在你用到 `lazy_double` 的时候才会被计算。但如果我们多次引用 `lazy_double`，`sqrt(2.0)` 便会被执行多次，我们希望它能只计算一次。所以，`lazy_double` 要么是 double，要么是返回一个 double 的函数。因为我们知道，C++ 有隐式转换特性，我们只需要在类里实现一个形如

```c++
operator const T &() const
{
    return T{};
}
```

的函数，即可将该类的实例隐式转换为 T 的实例。

更进一步，我们还可以表达异步计算的语义。如果我们之前声明了一个块，这个块的计算需要耗费大量的时间，于是我们利用 C++ 标准库的 `std::async`  来获得一个 `std::future` ，发起异步的计算。在我们需要用它的时候，再阻塞地拿到值。

不知不觉中，我们抽象掉了具体的计算过程及方法。在我们主要的程序中，我们只是声明了数据流动的方式，而并非给机器施加了计算的指令。这其实也是函数式编程与命令式编程在思维方式上的微小差异。扯远了，我们回到 `lazy_type` 的问题上来。

于是我们就可以利用 `std::variant` 定义出 `lazy_type` ，为了方便，我统一使用了智能指针：

```c++
template <typename T>
struct lazy_type_t
{
    using block_t = std::function<T()>;
    using data_t = T;
    using future_t = std::future<T>;
    using store_t = std::variant<block_t, data_t, future_t>;

    template <typename Y>
    friend class lazy_type_t;

  private:
    std::shared_ptr<store_t> ptr_data;

  public:
    lazy_type_t() : ptr_data(std::make_shared<store_t>()) {}
    lazy_type_t(const data_t &v) : ptr_data(std::make_shared<store_t>(v)) {}
    lazy_type_t(const lazy_type_t<T> &x) : ptr_data(x.ptr_data) {}
    
    explicit lazy_type_t(std::shared_ptr<store_t> p) : ptr_data(std::move(p)) {}
    
    const T &get() const;
    
    lazy_type_t<T> &async();
    
    operator const T &() const;

    bool operator==(const lazy_type_t<T> &x) const;

    template <typename Y>
    lazy_type_t<return_type_t<Y>> transform(const Y &fun) const;

    template <typename Y>
    lazy_type_t<return_type_t<Y>> operator|(const Y &fun) const;
};
```

`block_t` 是返回 T 的函数，`future_t` 是返回 T 的 `future` ，`store_t` 即是 `block_t`、`future_t`、`T` 三种类型的和类型，即任意时刻，`store_t` 存的值是上述三种类型的一种。`block_t` 可以通过 `async` 调用进入异步计算模式，即转变为 `future_t`，而两者均在`get` 时转换为 `T` 类型存下来。 

`transform` 函数和 `|` 运算符用于把一个函数应用到该类型上，产生一个新的 `lazy_type_t` 的值。这里用到了一个模板 `return_type_t`，这是用来计算类型 `Y` 的返回值类型的。它的实现我是抄的 Stack Overflow 上的答案。链接在[这里](https://stackoverflow.com/questions/27822277/finding-out-the-return-type-of-a-function-lambda-or-function)。

最终实现的效果如下，以下代码节选自 [lazy.cpp](https://github.com/nicekingwei/steak/blob/master/examples/lazy.cpp)

```c++
auto l4 = lazy_call(time_consuming_compute).async();

sleep(1);

auto l1 = lazy_type_t(1);
auto l2 = l1.transform([](int x) { return 'a'; });
const auto l3 = lazy_call([]() {
    cout << "eval l3\n";
    return 'v';
});

cout << l2 << endl;
cout << l3 << endl;

cout << l4 << endl;
cout << l4 << endl;

lazy_type_t<std::pair<int, char>> l5(std::pair(1, 'a'));
cout << l5.get().first;
f(l5);

auto l6 = lazy_type_t(1)
    | [](int x) { return x + 1; }
| [](int x) { return x * 2; }
| [](int x) {
    cout << x << endl;
    return "hello world";
};

cout << l6 << endl;
```



## 积类型

单纯实现积类型非常简单，直接使用 `std::tuple` 即可，但在支持模式匹配路上遇到了许多困难，最后我选择了自己实现积类型 `zipped_pair_t`。

首先定义一个接收任意数量的类型参数的实现

```c++
template <class... T>
struct zipped_pair_t
{
    template <typename... K>
    bool match(K...)
    {
        return true;
    }
};
```

然后进行特化，首先需要用 `lazy_type_t` 存一个数据，然后定义各种情况下的模式匹配函数，区别对待左值、右值和占位符。模式匹配时，碰到左值则进行数据绑定（在这里是拷贝），碰到右值进行比较，碰到占位符默认返回成功。

```c++
template <typename T1>
struct zipped_pair_t<T1>
{
    lazy_type_t<T1> data;

    zipped_pair_t() {}

    zipped_pair_t(const T1 &x) { data = x; }

    zipped_pair_t(const lazy_type_t<T1> &x) { data = x; }

    bool operator==(const zipped_pair_t<T1> &x) const
    {
        return x.data == data;
    }

    bool match(std::pair<T1 &, place_holder_t> v1)
    {
        v1.first = data.get();
        return true;
    }

    bool match(std::pair<T1 &&, place_holder_t> v1)
    {
        return v1.first == data.get();
    }

    bool match(T1 &v1)
    {
        v1 = data.get();
        return true;
    }

    bool match(T1 &&v1)
    {
        return v1 == data.get();
    }
    
	// ......
};
```

然后是多个参数的情况，这里采用了一个递归定义的类模板，进行具体处理时，只需处理第一个参数，然后对第二个参数递归对应的处理函数。成员函数的具体实现略去。

```c++
template <typename T1, typename... T>
struct zipped_pair_t<T1, T...> : public std::pair<lazy_type_t<T1>, zipped_pair_t<T...>>
{
	// .......
};
```



对于传进来进行模式匹配的参数，我定义了一个 `forward_and_zip` 函数将他们打包成 `zipped_pair`，并且通过完美转发保留了他们原本的类型。

```c++
inline auto forward_and_zip()
{
    return _;
}

template <typename T1>
inline auto forward_and_zip(T1 &&v1)
{
    auto sec = _;
    return std::pair<T1, decltype(sec)>(std::forward<T1>(v1), std::forward<decltype(sec)>(sec));
}

template <typename T1, typename... Ts>
inline auto forward_and_zip(T1 &&v1, Ts &&... vs)
{
    auto sec = forward_and_zip<Ts...>(std::forward<Ts>(vs)...);
    return std::pair<T1, decltype(sec)>(std::forward<T1>(v1), std::forward<decltype(sec)>(sec));
}
```



### 和类型

和类型直接封装 `std::variant`，并提供模式匹配接口即可。

```c++
template <typename... T>
struct data_class_t : public std::variant<T...>
{
    using data_class_label = char;

    data_class_t() {}

    template <typename K>
    data_class_t(const K &x) : std::variant<T...>(x) {}

    template <typename G, typename S>
    inline bool match(ghost_t<G, S> t)
    {
        return search_t<sizeof...(T) - 1, std::variant<T...>>::search(&t, this);
    }

    bool operator==(const data_class_t<T...> &x) const
    {
        return search_t<sizeof...(T) - 1, std::variant<T...>>::compare(&x, this);
    }

    std::ostream &show(std::ostream &out) const
    {
        return search_t<sizeof...(T) - 1, std::variant<T...>>::show(out, this);
    }

    auto get()
    {
        return *this;
    }
};
```

在类模板参数不固定的情况下，遍历每个模板参数显得有些困难，于是不得不采用一些取巧的方法。上面出现的 `search_t` 就是这样的帮助递归遍历每个模板参数的辅助类。

```c++
template <int index, typename V>
struct search_t
{
	static std::ostream &show(std::ostream &out, const V *var)
    {
        try
        {
            auto &data = std::get<index>(*var);
            out << data;
            return out;
        }
        catch (std::bad_variant_access &)
        {
            return search_t<index - 1, V>::show(out, var);
        }
    }
    // ......
};

template <typename V>
struct search_t<-1, V>
{
    static std::ostream &show(std::ostream &out, const V *)
    {
        return out;
    }
    
    // ......
};
```

上面这段节选了 show 函数，即将一个 `std::variant` 打印出来的函数。递归尝试 `std::variant` 的类型，失败就尝试下一个类型，成功就打印该变量。



## 用法

你可以通过宏来使用 Steak 语言，大概长这样：

```c++
RegCons(Nil) RegCons(Cons)
Data(Va,List,RealType(Nil),RealType(Cons,a,List<a>))
    Cons0(Va,Nil,List<a>)
    Cons2(Va,Cons,List<a>,a,List<a>)
DerivingShow(Va,List<a>)

RegCons(Nothing) RegCons(Just)
Data(Va,Maybe,RealType(Nothing),RealType(Just,a))
    Cons0(Va,Nothing,Maybe<a>)
    Cons1(Va,Just,Maybe<a>,a)
DerivingShow(Va,Maybe<a>)

RegCons(Z) RegCons(S)
Data(V,Peano,RealType(Z),RealType(S,Peano))
    Cons0(V,Z,Peano)
    Cons1(V,S,Peano,Peano)
DerivingShow(V,Peano)


Va std::ostream& operator << (std::ostream& out,List<a> l)
{
    out<<'[';
    bool first=true;
    while(true)
    {
        a x;
        With(l)
            Case(Cons,x,l)
                if(first) first=false;
                else out<<',';
                out<<x;
            Case(Nil)
                break;
        EndWith()
    }
    return out<<']';
}

int maybe_sum(steak::lazy_type_t<List<Maybe<int>>> l)
{
    int x=0,y=0;
    while(1)
    {
        With(l)
            Case(Cons,UnZip(Just,y),l)
                x+=y;
            Case(Nil)
                break;
            Case(Cons,UnZip(Nothing),l)
                ;            
        EndWith()
    }
    return x;
}
```

或者使用我用 Haskell 写的编译器进行代码生成，代码会清爽一些：

```c++
template<typename a>
dataclass Maybe
{
    Maybe<a> Nothing();
    Maybe<a> Just(a);
};

template<typename a>
dataclass List
{
    List<a> Nil();
    List<a> Cons(a,List<a>);
};

int maybe_sum(List<Maybe<int>> l)
{
    int x=0,y=0;
    bool flag=true;
    while(flag)
    {
        match(l)
        {
            case Cons(Just(y),l):
                x+=y;
                break;
            case Cons(Nothing(),l):
                break;
            case Nil():
                flag=false;
                break;
        }
    }
    return x;
}
```



## 结尾

Steak 语言运行时的核心就是这些啦，对于这些需求，我的实现方式可能也不是最好的，欢迎大家在评论区讨论 C++ 更好的用法。没展示出来的代码都是用来处理一些边界情况，或让代码看起来更漂亮的。



（给自己打个广告，我最近在找工作，如果各位朋友知道有 PL、编译器、DB 相关的岗位，可以私信告诉我，谢谢大家！）
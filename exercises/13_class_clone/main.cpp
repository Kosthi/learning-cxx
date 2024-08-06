#include "../exercise.h"
#include <cstring>

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    DynFibonacci(int capacity_): cache(new size_t[capacity_]), cached(1), capacity(capacity_) {
        cache[0] = 0;
        if (capacity > 1) {
            cache[1] = 1;
        }
    }

    DynFibonacci(DynFibonacci const &other): cache(new size_t[other.capacity]), cached(other.cached), capacity(other.capacity) {
        std::memcpy(cache, other.cache, (other.cached + 1) * sizeof(size_t));
    }

    ~DynFibonacci() {
        delete []cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        if (i <= cached) {
            return cache[i];
        }
        if (i + 1 >= capacity) {
            // Reallocate cache if needed
            size_t *newCache = new size_t[capacity + 1];
            std::memcpy(newCache, cache, cached * sizeof(size_t));
            delete []cache;
            cache = newCache;
            ++capacity;
        }
        for (int cached_ = cached + 1; cached_ <= i; ++cached_, ++cached) {
            cache[cached_] = cache[cached_ - 1] + cache[cached_ - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        // std::cout << cached << std::endl;
        if (i <= cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}

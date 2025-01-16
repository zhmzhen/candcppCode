#include <iostream>
#include <optional>
#include <vector>
#include <algorithm>

std::optional<int> find_the_first_postive_value(const std::vector<int>& values) {
    for (auto& val : values) {
        if (val > 0) {
            return std::optional<int>(val);
        }
    }

    return std::nullopt;
}

std::optional<int> find_the_first_postive_value_v2(const std::vector<int>& values) {
    auto it = std::find_if(values.begin(), values.end(), [](int val) { return val > 0; });
    return it != values.end() ? std::make_optional(*it) : std::nullopt;
}

void show_backend(std::optional<std::string> backend) {
    if (backend) {
        std::cout << "==> use set backend: " << backend.value() << std::endl;
    } else {
        std::cout << "==> use default backend: CPU" << std::endl;
    }
}

int main() {
    // std::optional 简单例子
    bool is_even = true;
    std::optional<int> even_value = is_even ? std::optional<int>(128) : std::nullopt;
    if (even_value != std::nullopt) {
        std::cout << "has value, which is " << even_value.value() << std::endl;
    } else {
        std::cout << "no value" << std::endl;
    }

    // 1. std::optional 对象的构造
    // 1.0 采用 std::nullopt 初始化再调用 emplace 插入值
    std::optional<int> val0 = std::nullopt;
    val0.emplace(128);
    val0.emplace(129);
    std::cout << val0.value() << std::endl;

    // 1.1 采用 {} 初始化再调用 emplace 插入值
    std::optional<int> val1 = {};
    val1.emplace(128);
    std::cout << val1.value() << std::endl;

    // 1.2 采用 std::optional<T>(val) 初始化
    std::optional<int> val2 = std::optional<int>(128);
    std::cout << val2.value() << std::endl;

    // 1.3 采用 std::optional(val) 初始化，自动推导变量类型
    std::optional<int> val3 = std::optional(128);
    std::cout << val3.value() << std::endl;

    // 1.4 采用 std::optional<T>{val} 初始化
    std::optional<int> val4 = std::optional<int>{128};
    std::cout << val4.value() << std::endl;

    // 1.5 采用 std::optional{val} 初始化
    std::optional<int> val5 = std::optional{128};
    std::cout << val5.value() << std::endl;

    // 1.6 采用 {val} 初始化
    std::optional<int> val6 = {128};
    std::cout << val6.value() << std::endl;

    // 1.7 采用 std::make_optional<T>(val) 初始化
    std::optional<int> val7 = std::make_optional<int>(128);
    std::cout << val7.value() << std::endl;

    // 1.8 采用 std::make_optional(val) 初始化，自动推导变量类型
    std::optional<int> val8 = std::make_optional(128);
    std::cout << val8.value() << std::endl;

    std::optional<int> val9 = std::nullopt;
    std::cout << val9.value_or(-1) << std::endl;
    val9.emplace(128);
    std::cout << val9.value_or(-1) << std::endl;

    //    std::optional<int> val10 = std::nullopt;
    //    std::cout << val10.value() << std::endl;

    std::optional<int> val11 = std::nullopt;
    try {
        std::cout << val11.value() << std::endl;
    } catch (const std::bad_optional_access& e) {
        std::cout << "==> error: " << e.what() << std::endl;
    }

    // 函数调用例子
    std::vector<int> neg_values = {-1, -3, -5};
    std::vector<int> pos_values = {1, 3, 5};

    auto result1 = find_the_first_postive_value_v2(pos_values);
    if (result1.has_value()) {
        std::cout << result1.value() << std::endl;
    }
    if (result1 != std::nullopt) {
        std::cout << result1.value() << std::endl;
    }
    if (result1) {
        std::cout << result1.value() << std::endl;
    }
    if (result1) {
        std::cout << *result1 << std::endl;
    }

    // try-catch 示例
    try {
        std::cout << result1.value() << std::endl;
    } catch (const std::bad_optional_access& e) {
        std::cout << "==> error: " << e.what() << std::endl;
    }

    show_backend(std::nullopt);
    show_backend(std::make_optional("CUDA"));

    auto my_backend = std::optional<std::string>{"MPS"};
    show_backend(my_backend);
    my_backend.emplace("DSP");
    show_backend(my_backend);

    std::optional<std::vector<int>> res = std::optional<std::vector<int>>({1, 2, 3});
    std::cout << res.value()[0] << std::endl;
}


#pragma once

#include <memory>
#include <type_traits>
#include <functional>

namespace SimpleSTL
{

template <typename FnSig>
struct Function {
    static_assert(!std::is_same_v<FnSig, FnSig>, "not a valid function signature");
};

template <typename Ret, typename ...Args>
struct Function<Ret(Args...)> {
private:
    struct FuncBase {
        virtual Ret call(Args ...args) = 0;
        virtual ~FuncBase() = default;
    };

    template <typename F>
    struct FuncImpl : FuncBase {
        F m_f;

        FuncImpl(F f) : m_f(std::move(f)) {}

        virtual Ret call(Args ...args) override {
            return m_f(std::forward<Args>(args)...);
        }
    };

    std::shared_ptr<FuncBase> m_base;

public:
    Function() = default;

    template <class F, class = std::enable_if_t<std::is_invocable_r_v<Ret, F &, Args...>>>
    Function(F f) : m_base(std::make_shared<FuncImpl<F>>(std::move(f)))
    {}

    Ret operator() (Args ...args) const {
        return m_base->call(std::forward<Args>(args)...);
    }
};

}
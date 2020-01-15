#pragma once

/************************************/
// TypeList的C++11实现方式
template <typename...> struct TypeList;
template <typename T, typename... U>
struct TypeList<T, U...> {
    using Head = T;
    using Tails = TypeList<U...>;
};
template <>
struct TypeList<> {};
/************************************/

/************************************/
template <typename T>
struct TypeListForeach {
    template<typename Func>
    static bool execute(const Func &func) noexcept {
        return func.template operator()<T>();
    }
};
template <typename... T>
struct TypeListForeach<TypeList<T...>> {
    template<typename Func>
    static bool execute(const Func &func) noexcept {
        typedef TypeList<T...> List;
        if(TypeListForeach<typename List::Head>::execute(func))
            return true;
        if(TypeListForeach<typename List::Tails>::execute(func))
            return true;
        return false;
    }
};
template <>
struct TypeListForeach<TypeList<>> {
    template<typename Func>
    static bool execute(const Func &) noexcept {
        return false;
    }
};
/************************************/

#define MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class) \
    __TypeListForeach##Class##Helper__

#define MC_TYPELIST_FOREACH_HELPER_CLASS(Class) \
    MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class)()

#define MC_TYPELIST_FOREACH_TEMPLATE_HELPER_CLASS_IMPL(HelperClass, Class, ptr) \
    MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(HelperClass)<Class>(ptr)

#define MC_TYPELIST_FOREACH_TEMPLATE_HELPER_CLASS(Class) \
    MC_TYPELIST_FOREACH_TEMPLATE_HELPER_CLASS_IMPL(Class, std::remove_pointer<decltype(this)>::type, this)

#define MC_TYPELIST_FOREACH_HELPER(Class)   \
    struct MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class) {    \
        template<typename T>    \
        bool operator()() const noexcept {

#define MC_TYPELIST_FOREACH_HELPER_END()    \
        }   \
    };

#define MC_TYPELIST_FOREACH_TEMPLATE_HELPER(Class)   \
    template<typename C>    \
    struct MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class) {    \
    private:    \
        C *__d__;    \
    public: \
        MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class)(C *ptr) : __d__(ptr){}    \
        C *d_ptr() const noexcept {return __d__;}   \
        template<typename T>    \
        bool operator()() const noexcept {

#define MC_TYPELIST_FOREACH_TEMPLATE_HELPER_FRIEND(Class) \
    template<typename T> \
    friend struct MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class);

#define MC_TYPELIST_FOREACH_IMPL(TypeList, HelperClass, Class, ptr)  \
    TypeListForeach<TypeList>::execute(MC_TYPELIST_FOREACH_TEMPLATE_HELPER_CLASS_IMPL(HelperClass, Class, ptr));

#define MC_TYPELIST_FOREACH(TypeList, Class)  \
    MC_TYPELIST_FOREACH_IMPL(TypeList, Class, std::remove_pointer<decltype(this)>::type, this)
    

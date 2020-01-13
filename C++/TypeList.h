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
    static bool execute(const Func &func) {
        return func.template operator()<T>();
    }
};
template <typename... T>
struct TypeListForeach<TypeList<T...>> {
    template<typename Func>
    static bool execute(const Func &func) {
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
    static bool execute(const Func &) {
        return false;
    }
};
/************************************/

#define MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class) \
    __TypeListForeach##Class##Helper__

#define MC_TYPELIST_FOREACH_HELPER_CLASS(Class) \
    MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class)()

#define MC_TYPELIST_FOREACH_TEMPLATE_HELPER_CLASS(Class) \
    MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class)<Class>(this)

#define MC_TYPELIST_FOREACH_HELPER(Class)   \
    struct MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class) {    \
        template<typename T>    \
        bool operator()() const {

#define MC_TYPELIST_FOREACH_HELPER_END()    \
        }   \
    };

#define MC_TYPELIST_FOREACH_TEMPLATE_HELPER(Class)   \
    template<typename C>    \
    struct MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class) {    \
    private:    \
        C *d;    \
    public: \
        MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class)(C *ptr) : d(ptr){}    \
        template<typename T>    \
        bool operator()() const {

#define MC_TYPELIST_FOREACH_TEMPLATE_HELPER_FRIEND(Class) \
    template<typename T> \
    friend struct MC_TYPELIST_FOREACH_HELPER_CLASS_NAME(Class);

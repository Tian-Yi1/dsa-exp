#pragma once
#include <iterator>
#include <type_traits>

// 全局函数::dispose,用于单项链表,释放由begin开始的链表
// 适配多种 iterator/指针 表现：
// - 如果传入的是原始指针（node*），直接 delete
// - 否则尝试使用 operator-> / base() / get() / node 成员来取得可删除的原始指针
// 若无法取得可删除指针，会在编译时报错，提示无法释放该迭代器类型
namespace dsa_detail {
	template <typename Itr>
	auto get_deletable_ptr(Itr p) {
		if constexpr (std::is_pointer_v<Itr>) {
			return p;
		} else if constexpr (requires { p.operator->(); }) {
			return p.operator->();
		} else if constexpr (requires { p.base(); }) {
			return p.base();
		} else if constexpr (requires { p.get(); }) {
			return p.get();
		} else if constexpr (requires { p.node; }) {
			return p.node;
		} else {
			static_assert(sizeof(Itr) == 0, "dispose: 无法从迭代器类型提取可删除的原始指针，请传入 node* 或为迭代器提供 base()/get()/operator->()/node 成员。");
		}
	}
}

// 带 head 参数的版本
template <std::input_iterator Itr, typename TII>
void dispose(Itr begin, TII head) {
	Itr q = begin;
	Itr p;
	while (q != Itr{}) {
		p = q;
		++q;
		auto raw = dsa_detail::get_deletable_ptr(p);
		delete raw;
	}
	delete head;
}

// 不带 head 参数的版本
template <std::input_iterator Itr, typename TII>
void dispose(Itr begin) {
	Itr q = begin;
	Itr p;
	while (q != Itr{}) {
		p = q;
		++q;
		auto raw = dsa_detail::get_deletable_ptr(p);
		delete raw;
	}
}
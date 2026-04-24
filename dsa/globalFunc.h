#pragma once
#include <iterator>
//全局函数::dispose,用于单项链表,释放由begin开始的链表
template <std::input_iterator Itr,typename TII>
void dispose(Itr begin,TII head) {
	Itr q = begin;
	Itr p;
	while (q != Itr{}) {
		p = q;
		++q;
		delete p;
	}
	delete head;
}
template <std::input_iterator Itr, typename TII>
void dispose(Itr begin) {
	Itr q = begin;
	Itr p;
	while (q != Itr{}) {
		p = q;
		++q;
		delete p;
	}
}
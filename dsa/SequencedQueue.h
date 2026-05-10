/**
 * @file Queue.h
 * @brief 自定义顺序队列 (循环数组实现)
 */

#pragma once

#include <cstddef>
#include <stdexcept>
#include <memory>
#include <utility>

 /**
  * @brief 顺序队列类模板
  * @tparam T 队列中元素的类型
  * @tparam Allocator 内存分配器类型，默认为 std::allocator<T>
  *
  * 支持的操作：
  * - push / emplace : 在队尾插入元素
  * - pop            : 移除队首元素
  * - front / back   : 访问队首/队尾元素
  * - empty / size   : 队列状态查询
  * - clear / swap   : 清空或交换两个队列
  * - 拷贝/移动构造及赋值
  */

template<typename T, typename Allocator = std::allocator<T>>
class SequencedQueue {
public:
	using value_type = T;
	using allocator_type = Allocator;
	using size_type = std::size_t;
	using reference = value_type&;
	using const_reference = const value_type&;
private:
	allocator_type alloc_;///< 内存分配器
	T* buffer_;///< 动态数组指针
	size_type capacity_;///< 数组容量
	size_type head_;///< 队首索引
	size_type tail_;///< 队尾索引
	size_type count_;///< 当前元素数量
	// 辅助函数：循环前进索引
	size_type advance(size_type idx, size_type step = 1) const noexcept {
		return (idx + step) % capacity_;
	}
	// 辅助函数：销毁有效范围内的所有元素
	void destroy_elements() noexcept {
		if (!buffer_) return;
		size_type idx = head_;
		for (size_type i = 0; i < count_; ++i) {
			std::allocator_traits<allocator_type>::destroy(alloc_, buffer_ + idx);
			idx = advance(idx);
		}
	}
	// 辅助函数：当容量不足时进行扩容(扩容因子:2)
	void reallocate(size_type new_capacity) {
		T* new_buffer = std::allocator_traits<allocator_type>::allocate(alloc_, new_capacity);
		size_type new_tail = 0;
		size_type idx = head_;
		for (size_type i = 0; i < count_; ++i) {
			std::allocator_traits<allocator_type>::construct(alloc_, new_buffer + new_tail,
				std::move_if_noexcept(buffer_[idx]));
			idx = advance(idx);
			++new_tail;
		}
		destroy_elements();
		std::allocator_traits<allocator_type>::deallocate(alloc_, buffer_, capacity_);
		buffer_ = new_buffer;
		capacity_ = new_capacity;
		head_ = 0;
		tail_ = count_;
	}
public:
	/**
	 * @brief 默认构造函数，创建一个空队列
	 * @param capacity 初始容量，默认为16
	 * @param alloc    内存分配器
	 * @throw std::bad_alloc 如果初始内存分配失败
	 */
	explicit SequencedQueue(size_type capacity = 16, const allocator_type& alloc = allocator_type()) :
		alloc_(alloc), buffer_(nullptr), capacity_(capacity), head_(0), tail_(0), count_(0) {
		buffer_ = std::allocator_traits<allocator_type>::allocate(alloc_, capacity_);
	}
	/**
	 * @brief 拷贝构造函数
	 * @param other 被拷贝的队列
	 */
	SequencedQueue(const SequencedQueue& other) :alloc_(std::allocator_traits<allocator_type>::select_on_container_copy_construction(other.alloc_)), buffer_(nullptr), capacity_(other.capacity_), head_(0), tail_(0), count_(other.count_) {
		buffer_ = std::allocator_traits<allocator_type>::allocate(alloc_, capacity_);
		size_type idx = other.head_;
		for (size_type i = 0; i < count_; ++i) {
			std::allocator_traits<allocator_type>::construct(alloc_, buffer_ + i, other.buffer_[idx]);
			idx = other.advance(idx);
		}
		tail_ = count_;
	}
	/**
	* @brief 移动构造函数
	* @param other 被移动的队列，移动后变为空状态
	*/
	SequencedQueue(SequencedQueue&& other) noexcept :alloc_(std::move(other.alloc_)), buffer_(std::exchange(other.buffer_, nullptr)), capacity_(std::exchange(other.capacity_, 0)), head_(std::exchange(other.head_, 0)), tail_(std::exchange(other.tail_, 0)), count_(std::exchange(other.count_, 0)) {}
	/**
	 * @brief 析构函数，释放所有资源
	 */
	~SequencedQueue() noexcept {
		clear();
		if (buffer_) {
			std::allocator_traits<allocator_type>::deallocate(alloc_, buffer_, capacity_);
		}
	}
	/**
	 * @brief 拷贝赋值运算符
	 * @param other 被赋值的队列
	 * @return *this
	 */
	SequencedQueue& operator=(const SequencedQueue& other) {
		if (this != &other) {
			if constexpr (std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value) {
				alloc_ = other.alloc_;
			}
			SequencedQueue temp(other);;
			swap(temp);
		}
		return *this;
	}
	/**
	 * @brief 移动赋值运算符
	 * @param other 被移动的队列，移动后变为空状态
	 * @return *this
	 */
	SequencedQueue& operator=(SequencedQueue&& other) noexcept {
		if (this != &other) {
			clear();
			if (buffer_) {
				std::allocator_traits<allocator_type>::deallocate(alloc_, buffer_, capacity_);
			}
			buffer_ = std::exchange(other.buffer_, nullptr);
			capacity_ = std::exchange(other.capacity_, 0);
			head_ = std::exchange(other.head_, 0);
			tail_ = std::exchange(other.tail_, 0);
			count_ = std::exchange(other.count_, 0);
			if constexpr (std::allocator_traits<allocator_type>::propagate_on_container_move_assignment::value) {
				alloc_ = std::move(other.alloc_);
			}
		}
		return *this;
	}
	/**
	* @brief 访问队首元素
	* @return 队首元素的引用
	* @throw std::out_of_range 如果队列为空
	*/
	reference front() {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		}
		return buffer_[head_];
	}
	/**
	* @brief 访问队首元素 (const 版本)
	* @return 队首元素的常引用
	* @throw std::out_of_range 如果队列为空
	*/
	const_reference front() const {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		}
		return buffer_[head_];
	}
	/**
	 * @brief 访问队尾元素
	 * @return 队尾元素的引用
	 * @throw std::out_of_range 如果队列为空
	 */
	reference back() {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		}
		size_type back_idx = (tail_ == 0) ? capacity_ - 1 : tail_ - 1;
		return buffer_[back_idx];
	}
	/**
	 * @brief 访问队尾元素 (const 版本)
	 * @return 队尾元素的常引用
	 * @throw std::out_of_range 如果队列为空
	 */
	const_reference back() const {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		}
		size_type back_idx = (tail_ == 0) ? capacity_ - 1 : tail_ - 1;
		return buffer_[back_idx];
	}
	/**
	* @brief 判断队列是否为空
	* @return true 如果队列中不含任何元素
	*/
	bool empty() const noexcept {
		return count_ == 0;
	}
	/**
	* @brief 获取队列中元素个数
	* @return 当前元素数量
	*/
	size_type size() const noexcept {
		return count_;
	}
	/**
	* @brief 获取当前底层数组的容量 (非标准 queue 扩展)
	* @return 可容纳元素的最大数量
	*/
	size_type capacity() const noexcept {
		return capacity_;
	}
	/**
	* @brief 在队尾插入一个元素 (拷贝版本)
	* @param value 要插入的元素
	* @throw std::bad_alloc 如果内存分配失败
	*/
	void push(const value_type& value) {
		if (count_ == capacity_) {
			reallocate(capacity_ * 2);
		}
		std::allocator_traits<allocator_type>::construct(alloc_, buffer_ + tail_, value);
		tail_ = advance(tail_);
		++count_;
	}
	/**
	* @brief 在队尾插入一个元素 (移动版本)
	* @param value 要插入的元素
	* @throw std::bad_alloc 如果内存分配失败
	*/
	void push(value_type&& value) {
		if (count_ == capacity_) {
			reallocate(capacity_ * 2);
		}
		std::allocator_traits<allocator_type>::construct(alloc_, buffer_ + tail_, std::move(value));
		tail_ = advance(tail_);
		++count_;
	}
	/**
	 * @brief 在队尾原位构造一个元素
	 * @tparam Args 构造参数类型包
	 * @param args 传递给元素构造函数的参数
	 * @throw std::bad_alloc 如果内存分配失败
	 */
	template<typename... Args>
	void emplace(Args&&... args) {
		if (count_ == capacity_) {
			reallocate(capacity_ * 2);
		}
		std::allocator_traits<allocator_type>::construct(alloc_, buffer_ + tail_, std::forward<Args>(args)...);
		tail_ = advance(tail_);
		++count_;
	}
	/**
	 * @brief 移除队首元素
	 * @note 如果队列为空，行为未定义 (出于效率考虑不检查，但处于调试目的可添加断言)
	 *       调用前建议先检查 empty() 是否为空。
	 */
	void pop() {
		if (!empty()) {
			std::allocator_traits<allocator_type>::destroy(alloc_, buffer_ + head_);
			head_ = advance(head_);
			--count_;
		}
	}
	/**
	 * @brief 清空队列中所有元素
	 * @post empty() == true, size() == 0
	 */
	void clear() noexcept {
		destroy_elements();
		head_ = 0;
		tail_ = 0;
		count_ = 0;
	}
	/**
	 * @brief 交换两个队列的内容
	 * @param other 要交换的另一队列
	 */
	void swap(SequencedQueue& other) noexcept {
		using std::swap;
		swap(alloc_, other.alloc_);
		swap(buffer_, other.buffer_);
		swap(capacity_, other.capacity_);
		swap(head_, other.head_);
		swap(tail_, other.tail_);
		swap(count_, other.count_);
		if constexpr (std::allocator_traits<allocator_type>::propagate_on_container_swap::value) {
			swap(alloc_, other.alloc_);
		}
	}
	/**
	 * @brief 判断两个队列是否相等
	 * @param lhs 左队列
	 * @param rhs 右队列
	 * @return true 如果 size 相等且对应元素依次相等
	 */
	friend bool operator==(const SequencedQueue& lhs, const SequencedQueue& rhs) {
		if (lhs.size() != rhs.size()) return false;
		size_type lidx = lhs.head_;
		size_type ridx = rhs.head_;
		for (size_type i = 0; i < lhs.count_; ++i) {
			if (lhs.buffer_[lidx] != rhs.buffer_[ridx]) return false;
			lidx = lhs.advance(lidx);
			ridx = rhs.advance(ridx);
		}
		return true;
	}
	/**
	 * @brief 判断两个队列是否不等
	 * @param lhs 左队列
	 * @param rhs 右队列
	 * @return true 如果 !(lhs == rhs)
	 */
	friend bool operator!=(const SequencedQueue& lhs, const SequencedQueue& rhs) {
		return !(lhs == rhs);
	}
};
/**
 * @brief 特化 swap 函数，便于在非成员上下文中调用
 * @param a 队列对象
 * @param b 另一队列对象
 */
template<typename T, typename Alloc>
void swap(SequencedQueue<T, Alloc>& a, SequencedQueue<T, Alloc>& b) noexcept(noexcept(a.swap(b))) {
	a.swap(b);
}
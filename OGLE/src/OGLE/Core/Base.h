#pragma once
#include <memory>

#include "OGLE/Core/PlatformDetection.h"

#ifdef OGLE_DEBUG
#if defined(OGLE_PLATFORM_WINDOWS)
#define OGLE_DEBUGBREAK() __debugbreak()
#elif defined(OGLE_PLATFORM_LINUX)
#include <signal.h>
#define OGLE_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define OGLE_ENABLE_ASSERTS
#else
#define OGLE_DEBUGBREAK()
#endif

#define OGLE_EXPAND_MACRO(x) x
#define OGLE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define OGLE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace OGLE {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}


    template<typename T>
    class ContVector {
    public:
        // Constructor
        ContVector() = default;

        // Destructor
        ~ContVector() = default;

        // Move Constructor
        ContVector(ContVector&& other) noexcept
            : data_(std::move(other.data_)) {}

        // Copy Constructor
        ContVector(const ContVector& other) : data_(other.data_) 
        {
        }

        // Constructor taking std::initializer_list
        ContVector(std::initializer_list<T> initList) : data_(initList) {}

        // Move Assignment Operator
        ContVector& operator=(ContVector&& other) noexcept {
            if (this != &other) {
                data_ = std::move(other.data_);
            }
            return *this;
        }

        // Swap the contents of two ContiguousVector objects
        void swap(ContVector& other) noexcept {
            data_.swap(other.data_);
        }

        // Insert a single element at a given index
        void insert(size_t index, const T& value) {
            data_.insert(data_.begin() + index, value);
        }

        // Add element to vector
        template<typename... Args>
        void emplace_back(Args&&... args) {
            data_.emplace_back(std::forward<Args>(args)...);
        }

        // Insert all elements from another ContVector at the end
        void insert(const ContVector& other) {
            insert(other.data_);
        }

        // Insert elements from an array
        template<size_t N>
        void insert(const std::array<T, N>& arr) {
            insert(std::vector<T>(arr.begin(), arr.end()));
        }

        void insert(const std::vector<T>& vec) {
            data_.insert(data_.end(), vec.begin(), vec.end());
        }

        // Erase an element at a given index
        void erase(size_t index) {
            data_.erase(data_.begin() + index);
        }

        // Erase elements in the range [first, last)
        void erase(size_t first, size_t last) {
            data_.erase(data_.begin() + first, data_.begin() + last);
        }

        // Resize the vector
        void resize(size_t newSize) {
            data_.resize(newSize);
        }

        // Reserve memory for elements
        void reserve(size_t m_Capacity) {
            data_.reserve(m_Capacity);
        }

        // Clear all elements and release memory
        void clear() {
            data_.clear();
            data_.shrink_to_fit();
        }

        // Check if the vector is empty
        bool empty() const {
            return data_.empty();
        }

        // Return number of elements in vector
        size_t size() const {
            return data_.size();
        }

        // Access element at index (read-only)
        const T& operator[](size_t index) const {
            return data_[index];
        }

        // Access element at index (read/write)
        T& operator[](size_t index) {
            return data_[index];
        }

        // Remove the last element
        void pop_back() {
            data_.pop_back();
        }

        // Iterator functions
        typename std::vector<T>::iterator begin() { return data_.begin(); }
        typename std::vector<T>::iterator end() { return data_.end(); }
        typename std::vector<T>::const_iterator cbegin() const { return data_.cbegin(); }
        typename std::vector<T>::const_iterator cend() const { return data_.cend(); }

        // Return pointer to contiguous memory block
        T* data() {
            return data_.data();
        }
     
        std::vector<Ref<T>>* GetSubset(size_t startIndex, size_t length, bool autoResize) {
            if (autoResize && (startIndex >= size() || startIndex + length > size())) {
                resize(startIndex + length);
            }

            // Calculate endIndex based on startIndex and length
            size_t endIndex = std::min(startIndex + length, data_.size());

            // Create a vector of references to elements in data_
            std::vector<Ref<T>>* subset = new  std::vector<Ref<T>>();
            subset->reserve(endIndex - startIndex); // Reserve space for efficiency

            // Transform elements in the specified range into shared pointers and add them to subset
            std::transform(data_.begin() + startIndex, data_.begin() + endIndex, std::back_inserter(*subset),
                [](T& elem) -> Ref<T> { return std::shared_ptr<T>(&elem, [](T*) {}); });

            return subset;
        }


    private:
        std::vector<T> data_;
    };

}

#include "OGLE/Debug/Assert.h"
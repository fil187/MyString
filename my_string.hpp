#include <cstddef>
#include <stdexcept>
#include <cstdint>

/**
 * @brief A dynamically allocated mutable string.
 * 
 * @invariant capacity > 0
 * @invariant size <= capacity
 * @invariant data != nullptr
 * @invariant data points to an allocated array of exactly this->capacity chars.
 */
class MyString {

private:

    size_t size;
    size_t capacity;
    char* data;

    static constexpr size_t DEFAULT_CAPACITY = 128;

public:
    
    /**
     * @brief Construct an empty string with the default capacity.
     */
    MyString() : MyString(DEFAULT_CAPACITY) {}

    /**
     * @brief Construct an empty string with the specified capacity.
     * 
     * @param capacity The initial storage capacity in characters.
     * @throws std::invalid_argument if capacity == 0
     */
    MyString(size_t capacity) : size(0), capacity(capacity) {
        if (capacity == 0)
            throw std::invalid_argument("capacity must be greater than 0");

        data = new char[capacity];
    }

    /**
     * @brief Constructs a MyString from the contents of a std::string.
     * 
     * @par Complexity
     *      O(m)
     * 
     * @param source The std::string whose contents are copied into this MyString.
     */
    MyString(const std::string& source) : size(source.length()), capacity(std::max(DEFAULT_CAPACITY, source.length())) {
        data = new char[std::max(DEFAULT_CAPACITY, source.length())];
        std::copy(source.data(), source.data() + source.length() + 1, data);
    }

    /**
     * @return The number of stored elements.
     */
    size_t length() const {
        return size;
    }

    /**
     * @brief Returns A std::string containing the characters of this string followed by the characters of source.
     * 
     * @par Complexity
     *      O(n + m)
     */
    std::string operator+(const std::string& source) const {
        char* concatination = new char[size + source.length()];
        std::copy(data, data + size, concatination);
        std::copy(source.data(), source.data() + source.length() + 1, concatination + size);
        std::string result(concatination);
        delete[] concatination;
        return result;
    }

    /**
     * @brief Replaces the contents of this string with those of source.
     * 
     * @par Complexity
     *      - Worst case O(n)
     * 
     * @throws std::bad_alloc if the allocation fails
     * 
     * @post The contents of this String are equal to source.
     * @post The length of this String equals the length of the source.
     */
    void operator=(const std::string& source) {
        if (capacity <= source.length())
            resize(std::max(2 * capacity, source.length()));
        
        std::copy(source.data(), source.data() + source.length() + 1, data);
        size = source.length();
    }

    /**
     * @brief Replaces the contents of this string with those of source.
     * 
     * @par Complexity
     *      Worst case O(n)
     * 
     * @post The contents of this String are equal to source.
     * @post The length of this String equals the length of the source.
     */
    void operator=(const MyString& source) {
        char* old_data = data;
        data = new char[source.capacity];
        std::copy(source.data, source.data + source.size, data);
        capacity = source.capacity;
        size = source.size;
        delete[] old_data;
    }

    /**
     * @brief Appends the contents of source to this String.
     * 
     * @par Complexity
     *      Worst case O(n)
     * 
     * @post This String contains its original contents followed by the contents of source.
     * @post The length of this String is equal to its previous length plus the length of the source.
     */
    MyString& operator+=(const std::string& source) {
        *this = *this + source;
        return *this;
    }

    /**
     * @brief Returns true if this String and source contain the same characters, otherwise false.
     * 
     * @par Complexity
     *      Worst case O(n)
     */
    bool operator==(const std::string& source) const {
        
        if (source.length() != size)
            return false;
        
        for (size_t i = 0; i < size; i++)
            if (data[i] != source[i])
                return false;
        
        return true;
    }
    
    /**
     * @brief Returns true if this String and source contain the same characters, otherwise false.
     */
    bool operator==(const MyString& source) const {
        
        if (source.length() != size)
            return false;
        
        for (size_t i = 0; i < size; i++)
            if (data[i] != source[i])
                return false;
        
        return true;
    }

    /**
     * @throws std::out_of_range if idx >= the length of this String.
     * @return the character at the specified index.
     */
    char operator[](size_t idx) const {
        if (idx >= size)
            throw std::out_of_range("index out of range");
        
        return data[idx];
    }
    
    /**
     * @brief Returns whether this string begins with source.
     */
    bool start_with(const std::string& source) const {

        if (source.length() > size)
            return false;

        for (size_t i = 0; i < source.length(); i++)
            if (data[i] != source.at(i))
                return false;
        
        return true;
    }

    /**
     * @brief Returns true if source occurs within this String, otherwise false.
     * 
     * @par Complexity 
     *      Average case O(n + m)
     *      Worst case O(n * m)
     * 
     * @param source The substring to search for.
     */
    bool contains(const std::string& source) const {

        if (source.length() > size)
            return false;
        if (source.length() == 0)
            return true;
        
        auto hash = [] (const char* head, size_t length) {
            uint64_t hash = 0;
            for (size_t i = 0; i < length; i++)
                hash = hash * 131 + static_cast<uint64_t>(head[i]);
            return hash;
        };

        auto power = [] (size_t length) {
            uint64_t power = 1;
            for (size_t i = 1; i < length; i++)
                power *= 131;
            return power;
        };

        const size_t len = source.length();
        const uint64_t step_back = power(len);
        uint64_t source_hash = hash(source.data(), len);
        uint64_t current_hash = hash(data, len);
        
        if (source_hash == current_hash) {
            bool match = true;
            for (size_t i = 0; i < len; i++)
                if (data[i] != source[i]) {
                    match = false;
                    break;
                }
            if (match)
                return true;
        }
        
        for (size_t i = 1; i <= size - len; i++) {
            current_hash -= static_cast<uint64_t>(data[i - 1]) * step_back;
            current_hash *= 131;
            current_hash += static_cast<uint64_t>(data[i + len - 1]);
            if (source_hash == current_hash) {
                bool match = true;
                for (size_t j = 0; j < len; j++)
                    if (data[j + i] != source[j]) {
                        match = false;
                        break;
                    }
                if (match)
                    return true;
            }
        }

        return false;
    }

    ~MyString() {
        delete[] data;
    }

private:
    
    /**
     * @par Complexity
     *      Worst case O(n)
     * 
     * @throws std::bad_alloc if the allocation fails
     * 
     * @pre new_capacity > 0
     * @post The contents of this string are unchanged
     * @post The capacity of this string is equal to new_capacity
     */
    void resize(size_t new_capacity) {
        char* new_data = new char[new_capacity];

        if (new_data == nullptr)
            throw std::bad_alloc();

        std::copy(data, data + size, new_data);
        char* old_data = data;
        data = new_data;
        delete[] old_data;
        capacity = new_capacity;
    }

};
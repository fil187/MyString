#include <cstddef>
#include <stdexcept>
#include <cstdint>

class MyString {

private:
    
    /**
     * @invariant capacity > 0
     * @invariant size <= capacity
     * @invariant data != nullptr
     * @invariant data points to an allocated array of exactly this->capacity chars.
     */
    size_t size;
    size_t capacity;
    char* data;

    static constexpr size_t DEFAULT_CAPACITY = 128;

public:
    
    /**
     * Construct an empty Heap with the default capacity.
     */
    MyString() : MyString(DEFAULT_CAPACITY) {}

    /**
     * Construct an empty String with the specified capacity.
     * 
     * @param capacity the capacity of the string.
     * @throws std::invalid_argument if capacity == 0
     */
    MyString(size_t capacity) : size(0), capacity(capacity) {
        if (capacity == 0)
            throw std::invalid_argument("capacity must be greater than 0");

        data = new char[capacity];
    }

    /**
     * Constructs a MyString from the contents of a std::string.
     * 
     * @param source The std::string whose contents are copied into this MyString
     */
    MyString(const std::string& source) : size(source.length()), capacity(max(DEFAULT_CAPACITY, source.length())) {
        data = new char[max(DEFAULT_CAPACITY, source.length())];
        std::copy(source.data(), source.data() + source.length() + 1, data);
    }

    size_t length() const {
        return size;
    }

    /**
     * @return An std::string containing the characters of this String followed by the characters of source.
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
     * @throws std::bad_alloc if the allocation fails
     * 
     * @post The contents of this String are equal to source
     * @post The length of this String equals source.length()
     */
    void operator=(const std::string& source) {
        if (capacity <= source.length())
            resize(max(2 * capacity, source.length()));
        
        std::copy(source.data(), source.data() + source.length() + 1, data);
        size = source.length();
    }

    /**
     * @post The contents of this String are equal to source
     * @post The length of this String equals source.length()
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
     * Appends the contents of source to this String.
     * 
     * @post This String contains its original contents followed by the contents of source
     * @post The length of this String is equal to its previous length plus source.length()
     */
    MyString& operator+=(const std::string& source) {
        *this = *this + source;
        return *this;
    }

    /**
     * @return true if this String and source contain the same characters, otherwise false.
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
     * @return true if this String and source contain the same characters, otherwise false.
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
     * Returns the character at the specified index
     * 
     * @throws std::out_of_range if idx >= the length of this String
     */
    char operator[](size_t idx) const {
        if (idx >= size)
            throw std::out_of_range("index out of range");
        
        return data[idx];
    }
    
    /**
     * Checks whether this String starts with the contents of source.
     * 
     * @return true if this String begins with source, otherwise false.
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
     * Checks whether this String contains source as a substring.
     * 
     * @return true if source occurs within this String, otherwise false.
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
     * @throws std::bad_alloc if the allocation fails
     * 
     * @pre new_capacity > 0
     * @post The contents of this String are unchanged
     * @post The capacity of this String is equal to new_capacity
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

    inline static size_t max(size_t a, size_t b) {
        return (a >= b) ? a : b;
    }

};
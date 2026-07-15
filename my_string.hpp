#include <cstddef>
#include <stdexcept>
#include <cstdint>

class MyString {

private:
    
    size_t size;
    size_t capacity;
    char* data;

    static constexpr size_t DEFAULT_CAPACITY = 128;

public:
    
    MyString(): MyString(DEFAULT_CAPACITY) {
        // constructor with default capacity (128);
    }

    MyString(size_t capacity): size(0), capacity(capacity) {
        // constructor with capacity as parameter
        // throws illegal argument exception if capacity is null
        // @param capacity -> capacity to build the string with
        if (capacity == 0)
            throw std::invalid_argument("capacity must be greater than 0");

        data = new char[capacity];
    }

    MyString(const std::string& source): size(source.length()), capacity(max(DEFAULT_CAPACITY, source.length())) {
        // constructor from string source
        // @param source -> source to build the string from
        data = new char[max(DEFAULT_CAPACITY, source.length())];
        std::copy(source.data(), source.data() + source.length() + 1, data);
    }

    size_t length() const {
        return size;
    }

    std::string operator+(const std::string& source) const {
        char* concatination = new char[size + source.length()];
        std::copy(data, data + size, concatination);
        std::copy(source.data(), source.data() + source.length() + 1, concatination + size);
        std::string result(concatination);
        delete[] concatination;
        return result;
    }

    void operator=(const std::string& source) {
        if (capacity <= source.length())
            if (!resize(max(2 * capacity, source.length())))
                return;
        
        std::copy(source.data(), source.data() + source.length() + 1, data);
        size = source.length();
    }

    MyString& operator+=(const std::string& source) {
        *this = *this + source;
        return *this;
    }

    bool operator==(const std::string& source) const {
        
        if (source.length() != size)
            return false;
        
        for (size_t i = 0; i < size; i++)
            if (data[i] != source[i])
                return false;
        
        return true;
    }

    bool operator==(const MyString& source) const {
        
        if (source.length() != size)
            return false;
        
        for (size_t i = 0; i < size; i++)
            if (data[i] != source[i])
                return false;
        
        return true;
    }

    void operator=(const MyString& source) {
        char* old_data = data;
        data = new char[source.capacity];
        std::copy(source.data, source.data + source.size, data);
        capacity = source.capacity;
        size = source.size;
        delete[] old_data;
    }

    char operator[](size_t idx) const {
        // throws index out of range exception if index >= length
        if (idx >= size)
            throw std::out_of_range("index out of range");
        
        return data[idx];
    }

    bool start_with(const std::string& source) const {

        if (source.length() > size)
            return false;

        for (size_t i = 0; i < source.length(); i++)
            if (data[i] != source.at(i))
                return false;
        
        return true;
    }

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
    
    bool resize(size_t new_capacity) {
        char* new_data = new char[new_capacity];

        if (new_data == nullptr)
            return false;

        std::copy(data, data + size, new_data);
        char* old_data = data;
        data = new_data;
        delete[] old_data;
        capacity = new_capacity;
        return true;
    }

    inline static size_t max(size_t a, size_t b) {
        return (a >= b) ? a : b;
    }
};
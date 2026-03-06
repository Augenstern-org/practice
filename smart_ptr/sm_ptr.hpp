//
// Created by Neuroil on 2026/2/28.
//

#ifndef SMART_PTR_SM_PTR_HPP
#define SMART_PTR_SM_PTR_HPP

template <typename T>
class sm_ptr {
public:
    sm_ptr(T* prt = nullptr) : origin_ptr(prt), counter(new int(1)){};
    sm_ptr(const sm_ptr& other_ptr) : origin_ptr(other_ptr.origin_ptr), counter(other_ptr.counter) {
        ++(*counter);
    };
    ~sm_ptr() {
        release();
    };

    sm_ptr& operator=(const sm_ptr& other) {
        if (this != &other) {
            release();

            origin_ptr = other.origin_ptr;
            counter = other.counter;

            if (counter) {
                ++(*counter);
            }
        }
        return *this;
    }

    T& operator*() const {
        return *origin_ptr;
    }

    T* operator->() const {
        return origin_ptr;
    }

    int use_count() {
        return *counter;
    }

private:
    void release() {
        --(*counter);
        if (*counter == 0) {
            delete origin_ptr;
            delete counter;
        }
    }
    T* origin_ptr;
    int* counter;
};


#endif //SMART_PTR_SM_PTR_HPP
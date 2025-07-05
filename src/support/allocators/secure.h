// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SUPPORT_ALLOCATORS_SECURE_H
#define BITCOIN_SUPPORT_ALLOCATORS_SECURE_H

#include <support/pagelocker.h>

#include <string>

//
// Allocator that locks its contents from being paged
// out of memory and clears its contents before deletion.
//
template <typename T>
struct secure_allocator : public std::allocator<T> {
    // MSVC8 default copy constructor is broken
    using base = std::allocator<T>;
    using size_type = typename std::allocator_traits<base>::size_type;
    using difference_type = typename std::allocator_traits<base>::difference_type;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using value_type = T;
    secure_allocator() throw() {}
    secure_allocator(const secure_allocator& a) throw() : base(a) {}
    template <typename U>
    secure_allocator(const secure_allocator<U>& a) throw() : base(a)
    {
    }
    ~secure_allocator() throw() {}
    template <typename _Other>
    struct rebind {
        typedef secure_allocator<_Other> other;
    };

    T* allocate(std::size_t n)
    {
        T* p;
        p = std::allocator<T>::allocate(n);
        if (p != NULL)
            LockedPageManager::Instance().LockRange(p, sizeof(T) * n);
        return p;
    }

    void deallocate(T* p, std::size_t n)
    {
        if (p != NULL) {
            memory_cleanse(p, sizeof(T) * n);
            LockedPageManager::Instance().UnlockRange(p, sizeof(T) * n);
        }
        std::allocator<T>::deallocate(p, n);
    }
};

// This is exactly like std::string, but with a custom allocator.
typedef std::basic_string<char, std::char_traits<char>, secure_allocator<char> > SecureString;

#endif // BITCOIN_SUPPORT_ALLOCATORS_SECURE_H

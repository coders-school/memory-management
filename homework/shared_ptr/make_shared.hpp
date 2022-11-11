#pragma once

namespace my {

template <class T, class... Args>
shared_ptr<T> make_shared(Args&&... args);  // TODO:

// ------------------  OPTIONAL ---------------------------------

template <class T>
shared_ptr<T> make_shared(std::size_t N);  // NOTE:  OPTIONAL most likely

template <class T>
shared_ptr<T> make_shared();  // NOTE:  OPTIONAL most likely

template <class T>
shared_ptr<T> make_shared(std::size_t N, const std::remove_extent_t<T>& u);  // NOTE: OPTIONAL most likely

template <class T>
shared_ptr<T> make_shared(const std::remove_extent_t<T>& u);  // NOTE: OPTIONAL most likely

};  // namespace my

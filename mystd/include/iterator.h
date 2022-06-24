#ifndef MYSTD_INTERATOR_H
#define MYSTD_INTERATOR_H
#include<cstddef>

namespace mystd
{

// iterator model of 5
struct input_iterator_tag {};
struct output_iterator_tag {};
struct froward_iterator_tag :public input_iterator_tag {};
struct bidirectional_iterator_tag :public froward_iterator_tag {};
struct random_acces_iterator_tag : public bidirectional_iterator_tag {};

// iterator template
template<class Category, class T, class Distance = pridiff_t,
    class Pointer = T*, class Reference = T&>
    struct iterator
{

};





} // namespace mystd
#endif

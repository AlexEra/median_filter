#include <stdint.h>
#include <vector>
#include <algorithm>


template <class Var>
class MedianFilter {
public:
    MedianFilter(void) { }
    MedianFilter(size_t sz);
    ~MedianFilter();
    void set_size(size_t sz);
    size_t get_size(void) const;
    Var step(Var new_value);

private:
    std::vector<Var> *p_data;
    class std::vector<Var>::iterator it;
    Var last_val{0};
};

template <class Var>
MedianFilter<Var>::MedianFilter(size_t sz) {
    set_size(sz);
}

template <class Var>
MedianFilter<Var>::~MedianFilter() {
    delete p_data;
}

template <class Var>
void MedianFilter<Var>::set_size(size_t sz) {
    p_data = new std::vector<Var>(sz);
    it = p_data->begin();
}

template <class Var>
size_t MedianFilter<Var>::get_size(void) const {
    return p_data->size();
}

template <class Var>
Var MedianFilter<Var>::step(Var new_value) {
    *it = new_value;
    if (++it == p_data->end()) {
        it = p_data->begin() + (p_data->size() >> 1);
        sort(p_data->begin(), p_data->end());
        last_val = *it;
        it = p_data->begin();
    }
    return last_val;
}

#include "bloom_filter.h"
 
 
BloomFilter::BloomFilter(size_t hashes, size_t bits) : _hashes(hashes), _bits(bits) { 
    _filter.resize(bits, false);
}
 
 
void BloomFilter::add(const std::string & str) {
    for(size_t i = 0; i< _hashes; ++i){
        _filter[_get_hash(i, str)] = true;
    }
    _raw_set.insert(str);
}
 
 
bool BloomFilter::verify(const std::string &str) {
    bool f = true;
    for(size_t i = 0; i< _hashes; ++i){
        // f &= _filter[_get_hash(i, str)]; не заходило
        f = f && _filter[_get_hash(i, str)]; // зашло
    }
    if(f && !_raw_set.count(str))
        ++false_positive_cnt;
    ++cnt;
    return f;
}
 
 
double BloomFilter::getFPRate() const {
    if(cnt == 0)
        return 0;
    return static_cast<double>(false_positive_cnt)/cnt;
}
 
 
size_t BloomFilter::numberOfHashFunctions() const {
    return _hashes;
}
 
 
size_t BloomFilter::numberOfBits() const {
    return _bits;
}
 
 
inline size_t BloomFilter::_get_hash(int index, const std::string &str) const {
    return hasher(str + std::to_string(index)) % _bits;
}
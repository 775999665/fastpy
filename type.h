#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "func.h"

struct value;
typedef std::vector<value> list_t;
typedef std::string str_t;
typedef std::unordered_set<value> set_t;
typedef std::unordered_map<value, value> dict_t;
typedef struct { long start, stop, step; } range_t;
typedef range_t range_iterator_t;
typedef struct { long start, stop, step; } slice_t;
typedef struct { list_t *list; size_t index; } list_iterator_t;
struct set_iterator_t;
struct dict_iterator_t;

struct base_value {
    mutable size_t hash;
    base_value(): hash(0) {

    }
};

struct value {
    mutable size_t hash;
    union {
        bool boolval;
        long intval;
        double floatval;
        str_t *strval;
        list_t *listval;
        set_t *setval;
        dict_t *dictval;
        range_t *rangeval;
        range_iterator_t *range_iteratorval;
        slice_t *sliceval;
        list_iterator_t *list_iteratorval;
        set_iterator_t *set_iteratorval;
        dict_iterator_t *dict_iteratorval;
        void* voidval;
    };
    enum Type { NONE, BOOL, INT, FLOAT, STR, LIST, SET, DICT, RANGE, RANGE_ITERATOR, SLICE, LIST_ITERATOR, SET_ITERATOR, DICT_ITERATOR } type;
    value(): hash(0) {

    }
    
    bool operator ==(value other) const {
        return __eq__(*this, other).boolval;
    }
    
    bool operator !=(value other) const {
        return __ne__(*this, other).boolval;
    }
    
    bool operator <(value other) const {
        return __lt__(*this, other).boolval;
    }
    
    bool operator >(value other) const {
        return __gt__(*this, other).boolval;
    }
    
    bool operator <=(value other) const {
        return __le__(*this, other).boolval;
    }
    
    bool operator >=(value other) const {
        return __ge__(*this, other).boolval;
    }
    
    value operator +(value other) const {
        return __add__(*this, other);
    }
    
    value operator -(value other) const {
        return __sub__(*this, other);
    }
    
    value operator *(value other) const {
        return __mul__(*this, other);
    }
    
    value operator /(value other) const {
        return __truediv__(*this, other);
    }
    
    value operator %(value other) const {
        return __mod__(*this, other);
    }
    
    value operator &(value other) const {
        return __and__(*this, other);
    }
    
    value operator |(value other) const {
        return __or__(*this, other);
    }
    
    value operator ^(value other) const {
        return __xor__(*this, other);
    }
    
    value operator ~() const {
        return __invert__(*this);
    }
    
    value operator <<(value other) const {
        return __lshift__(*this, other);
    }

    value operator >>(value other) const {
        return __rshift__(*this, other);
    }
        
    operator bool() const {
        return __bool__(*this).boolval;
    }
};

namespace std {
    template<>
    struct hash<value> {
        size_t operator ()(const value& v) const {
            if (v.hash) {
                return v.hash;
            }
            printf("do calc\n");
            switch (v.type) {
            case value::NONE:
                return v.hash = -9223372036577629359;
            case value::BOOL:
                return v.hash = std::hash<bool>()(v.boolval);
            case value::INT:
                return v.hash = std::hash<long>()(v.intval);
            case value::FLOAT:
                if (v.floatval == (long)v.floatval)
                    return v.hash = std::hash<long>()((long)v.floatval);
                return v.hash = std::hash<double>()(v.floatval);
            case value::STR:
                printf("%s\n", v.strval->c_str());
                return v.hash = std::hash<str_t>()(*v.strval);
            default:
                throw std::runtime_error("unhashable type");
            }
        }
    };
}

struct set_iterator_t { set_t::const_iterator cur, end; };
struct dict_iterator_t { dict_t::const_iterator cur, end; };
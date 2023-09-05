#pragma once

template<typename T, typename K>
inline bool instanceof(const K* ptr) {
    return dynamic_cast<const T*>(ptr) != nullptr;
}

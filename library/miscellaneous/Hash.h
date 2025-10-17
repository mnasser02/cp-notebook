template <>
struct std::hash<Key> {
    std::size_t operator()(const Key& k) const {
        using std::hash;
        return ((hash<string>()(k.first) ^ (hash<string>()(k.second) << 1)) >> 1) ^ (hash<int>()(k.third) << 1);
    }
};

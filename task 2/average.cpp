namespace orig {
    template <typename Result, typename First, typename Second>
    Result average(const First& a, const Second& b) {
        return static_cast<Result>((a + b) / 2.0);
    }
}

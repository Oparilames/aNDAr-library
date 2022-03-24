namespace aNDAr {
// from https://mmore500.com/2019/07/07/cpp-compile-loop.html
template <size_t N>
struct ForEach {

  template <size_t I>
  static void item() {

    // do whatever
    /*
    emp::BitString<N> bs; // templated class
    bs.template ROTR_SELF<I>(); // spicy syntax for
                                // templated class' templated function
    */
    // recurse upwards
    if constexpr (I+1 < N) ForEach<N>::item<I+1>();

  }

};

// the argument for the lambda need to satisfy the order: int or int& i, return
// type for std::get()
template <typename TUPLE, size_t startIndex = 0,
          size_t inclusiveEndElementIndex = std::tuple_size_v<TUPLE>>
struct tupleForLoop
{
private:
  template <size_t I>
  static auto access(TUPLE theTuple, auto&& lambda)
  {

    if
      constexpr(I + 1 < inclusiveEndElementIndex)
        tupleForLoop<TUPLE, startIndex,
                        inclusiveEndElementIndex>::access<I + 1>(theTuple,
                                                                 lambda);

    return lambda(I, std::get<I>(theTuple));
  }

public:
  template <typename L = void>
  static auto call(TUPLE theTuple, L lambda)
  {
    return access<startIndex>(theTuple, lambda);
  }
};
} // aNDAr

class Foo
{
public:
  Foo(std::size_t s) : _impl{std::in_place, s} {}

  bool operator==(Foo const& other) const = default;
  auto operator<=>(Foo const& other) const = default;

  bool empty() const {
    return _impl->size() != 0;
  }

  void resize(std::size_t s) {
    _impl.modify([&](auto& impl) { impl.resize(s); });
  }

  void push_front(int val) {
    _impl.modify(
      [&](std::vector<int>& impl) {
        impl.push_front(val);
      }
    );
  }

private:
  std::copy_on_write<std::vector<int>> _impl;
};

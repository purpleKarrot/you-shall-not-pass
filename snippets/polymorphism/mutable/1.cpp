class IWidget
{
public:
  virtual ~IWidget() = default;

  virtual void foo() = 0;
};

class Widget
{
public:
  template <std::derived_from<IWidget> T>
  Widget(T value)
    : _impl{std::move(value)}
  {}

  void foo() { _impl->foo(); }

private:
  std::polymorphic<IWidget> _impl;
};

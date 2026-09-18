class IWidget
{
protected:
  ~IWidget() = default;

public:
  IWidget(IWidget const&) = delete;
  IWidget& operator=(IWidget const&) = delete;

  virtual void foo() const = 0;
};

class Widget
{
public:
  template <std::derived_from<IWidget> T>
  Widget(T value)
    : _impl{std::make_shared<T>(std::move(value))}
  {}

  void foo() const { _impl->foo(); }

private:
  std::shared_ptr<IWidget const> _impl;
};

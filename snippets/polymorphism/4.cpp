class IWidget
{
public:
  virtual ~IWidget() = default;

  IWidget(IWidget const&) = delete;
  IWidget& operator=(IWidget const&) = delete;

  void foo() {
    this->xfoo();
  }

private:
  virtual void xfoo() = 0;
};

#ifndef NOT_COPYABLE_HPP
#define NOT_COPYABLE_HPP

class NotCopyable {
  private:
    NotCopyable(const NotCopyable& ) = delete; // non construction-copyable
    NotCopyable& operator=( const NotCopyable& ) = delete; // non copyable
public:
    NotCopyable() = default;
    ~NotCopyable() = default;
};

#endif // NOT_COPYABLE_HPP

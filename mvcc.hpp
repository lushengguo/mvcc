#pragma once
#include <atomic>
#include <tuple>
#include <vector>

namespace mvcc
{

enum class isolation_level
{
    ReadUncommitted,
    ReadCommitted,
    RepeatableRead,
    Serializable
};

template <typename... Args>
class line
{
  public:
    typedef std::size_t         modify_tid;
    typedef std::size_t         delete_tid;
    typedef std::tuple<Args...> value_type;
    typedef const value_type   &const_value_reference;

  public:
    bool modify(const value_type &value) {}
    bool modify(const value_type &&value) {}

    const_value_reference get() { return static_cast<value_type>(data_); }

  private:
    std::tuple<modify_tid, delete_tid, Args...> data_;
};

template <typename... Args>
class mvcc
{
  public:
    typedef line<Args...> line;
    typedef line         &line_reference;
    typedef const line   &const_line_reference;

  public:
    template <>
    line_reference select();

  private:
    std::vector<line>  data_;
    std::atomic_size_t tid_;
};

} // namespace mvcc
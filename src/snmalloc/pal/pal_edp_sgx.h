#pragma once

#include "../aal/aal.h"
#include "../aal/aal_x86_sgx.h"

extern "C" void* get_tcs_addr();

namespace snmalloc
{
  class PALEdpSgx
  {
  public:
  using ThreadIdentity = size_t;
  static constexpr uint64_t pal_features = NoAllocation;
  static constexpr size_t address_bits = Aal::address_bits;
  static constexpr size_t page_size = Aal::smallest_page_size;

  [[noreturn]] static void error(const char* const str) noexcept
  {
      UNUSED(str);
      abort();
  }

  static void notify_not_using(void* p, size_t size) noexcept
  {
  UNUSED(p);
  UNUSED(size);
  }

  template<ZeroMem zero_mem>
  static void notify_using(void* p, size_t size) noexcept
  {
  UNUSED(p);
  UNUSED(size);
  }

  static void notify_using_readonly(void* p, size_t size) noexcept
  {
    UNUSED(p);
    UNUSED(size);
  }

  static void* reserve(size_t size) noexcept
  {
    UNUSED(size);
    return NULL;
  }

  static void message(char* str) noexcept
  {
  UNUSED(str);
  }

  template<bool page_aligned = false>
  static void zero(void* p, size_t size) noexcept
    {
    UNUSED(p);
    UNUSED(size);
    }

  template<typename T, SNMALLOC_CONCEPT(capptr::IsBound) B>
  static SNMALLOC_FAST_PATH CapPtr<T, capptr::user_address_control_type<B>>
  capptr_to_user_address_control(CapPtr<T, B> p)
    {
    UNUSED(p);
    }

  static inline uint64_t get_entropy64()
  {
      long long unsigned int result = 0;
      AAL_x86_sgx::entropy(&result);
      return result;
  }

  static inline ThreadIdentity get_tid() noexcept
  {
      return (size_t) get_tcs_addr();
  }

  };
}

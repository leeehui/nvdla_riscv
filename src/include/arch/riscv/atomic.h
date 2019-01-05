// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "debug.h"
#include "trap.h"

// Currently, interrupts are always disabled in M-mode.
#define disable_irqsave() (0)
#define enable_irqrestore(flags) ((void) (flags))

typedef struct { int lock; } spinlock_t;
#define SPINLOCK_INIT {0}

#define mb() asm volatile ("fence" ::: "memory")
#define atomic_set(ptr, val) (*(volatile typeof(*(ptr)) *)(ptr) = val)
#define atomic_read(ptr) (*(volatile typeof(*(ptr)) *)(ptr))

#ifdef __riscv_atomic
# define atomic_add(ptr, inc) __sync_fetch_and_add(ptr, inc)
# define atomic_or(ptr, inc) __sync_fetch_and_or(ptr, inc)
# define atomic_swap(ptr, swp) __sync_lock_test_and_set(ptr, swp)
# define atomic_cas(ptr, cmp, swp) __sync_val_compare_and_swap(ptr, cmp, swp)
#else
# define atomic_binop(ptr, inc, op) ({ \
  long flags = disable_irqsave(); \
  typeof(*(ptr)) res = atomic_read(ptr); \
  atomic_set(ptr, op); \
  enable_irqrestore(flags); \
  res; })
# define atomic_add(ptr, inc) atomic_binop(ptr, inc, res + (inc))
# define atomic_or(ptr, inc) atomic_binop(ptr, inc, res | (inc))
# define atomic_swap(ptr, inc) atomic_binop(ptr, inc, (inc))
# define atomic_cas(ptr, cmp, swp) ({ \
  long flags = disable_irqsave(); \
  typeof(*(ptr)) res = *(volatile typeof(*(ptr)) *)(ptr); \
  if (res == (cmp)) *(volatile typeof(ptr))(ptr) = (swp); \
  enable_irqrestore(flags); \
  res; })
#endif

static inline int spinlock_trylock(spinlock_t* lock)
{
  int res = atomic_swap(&lock->lock, -1);
  mb();
  return res;
}

static inline void spinlock_lock(spinlock_t* lock)
{
  do
  {
    while (atomic_read(&lock->lock))
      ;
  } while (spinlock_trylock(lock));
}

static inline void spinlock_unlock(spinlock_t* lock)
{
  mb();
  atomic_set(&lock->lock,0);
}

static inline long spinlock_lock_irqsave(spinlock_t* lock)
{
  long flags = disable_irqsave();
  spinlock_lock(lock);
  return flags;
}

#define mb_always_required() asm volatile ("fence" ::: "memory")
static inline void __raw_writel(uint32_t val, volatile void *addr)
{
    asm volatile("sw %0, 0(%1)" :: "r"(val), "r"(addr));
}

static inline uint32_t __raw_readl(const volatile void *addr)
{
    uint32_t val;
    asm volatile("lw %0, 0(%1)" : "=r" (val) : "r" (addr));
    return val;
}

#define __io_br() do {} while (0)
#define __io_ar() __asm__ __volatile__ ("fence i,r" :::"memory");
#define __io_bw() __asm__ __volatile__ ("fence w,o" :::"memory");
#define __io_aw() do {} while (0)

#define readl(c)        ({ uint32_t __v; __io_br(); __v = __raw_readl(c); __io_ar(); __v;})
#define writel(v, c)    ({ __io_bw(); __raw_writel((v),(c)); __io_aw(); })

#define __io_rbr() do {} while (0)
#define __io_rar() do {} while (0)
#define __io_rbw() do {} while (0)
#define __io_raw() do {} while (0)

#define readl_relaxed(c)        ({ uint32_t __v; __io_rbr(); __v = __raw_readl(c); __io_rar(); __v;})
#define writel_relaxed(v, c)    ({ __io_rbw(); __raw_writel((v),(c)); __io_raw(); })

static inline void spinlock_unlock_irqrestore(spinlock_t* lock, long flags)
{
  spinlock_unlock(lock);
  enable_irqrestore(flags);
}

static inline void wait_for_dla_irq(uint32_t *notifier)
{
    while (!atomic_read(notifier));
    atomic_set(notifier, (*notifier) - 1);
}

static inline void notify_dla_irq(uint32_t *notifier)
{
    atomic_set(notifier, (*notifier) + 1);
}

static inline void wait_for_dla_flag(uint32_t *notifier, uint32_t *saved_irq_ptr,  uint32_t check_irq)
{
    while( atomic_read(saved_irq_ptr) != check_irq )
    {
        wait_for_dla_irq(notifier);
    }
}

#ifdef __cplusplus
}
#endif


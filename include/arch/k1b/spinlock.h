/*
 * MIT License
 *
 * Copyright(c) 2018 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef ARCH_K1B_SPINLOCK_H_
#define ARCH_K1B_SPINLOCK_H_

/**
 * @addtogroup k1b-spinlock Spinlocks
 * @ingroup k1b
 *
 * @brief k1b Spinlocks
 */
/**@{*/

	/* External dependencies. */
	#include <HAL/hal/hal_ext.h>
	#include <nanvix/const.h>
	#include <stdint.h>

/*============================================================================*
 *                             Spinlocks Interface                            *
 *============================================================================*/

	/**
	 * @name Spinlock State
	 */
	/**@{*/
	#define K1B_SPINLOCK_UNLOCKED 0 /**< Unlocked */
	#define K1B_SPINLOCK_LOCKED   1 /**< Locked   */
	/**@}*/

	/**
	 * @brief Spinlock.
	 */
	typedef uint64_t spinlock_t;

	/**
	 * @brief Initializes a spinlock.
	 *
	 * @param lock Target spinlock.
	 */
	static inline void k1b_spinlock_init(spinlock_t *lock)
	{
		__builtin_k1_sdu(lock,  K1B_SPINLOCK_UNLOCKED);
	}

	/**
	 * @brief Attempts to lock a spinlock.
	 *
	 * @param lock Target spinlock.
	 *
	 * @returns Upon successful completion, the spinlock pointed to by
	 * @p lock is locked and zero is returned. Upon failure, non-zero
	 * is returned instead, and the lock is not acquired by the
	 * caller.
	 */
	static inline int k1b_spinlock_trylock(spinlock_t *lock)
	{
		return (__builtin_k1_ldc(lock) == K1B_SPINLOCK_UNLOCKED);
	}

	/**
	 * @brief Locks a spinlock.
	 *
	 * @param lock Target spinlock.
	 */
	static inline void k1b_spinlock_lock(spinlock_t *lock)
	{
		while (!k1b_spinlock_trylock(lock))
			/* noop */;
	}

	/**
	 * @brief Unlocks a spinlock.
	 *
	 * @param lock Target spinlock.
	 */
	static inline void k1b_spinlock_unlock(spinlock_t *lock)
	{
		__builtin_k1_sdu(lock, K1B_SPINLOCK_UNLOCKED);
	}

/*============================================================================*
 *                              Exported Interface                            *
 *============================================================================*/

	/**
	 * @name Provided Interface
	 *
	 * @cond k1b
	 */
	/**@{*/
	#define __spinlock_t          /**< @p spinlock_t      */
	#define __spinlock_init_fn    /**< spinlock_init()    */
	#define __spinlock_lock_fn    /**< spinlock_lock()    */
	#define __spinlock_trylock_fn /**< spinlock_trylock() */
	#define __spinlock_unlock_fn  /**< spinlock_unlock()  */
	/**@}*/
	/**@endcond*/

	/**
	 * @see K1B_SPINLOCK_UNLOCKED
	 *
	 * @cond k1b
	 */
	#define SPINLOCK_UNLOCKED K1B_SPINLOCK_UNLOCKED
	/**@endcond*/

	/**
	 * @see K1B_SPINLOCK_LOCKED
	 *
	 * @cond k1b
	 */
	#define SPINLOCK_LOCKED K1B_SPINLOCK_LOCKED
	/**@endcond*/

	/**
	 * @see k1b_spinlock_init()
	 *
	 * @cond k1b
	 */
	static inline void spinlock_init(spinlock_t *lock)
	{
		k1b_spinlock_init(lock);
	}
	/**@endcond*/

	/**
	 * @see k1b_spinlock_trylock()
	 *
	 * @cond k1b
	 */
	static inline int spinlock_trylock(spinlock_t *lock)
	{
		return (k1b_spinlock_trylock(lock));
	}
	/**@endcond*/

	/**
	 * @see k1b_spinlock_lock()
	 *
	 * @cond k1b
	 */
	static inline void spinlock_lock(spinlock_t *lock)
	{
		k1b_spinlock_lock(lock);
	}
	/**@endcond*/

	/**
	 * @see k1b_spinlock_unlock()
	 *
	 * @cond k1b
	 */
	static inline void spinlock_unlock(spinlock_t *lock)
	{
		k1b_spinlock_unlock(lock);
	}
	/**@endcond*/

/**@}*/

#endif /* ARCH_K1B_SPINLOCK_H_ */


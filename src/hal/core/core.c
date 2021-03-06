/*
 * MIT License
 *
 * Copyright(c) 2011-2019 The Maintainers of Nanvix
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

#define __NEED_HAL_CLUSTER
#include <nanvix/hal/cluster.h>
#include <nanvix/const.h>
#include <nanvix/klib.h>

/*============================================================================*
 * core_idle()                                                                *
 *============================================================================*/

/**
 * The core_idle() function suspends instruction execution in the
 * underlying core until a start signal is received. While is
 * suspended mode, the underlying core is placed in a low-power state
 * to save energy.
 *
 * @see core_start(), core_run().
 *
 * @author Pedro Henrique Penna and Davidson Francis
 */
PUBLIC void core_idle(void)
{
		int coreid = core_get_id();

		cores[coreid].state = CORE_IDLE;

		/*
		 * The lock of this core was
		 * acquired when resetting, in
		 * core_reset().
		 */

	dcache_invalidate();
	spinlock_unlock(&cores[coreid].lock);

	while (TRUE)
	{
		spinlock_lock(&cores[coreid].lock);
		dcache_invalidate();

			/* Awaken. */
			if (cores[coreid].state != CORE_IDLE)
			{
				spinlock_unlock(&cores[coreid].lock);
				break;
			}

			core_clear();

		dcache_invalidate();
		spinlock_unlock(&cores[coreid].lock);

		core_waitclear();
	}
}

/*============================================================================*
 * core_sleep()                                                               *
 *============================================================================*/

/**
 * The core_sleep() function suspends instruction execution in the
 * underlying core until a wakeup signal is received. While is
 * suspended mode, the underlying core is placed in a low-power state
 * to save energy.
 *
 * @see core_wakeup().
 *
 * @author Pedro Henrique Penna and Davidson Francis
 */
PUBLIC void core_sleep(void)
{
	int coreid = core_get_id();

	while (TRUE)
	{
		spinlock_lock(&cores[coreid].lock);
		dcache_invalidate();

			/* Awaken. */
			if (cores[coreid].wakeups > 0)
			{
				cores[coreid].wakeups--;
				cores[coreid].state = CORE_RUNNING;

				dcache_invalidate();
				spinlock_unlock(&cores[coreid].lock);

				break;
			}

			cores[coreid].state = CORE_SLEEPING;
			core_clear();

		dcache_invalidate();
		spinlock_unlock(&cores[coreid].lock);

		core_waitclear();
	}
}

/*============================================================================*
 * core_wakeup()                                                              *
 *============================================================================*/

/**
 * The core_wakeup() function sends a wakeup signal to the
 * sleeping core whose ID equals to @p coreid.
 *
 * @see core_sleep().
 *
 * @todo Check if the calling core is not the target core.
 *
 * @author Pedro Henrique Penna and Davidson Francis
 */
PUBLIC void core_wakeup(int coreid)
{
	spinlock_lock(&cores[coreid].lock);
	dcache_invalidate();

		/* Wakeup target core. */
		cores[coreid].wakeups++;
		core_notify(coreid);

	dcache_invalidate();
	spinlock_unlock(&cores[coreid].lock);
}

/*============================================================================*
 * core_start()                                                               *
 *============================================================================*/

/**
 * The core_start() function sets the starting routine of the
 * sleeping core whose ID equals to @p coreid to @p start and sends a
 * wakeup signal to this core.
 *
 * @see core_idle(), core_run().
 *
 * @todo Check if the calling core is not the target core.
 *
 * @author Pedro Henrique Penna and Davidson Francis
 */
PUBLIC void core_start(int coreid, void (*start)(void))
{
again:

	spinlock_lock(&cores[coreid].lock);
	dcache_invalidate();

	/* Wait for reset. */
	if (cores[coreid].state == CORE_RESETTING)
	{
		spinlock_unlock(&cores[coreid].lock);
		goto again;
	}

	/* Wakeup target core. */
	if (cores[coreid].state == CORE_IDLE)
	{
		cores[coreid].state = CORE_RUNNING;
		cores[coreid].start = start;
		cores[coreid].wakeups = 0;
		dcache_invalidate();

		core_notify(coreid);
	}

	spinlock_unlock(&cores[coreid].lock);
}

/*============================================================================*
 * core_run()                                                                 *
 *============================================================================*/

/**
 * The core_run() function resumes instruction execution in the
 * underlying core, by calling the starting routine which was
 * previously registered with core_wakeup(). Furthermore, in the
 * first call ever made to core_run(), architectural structures of
 * the underlying core are initialized.
 *
 * @see core_idle(), core_start().
 *
 * @author Pedro Henrique Penna and Davidson Francis
 */
PUBLIC void core_run(void)
{
	int coreid = core_get_id();

	spinlock_lock(&cores[coreid].lock);
	dcache_invalidate();

		/* Initialize core. */
		if (!cores[coreid].initialized)
		{
			core_setup();
			cores[coreid].initialized = TRUE;
			dcache_invalidate();
		}

	spinlock_unlock(&cores[coreid].lock);

	cores[coreid].start();
}

/*============================================================================*
 * core_reset()                                                               *
 *============================================================================*/

/**
 * The core_reset() function resets execution instruction in
 * the underlying core by reseting the kernel stack to its initial
 * location and relaunching the slave_setup() function.
 *
 * @note This function does not return.
 *
 * @see slave_setup()
 *
 * @author Pedro Henrique Penna and Davidson Francis
 */
PUBLIC void core_reset(void)
{
	int coreid = core_get_id();

	spinlock_lock(&cores[coreid].lock);
	dcache_invalidate();

		cores[coreid].state = CORE_RESETTING;

		dcache_invalidate();

		_core_reset();

		/*
		 * The lock of this core will
		 * be released when resetting
		 * is completed, in core_idle().
		 */
}

/*============================================================================*
 * core_shutdown()                                                            *
 *============================================================================*/

/**
 * The core_shutdown() function powers off the underlying core.
 * Afeter powering off a core, instruction execution cannot be
 * resumed. The status code @p status is handled to the remote spawner
 * device.
 *
 * @author Pedro Henrique Penna and Davidson Francis
 */
PUBLIC void core_shutdown(int status)
{
	int coreid = core_get_id();

	UNUSED(status);

	spinlock_lock(&cores[coreid].lock);

		cores[coreid].state = CORE_OFFLINE;

	dcache_invalidate();
	spinlock_unlock(&cores[coreid].lock);

	core_poweroff();
}

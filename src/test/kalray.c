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

#include <nanvix/hal/hal.h>
#include <nanvix/const.h>
#include <errno.h>

#include "test.h"

/**
 * @name Involved nodes.
 */
#define MASTER_ID 128
#define SLAVE_ID 0

#define BARRIER_MODE 1

static spinlock_t mutex = SPINLOCK_UNLOCKED;

/**
 * @brief Handles a C-NoC interrupt.
 *
 * @param num Number of interrupt.
 */
PRIVATE void do_cnoc_handler(int num)
{
	UNUSED(num);

	kprintf("*HANDLER* Unlock mutex!");
	spinlock_unlock(&mutex);
}

/**
 * @brief Kalray Test: Synchronization Point with events
 */
PRIVATE void kalray_test_sync_with_nanvix_interrupts(void)
{
	int nodeid;
	int interface;
	int rx_tag, tx_tag;
	uint64_t mask;

	nodeid = __k1_get_cluster_id();
	interface = 0;
	rx_tag = 0;
	tx_tag = 0;
	mask = 1;

	spinlock_lock(&mutex);

	/* Nanvix prologue */
	interrupt_register(HAL_INT_CNOC, do_cnoc_handler);
	interrupts_enable();
	interrupt_unmask(HAL_INT_CNOC);

	if (nodeid == MASTER_ID)
	{
		kprintf("  IO: Alloc Rx and TX.");

		bostan_cnoc_rx_alloc(interface, rx_tag);
		bostan_cnoc_rx_config(interface, rx_tag, BARRIER_MODE, ~mask);
		bostan_cnoc_tx_alloc(interface, tx_tag);

		kprintf("  IO: Wait signal_1.");

		spinlock_lock(&mutex);
		bostan_cnoc_rx_clear(interface, rx_tag);
		bostan_cnoc_rx_config(interface, rx_tag, BARRIER_MODE, ~mask);

		kprintf("  IO: Receive signal_1 and Send response_1.");

		bostan_cnoc_tx_config(interface, MASTER_ID, tx_tag, SLAVE_ID, rx_tag);
		bostan_cnoc_tx_write(interface, tx_tag, mask);

		kprintf("  IO: Wait signal_2.");

		spinlock_lock(&mutex);
		bostan_cnoc_rx_clear(interface, rx_tag);

		kprintf("  IO: Receive signal_2 and Send response_2.");

		bostan_cnoc_tx_config(interface, MASTER_ID, tx_tag, SLAVE_ID, rx_tag);
		bostan_cnoc_tx_write(interface, tx_tag, mask);

		kprintf("  IO: Release RX and TX.");

		bostan_cnoc_tx_free(interface, tx_tag);
		bostan_cnoc_rx_free(interface, rx_tag);
	}
	else
	{
		kprintf("CC: Alloc Rx and TX.");

		bostan_cnoc_rx_alloc(interface, rx_tag);
		bostan_cnoc_rx_config(interface, rx_tag, BARRIER_MODE, ~mask);
		bostan_cnoc_tx_alloc(interface, tx_tag);

		kprintf("CC: Send signal_1.");

		bostan_cnoc_tx_config(interface, SLAVE_ID, tx_tag, MASTER_ID, rx_tag);
		bostan_cnoc_tx_write(interface, tx_tag, mask);

		kprintf("CC: Wait response_1.");

		spinlock_lock(&mutex);
		bostan_cnoc_rx_clear(interface, rx_tag);
		bostan_cnoc_rx_config(interface, rx_tag, BARRIER_MODE, ~mask);

		kprintf("CC: Receive response_1 and Send signal_2.");

		bostan_cnoc_tx_config(interface, SLAVE_ID, tx_tag, MASTER_ID, rx_tag);
		bostan_cnoc_tx_write(interface, tx_tag, mask);

		kprintf("CC: Wait response_2.");

		spinlock_lock(&mutex);
		bostan_cnoc_rx_clear(interface, rx_tag);

		kprintf("CC: Receive response_2.");
		kprintf("CC: Release RX and TX.");

		bostan_cnoc_tx_free(interface, tx_tag);
		bostan_cnoc_rx_free(interface, rx_tag);
	}

	/* Nanvix epilogue */
	interrupt_mask(HAL_INT_CNOC);
	interrupts_disable();
}

/*============================================================================*/

/**
 * @brief Unit tests.
 */
PUBLIC struct test kalray_sync_tests[] = {
	{kalray_test_sync_with_nanvix_interrupts, "Sync with interrupts"},
	{NULL, NULL},
};

/*============================================================================*
 * Test Driver                                                                *
 *============================================================================*/

/**
 * The test_sync() function launches testing units on the sync
 * interface of the HAL.
 *
 * @author Pedro Henrique Penna
 */
PUBLIC void kalray_sync(void)
{
	/* API Tests */
	for (int i = 0; kalray_sync_tests[i].test_fn != NULL; i++)
	{
		kalray_sync_tests[i].test_fn();
		kprintf("[kalray] %s [passed]", kalray_sync_tests[i].name);
	}
}

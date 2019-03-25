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

#ifndef TARGET_KALRAY_MPPA256_MAILBOX_H_
#define TARGET_KALRAY_MPPA256_MAILBOX_H_

/*============================================================================*
 *                             Mailbox Interface                              *
 *============================================================================*/

/* Processor API. */
#include <arch/target/kalray/mppa256/_mppa256.h>

	#include <nanvix/const.h>

	/**
	 * @brief Mailbox types
	 */
	/**@{*/
	#define MPPA256_MAILBOX_RX BOSTAN_NOC_RX_TYPE /**< Reciever type. */
	#define MPPA256_MAILBOX_TX BOSTAN_NOC_TX_TYPE /**< Sender type.   */
	/**@}*/

	/**
	 * @name Maximum number of mailboxes points.
	 */
	/**@{*/
	#define MPPA256_MAILBOX_CREATE_MAX (BOSTAN_MAILBOX_CREATE_PER_DMA * BOSTAN_NR_INTERFACES) /**< Maximum amount of create mailboxes. */
	#define MPPA256_MAILBOX_OPEN_MAX   (BOSTAN_MAILBOX_OPEN_PER_DMA * BOSTAN_NR_INTERFACES)   /**< Maximum amount of open mailboxes.   */
	/**@}*/

	/**
	 * @name Sizes (in bytes) of a mailbox message.
	 */
	/**@{*/
	#define MPPA256_MAILBOX_MSG_SIZE      120 /**< Data size.     */
	#define MPPA256_MAILBOX_METADATA_SIZE   2 /**< Metadata size. */
	/**@}*/

	/**
	 * @brief Underliyng size (in bytes) of a mailbox message.
	 */
	#define MPPA256_MAILBOX_MSG_SIZE_MAX (MPPA256_MAILBOX_METADATA_SIZE + MPPA256_MAILBOX_MSG_SIZE)

	/**
	 * @brief Creates a mailbox.
	 *
	 * @param nodenum Logic ID of the underlying NoC node.
	 *
	 * @returns Upon successful completion, the ID of the newly created
	 * mailbox is returned. Upon failure, a negative error code is
	 * returned instead.
	 */
	EXTERN int mppa256_mailbox_create(int nodenum);

	/**
	 * @brief Opens a mailbox.
	 *
	 * @param nodeid Logic ID of the target NoC node.
	 *
	 * @returns Upon successful completion, the ID of the target mailbox
	 * is returned. Upon failure, a negative error code is returned
	 * instead.
	 */
	EXTERN int mppa256_mailbox_open(int nodenum);

	/**
	 * @brief Destroys a mailbox.
	 *
	 * @param mbxid ID of the target mailbox.
	 *
	 * @returns Upon successful completion, zero is returned. Upon failure,
	 * a negative error code is returned instead.
	 */
	EXTERN int mppa256_mailbox_unlink(int mbxid);

	/**
	 * @brief Closes a mailbox.
	 *
	 * @param mbxid ID of the target mailbox.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
	EXTERN int mppa256_mailbox_close(int mbxid);

	/**
	 * @brief Writes data to a mailbox.
	 *
	 * @param mbxid  ID of the target mailbox.
	 * @param buffer Buffer where the data should be read from.
	 * @param size   Number of bytes to write.
	 *
	 * @returns Upon successful completion, the number of bytes
	 * successfully written is returned. Upon failure, a negative error
	 * code is returned instead.
	 */
	EXTERN ssize_t mppa256_mailbox_write(int mbxid, const void * buffer, size_t size);

	/**
	 * @brief Reads data from a mailbox.
	 *
	 * @param mbxid  ID of the target mailbox.
	 * @param buffer Buffer where the data should be written to.
	 * @param size   Number of bytes to read.
	 *
	 * @returns Upon successful completion, the number of bytes
	 * successfully read is returned. Upon failure, a negative error code
	 * is returned instead.
	 */
	EXTERN ssize_t mppa256_mailbox_read(int mbxid, void * buffer, size_t size);

/*============================================================================*
 *                              Exported Interface                            *
 *============================================================================*/

	/**
	 * @name Provided Interface
	 */
	/**@{*/
	#define __hal_mailbox_create_fn /**< hal_mailbox_create() */
	#define __hal_mailbox_open_fn   /**< hal_mailbox_open()   */
	#define __hal_mailbox_unlink_fn /**< hal_mailbox_unlink() */
	#define __hal_mailbox_close_fn  /**< hal_mailbox_close()  */
	#define __hal_mailbox_write_fn  /**< hal_mailbox_write()  */
	#define __hal_mailbox_read_fn   /**< hal_mailbox_read()   */
	/**@}*/

	/**
	 * @see MPPA256_SYNC_ONE_TO_ALL
	 * @see MPPA256_SYNC_ALL_TO_ONE
	 */
	/**@{*/
	#define HAL_MAILBOX_CREATE_MAX MPPA256_MAILBOX_CREATE_MAX
	#define HAL_MAILBOX_OPEN_MAX MPPA256_MAILBOX_OPEN_MAX
	/**@}*/

	/**
	 * @see BOSTAN_SYNC_CREATE_MAX
	 * @see BOSTAN_SYNC_OPEN_MAX
	 */
	/**@{*/
	#define HAL_MAILBOX_MSG_SIZE MPPA256_MAILBOX_MSG_SIZE
	/**@}*/

	/**
	 * @see mppa256_sync_create()
	 */
	EXTERN int hal_mailbox_create(int nodenum)
	{
		return mppa256_mailbox_create(nodenum);
	}

	/**
	 * @see mppa256_mailbox_open()
	 */
	static inline int hal_mailbox_open(int nodenum)
	{
		return mppa256_mailbox_close(nodenum);
	}

	/**
	 * @see mppa256_mailbox_unlink()
	 */
	static inline int hal_mailbox_unlink(int mbxid)
	{
		return mppa256_mailbox_unlink(mbxid);
	}

	/**
	 * @see mppa256_mailbox_close()
	 */
	static inline int hal_mailbox_close(int mbxid)
	{
		return mppa256_mailbox_close(mbxid);
	}

	/**
	 * @see mppa256_mailbox_write()
	 */
	static inline ssize_t hal_mailbox_write(int mbxid, const void * buffer, size_t size)
	{
		return mppa256_mailbox_write(mbxid, buffer, size);
	}

	/**
	 * @see mppa256_mailbox_read()
	 */
	static inline ssize_t hal_mailbox_read(int mbxid, void * buffer, size_t size)
	{
		return mppa256_mailbox_read(mbxid, buffer, size);
	}

#endif /* TARGET_KALRAY_MPPA256_MAILBOX_H_ */

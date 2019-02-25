#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#define RING_BUFFER_INVALID_ARGUMENT  -1
#define RING_BUFFER_OUT_OF_MEMORY    -2
#define RING_BUFFER_READ_ERROR    -3
#define RING_BUFFER_WRITE_DATA_NULL    -4
#define RING_BUFFER_WRITE_CAPACITY_FULL  -5
#define RING_BUFFER_SUCCESS	           0

/**
 * @addtogroup CircularBufferModule CircularBuffer API functions
 * Generic Circular Buffer implementation.
 *
 * @{
 */

/**
 * A circular buffer.
 *
 * @see list of functions used to operate on @ref CircularBufferModule "CircularBuffer" objects
 */
typedef struct CircularBuffer_t
{
  /**
   * Total buffer capacity.
   */
  int capacity;
  
  /**
   * Amount of data in buffer.
   */
  int size;
  
  /**
   * Write index.
   */
  int writeIdx;
  
  /**
   * Read index.
   */
  int readIdx;
  
}
CircularBuffer;

/**
 * Creates a circular buffer of the specified capacity.
 *
 * @param capacity the capacity in number of bytes of the data buffer.
 * @param mtag MALLOC allocation tag
 * @param buffer The circular buffer to initialize.
 */
int CircularBufferCreate(int capacity, CircularBuffer** buffer);

/**
 * Returns the capacity of the buffer.
 */
#define CircularBufferGetCapacity(buffer) ((buffer)->capacity + 0)

/**
 * Returns the current size (number of bytes) in the buffer.
 */
#define CircularBufferGetSize(buffer) ((buffer)->size + 0)

/**
 * Returns whether buffer is empty or not.
 */
#define CircularBufferIsEmpty(buffer) ((buffer)->size == 0)

/**
 * Returns whether buffer is full or not.
 **/
#define CircularBufferIsFull(buffer) ((buffer)->size == (buffer)->capacity)

/**
 * Resets the buffer to the empty state.
 */
#define CircularBufferReset(buffer) ((buffer)->size = \
                                     (buffer)->readIdx = \
                                                         (buffer)->writeIdx = 0)

/**
 * Determines the residual capacity of the circular buffer.
 */
#define CircularBufferGetAvailable(buffer) ((buffer)->capacity - (buffer)->size)

/**
 * Reads requested number of bytes from the circular buffer.
 *
 * @param buffer The circular buffer to read from.
 * @param data  Pointer to where to store read bytes.
 * @param bufSize The number of bytes to read from the circular buffer.
 *
 * @return the number of bytes that were read.  A negative value indicates an
 * error, while a value less than bufSize indicates that end-of-buffer is
 * reached.
 */
 
 int CircularBufferRead(CircularBuffer* buffer, void* data, int bufSize);

/**
 * Skips requested number of bytes from the circular buffer.
 *
 * @param buffer The circular buffer to skip from.
 * @param bufSize The number of bytes to skip from the circular buffer.
 *
 * @return the number of bytes that were skipped.  A negative value indicates an
 * error, while a value less than bufSize indicates that end-of-buffer is
 * reached.
 **/
 int CircularBufferSkip(CircularBuffer* buffer, int bufSize);

/**
 * Writes requested number of bytes from the circular buffer.
 *
 * @param buffer The circular buffer to write to
 * @param data  Pointer to data to write.
 * @param bufSize The number of bytes to write into the circular buffer.
 *
 * @return the number of bytes that were written.  A negative value indicates
 * an error, while a value less than bufSize indicates that buffer capacity is
 * reached.
 */
int CircularBufferWrite(CircularBuffer* buffer, const void* data, int bufSize);

/**
 * Removes the requested number of bytes from the end of the circular buffer.
 *
 * @param buffer The circular buffer to write to
 * @param amoun tThe number of bytes to remove from end of circular buffer.
 *
 * @return the number of bytes that were unwritten. A negative value indicates
 *         an error.
 */
int CircularBufferUnwrite(CircularBuffer* buffer, int amount);

/**
 * @}
 */


#endif 
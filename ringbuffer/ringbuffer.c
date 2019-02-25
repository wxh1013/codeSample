#include "ringbuffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CircularBufferCreate(int capacity, CircularBuffer** buffer)
{
  CircularBuffer* Interface;
  if (buffer == NULL || capacity <= 0)
    return RING_BUFFER_INVALID_ARGUMENT;
    
  Interface = (CircularBuffer *) malloc(sizeof(CircularBuffer) + capacity);
  if (Interface == NULL)
    return RING_BUFFER_OUT_OF_MEMORY;
  Interface->capacity = capacity;
  CircularBufferReset(Interface);
  *buffer = Interface;
  return RING_BUFFER_SUCCESS;
}


int CircularBufferRead(CircularBuffer* buffer, void* data, int bufSize)
{
  int nbRead = 0;
  unsigned char *bufferData = NULL;
  
  if (buffer == NULL || (data == NULL && bufSize > 0))
    return RING_BUFFER_READ_ERROR;
    
  if (buffer->size < bufSize)
    bufSize = buffer->size;
    
  if (bufSize == 0)
    return 0;
    
  bufferData = ((unsigned char *) buffer) + sizeof(CircularBuffer);
  
  if (buffer->readIdx >= buffer->writeIdx)
  {
    nbRead = buffer->capacity - buffer->readIdx;
    if (nbRead > bufSize) nbRead = bufSize;
    
    memcpy(data, bufferData + buffer->readIdx, nbRead);
    buffer->size -= nbRead;
    buffer->readIdx += nbRead;
    if (buffer->readIdx == buffer->capacity)
      buffer->readIdx = 0;
  }
  
  if (nbRead < bufSize)
  {
    int toRead = bufSize - nbRead;
    memcpy(((unsigned char *) data) + nbRead, bufferData + buffer->readIdx, toRead);
    buffer->size -= toRead;
    buffer->readIdx += toRead;
  }
  
  return bufSize;
}

int CircularBufferSkip(CircularBuffer* buffer, int bufSize)
{
  if ( buffer == NULL )
    return -1;
    
  if (buffer->size < bufSize)
    bufSize = buffer->size;
    
  if (bufSize == 0)
    return 0;
    
  buffer->readIdx += bufSize;
  if (buffer->readIdx >= buffer->capacity)
    buffer->readIdx -= buffer->capacity;
    
  buffer->size -= bufSize;
  
  return bufSize;
}

int CircularBufferWrite(CircularBuffer* buffer, const void *data, int bufSize)
{
  int nbWritten = 0;
  unsigned char *bufferData;
  int available = buffer->capacity - buffer->size;
  
  if (data == NULL && bufSize > 0)
    return RING_BUFFER_WRITE_DATA_NULL;
    
  if (available < bufSize)	/* We need to force an error to be logged here */
    return RING_BUFFER_WRITE_CAPACITY_FULL;
/*    bufSize = available;	Throwing data on the floor with no notice is asking for trouble */
    
  if (bufSize == 0)
    return 0;
    
  bufferData = ((unsigned char*) buffer) + sizeof(CircularBuffer);
  
  if (buffer->writeIdx >= buffer->readIdx)
  {
    nbWritten = buffer->capacity - buffer->writeIdx;
    if (nbWritten > bufSize) nbWritten = bufSize;
    memcpy(bufferData + buffer->writeIdx, data, nbWritten);
    buffer->size += nbWritten;
    buffer->writeIdx += nbWritten;
    if (buffer->writeIdx == buffer->capacity)
      buffer->writeIdx = 0;
  }
  
  if (nbWritten < bufSize)
  {
    int toWrite = bufSize - nbWritten;
    memcpy(bufferData + buffer->writeIdx, ((unsigned char*) data) + nbWritten, toWrite);
    buffer->size += toWrite;
    buffer->writeIdx += toWrite;
  }
  printf("readIdx:");
  return bufSize;
}

int CircularBufferUnwrite(CircularBuffer* buffer, int amount)
{
  int available = buffer->capacity - buffer->size;
  
  if (available < amount)
    amount = available;
  buffer->size -= amount;
  return amount;
}
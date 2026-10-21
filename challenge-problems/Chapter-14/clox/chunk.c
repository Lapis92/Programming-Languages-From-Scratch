#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lineCount = 0;     // Challenge #1 add lineCount for array
  chunk->lineCapacity = 0;  // Challenge #1 add lineCapacity for array
  chunk->lines = NULL;
  initValueArray(&chunk->constants);
}
void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
  FREE_ARRAY(LineStart, chunk->lines, chunk->lineCapacity); //Challenge #1 free the array
}
void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code,
        oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;

  // Challenge #1: if there isn't a new line, then do nothing
  if (chunk->lineCount > 0 && chunk->lines[chunk->lineCount-1].line == line) {
    return;
  }

  // Challenge #1: if there IS a new line, add it to the array
  if (chunk->lineCapacity < chunk->lineCount+1) {
    // Grow the array if necessary
    int oldCapacity = chunk->lineCapacity;
    chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
    chunk->lines = GROW_ARRAY(LineStart, chunk->lines, oldCapacity, chunk->lineCapacity);
  }

  // Challenge #1: create the line
  LineStart* lineStart = &chunk->lines[chunk->lineCount++];
  lineStart->offset = chunk->count - 1;
  lineStart->line = line;
}
int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

void writeConstant(Chunk* chunk, Value value, int line) {
  int index = addConstant(chunk, value);
  if (index < 256) {
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, (uint8_t)index, line);
  } else {
    writeChunk(chunk, OP_CONSTANT_LONG, line);
    writeChunk(chunk, (uint8_t)(index & 0xff), line);
    writeChunk(chunk, (uint8_t)((index >> 8) & 0xff), line);
    writeChunk(chunk, (uint8_t)((index >> 16) & 0xff), line);
  }
}

int getLine(Chunk* chunk, int instruction) {
  int start = 0;
  int end = chunk->lineCount-1;

  for(;;) {
    // Get the middle of the line, and binary search for instructions
    int middle = (start+end)/2;
    LineStart* line = &chunk->lines[middle];
    if (instruction < line->offset) {
      end = middle-1;
    }
    else if (middle == chunk->lineCount-1 || instruction < chunk->lines[middle+1].offset) {
      return line->line;
    }
    else {
      start = middle+1;
    }
  }
}

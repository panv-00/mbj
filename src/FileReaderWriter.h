#ifndef FILEREADERWRITER_H
#define FILEREADERWRITER_H

#include <stdio.h>
#include <stdint.h>

class FileReaderWriter
{
public:
  FileReaderWriter()
  {

  };

  ~FileReaderWriter()
  {

  };

  bool open(const char *filename, const char *open_mode)
  {
    fp = fopen(filename, open_mode);
    if (fp == NULL) { return false; }
    
    return true;
  };

  void close() { fclose(fp); };
  int read_byte() { return getc(fp); };
  void write_byte(uint8_t data) { putc(data, fp); };

private:
  FILE *fp;
};

#endif

#include "Stk.h"
#ifdef __RAW_ARRAYS__
#ifndef MEMORYFS_H
#define MEMORYFS_H

#include "Stk.h"
//#include "Arduino.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//#include <stdint.h>
//#include <stdbool.h>
//#include <vector> 
#if defined(ESP32)
#include "esp_system.h"
#include "esp32-hal-log.h"
#include "pgmspace.h"
#elif defined(ESP8266)
#include "pgmspace.h"
#endif

#define VFS_INC_SIZE 10
#define MIN(a,b) ((a) < (b) ? (a) : (b))

namespace stk {

//! Simulated File Descriptor of registered virtual "Memory" files
struct VFS_FD {
  const char *name;
  const unsigned char *data;
  size_t size; // in bytes
  bool is_open;
};

/***************************************************/
/*! \class MemoryFS
    \brief STK in memory File
    An instance is representing an individual memory array which
    can be registered with a file name.

    This functionality is used by the MemoryLoop and MemoryWvIn
    as compatibility layer for the related file based operations.
    So that we can use the instruments which are based on recorded
    samples.

  Phil Schatzmann
*/
/***************************************************/
class MemoryFS {
    public:
        MemoryFS(const unsigned char *raw=NULL, unsigned int size=0, int bytesPerSample=2, bool swapBytes=true);
        MemoryFS (const char* fileName);

        //! makes the file available so that the open (by name) operation is working
        static VFS_FD * registerFile(const char* fileName, const unsigned char *raw, unsigned int size);
        //! opens the indicated file
        bool open(const char* fileName, int bytesPerSample=2);
        //! Returns a descriptor with additional information
        VFS_FD* getFD();
        //! Determines the size (in samples)
        size_t getSize(); 
        //! sets to open flag to false
        void close();
        //! checks if the file has been opened
        bool isOpen();
        //! Reads the data into the buffer at the indicated start frame
        bool fileRead( StkFrames& buffer, unsigned long startFrame, bool doNormalize) ;

        size_t current_pos_; // current read position in the memory in samples


    protected:
        static int findByName(const char * path);
        VFS_FD *fd;
        long  fileSize_;
        bool swapBytes;
};

}

#endif
#endif
#pragma once

#include <mutex>
#include <string>
#include <functional>

#include <Vane/Core/Defines.hpp>
#include <Vane/Core/Asserts.hpp>

#ifdef VPLATFORM_WINDOWS
#include <Windows.h>

#define IOCP_EOF 3
#define IOCP_WRITE 3
#define IOCP_CANCEL 3

#endif

namespace Vane {
/**
 * \brief [Singleton] Handles opening/closing, reading, and writing files.
 */
class Filesystem {
private:
    static Filesystem* s_Instance;
    static std::mutex s_Mutex;
    
public:
    Filesystem(Filesystem& other) = delete;
    void operator=(const Filesystem&) = delete;

    /**
     * \brief Singleton class instance 
     * \return FileSystem*
     */
    static Filesystem* GetInstance();

    /**
     * \brief Destroy the File System object, cancel all current processes,
     * close files, I/O completion port, and delete all buffers created
     */
    ~Filesystem();

#ifdef VPLATFORM_WINDOWS
    /**
     * \brief For ease of use with Microsoft API
     */
    using OverlapIOInfo = struct _OVERLAPIOINFO {
        /// Microsoft overlapped datastructure used by asynchronous file I/O
        OVERLAPPED overlapped;
        /// Handle of the file associate with the call
        HANDLE hFile;
        /// Buffer which is being read into
        char* buffer;
        /// Callback function for completion of asynchronous operation
        Action<const char*> callback;
    };
#endif

    /**
     * \brief Read the specified filename (with file path) synchronously 
     * \param filename 
     * \return char* the contents of the read file
     */
    char* Read(const char* filename);

    
    /**
     * \brief Read the specified filename (with file path) synchronously 
     * \param filename 
     * \return char* the contents of the read file
     */
    char* Read(const std::string& fileName);

private:
    Filesystem();

    /// TODO(wowvain-dev): Finish implementing the FileSystem
};
}

#ifndef DLLINJECT_HPP
#define DLLINJECT_HPP

#include <cstdint>
#include <string>
#include <windows.h>

/**
 * @brief Opens a windows application and injects an external DLL into the process.
 */
class DLLInject
{
public:
    HANDLE        m_process_handle;
    std::uint32_t m_process_pid;
    std::string   m_process_name;
    std::string   m_dll_name;
    void*         m_dll_address;
    std::uint32_t m_poll_interval;

    DLLInject();

    /**
     * @brief Takes all necessary parameters to inject the DLL into another process.
     * @param process_name      Name of the process ("myProgram.exe")
     * @param dll_name          Path and name to the DLL ("C:/myDLLs/myDLL.dll").
     * @param poll_interval     Poll interval to refresh process list (in ms).
     */
    explicit DLLInject(
        const std::string&& process_name,
        const std::string&& dll_name,
        const std::uint32_t poll_interval = 1000);

    /**
     * @brief Starts the injection process (blocking function).
     */
    void run();

    /**
     * @brief   Polls windows process names until the name of the target executable is found.
     *          Polls with a fixed 1 second interval.
     */
    void getPID();

    /**
     * @brief   Opens the process and stores its handle.
     *          Execute this function only after the PID is found.
     */
    void openProcess();

    /**
     * @brief   Allocates memory in the target process and stores the name of the DLL in the opened
     *          process.
     */
    void allocate();

    /**
     * @brief   Calls a thread in the target process and loads the DLL. Once the DLL is injected
     *          the program stops
     */
    void startRemoteThread();
};

#endif  // DLLINJECT_HPP

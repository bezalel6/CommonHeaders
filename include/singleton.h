#ifndef SINGLETON_UTILS_H
#define SINGLETON_UTILS_H

/**
 * @file singleton_utils.h
 * @brief Utility macros for implementing the singleton pattern in embedded C++ projects
 *
 * This header provides macros to easily implement thread-safe singletons
 * while preventing copy construction and assignment.
 */

// Declare the singleton pattern in the class declaration
#define DECLARE_SINGLETON(className)                 \
   private:                                          \
    static className* instance;                      \
    className(const className&) = delete;            \
    className& operator=(const className&) = delete; \
                                                     \
   protected:                                        \
    className() {}                                   \
                                                     \
   public:                                           \
    static className* getInstance() {                \
        if (instance == nullptr) {                   \
            instance = new className();              \
        }                                            \
        return instance;                             \
    }

// Initialize the static instance pointer in the cpp file
#define IMPLEMENT_SINGLETON(className) \
    className* className::instance = nullptr;

// Declare and implement a singleton with automatic memory management
#define DECLARE_MANAGED_SINGLETON(className)         \
   private:                                          \
    static className& instance;                      \
    className(const className&) = delete;            \
    className& operator=(const className&) = delete; \
                                                     \
   protected:                                        \
    className() {}                                   \
                                                     \
   public:                                           \
    static className& getInstance() {                \
        static className instance;                   \
        return instance;                             \
    }

// Helper macro for creating thread-safe singletons using a mutex
#ifdef USE_MUTEX_PROTECTION
#include <mutex>
#define DECLARE_THREADSAFE_SINGLETON(className)      \
   private:                                          \
    static className* instance;                      \
    static std::mutex mutex;                         \
    className(const className&) = delete;            \
    className& operator=(const className&) = delete; \
                                                     \
   protected:                                        \
    className() {}                                   \
                                                     \
   public:                                           \
    static className* getInstance() {                \
        std::lock_guard<std::mutex> lock(mutex);     \
        if (instance == nullptr) {                   \
            instance = new className();              \
        }                                            \
        return instance;                             \
    }

// Implementation macro for thread-safe singleton
#define IMPLEMENT_THREADSAFE_SINGLETON(className) \
    className* className::instance = nullptr;     \
    std::mutex className::mutex;
#endif

// Helper macro for declaring common singleton methods
#define DECLARE_SINGLETON_METHODS(className) \
   public:                                   \
    virtual ~className() {}                  \
    virtual void init() {}                   \
    virtual void update() {}                 \
    virtual void reset() {}

#endif  // SINGLETON_UTILS_H
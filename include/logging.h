#ifndef LOGGING_H_
#define LOGGING_H_
#define MESAURE_TIME_START unsigned long __start = millis();
#define MESAURE_TIME_END millis() - __start
#define LOG_NO_NL(...) \
    Serial.printf(__VA_ARGS__);
#define LOG(...)           \
    LOG_NO_NL(__VA_ARGS__) \
    Serial.println();
#define LOCATION Serial.printf("\tFILE: %s LINE: %d\n", __FILENAME__, __LINE__)
#define HERE(func)                      \
    Serial.printf("IM HERE: %s", func); \
    LOCATION;
#define ENTERED(func)                   \
    Serial.printf("ENTERED: %s", func); \
    LOCATION;
#define DONE(func)                   \
    Serial.printf("DONE: %s", func); \
    LOCATION;

#define STR(a) a->toString().c_str()
#define ONCE(TASK)                \
    {                             \
        static bool done = false; \
        if (!done) {              \
            done = true;          \
            TASK;                 \
        }                         \
    }

#define DO_EVERY_X_TIMES(X, TASK)           \
    {                                       \
        static int ___count = 0;            \
        if (!___count || ++___count >= X) { \
            ___count = 0;                   \
            TASK;                           \
        }                                   \
    }

#define ASSERT(a, details)                                                                                                \
    while (!a) {                                                                                                          \
        Serial.printf("ASSERTION \"%s\" FAILED!!! %s\nON LINE %d\nIN FILE %s\n\n", #details, #a, __LINE__, __FILENAME__); \
        delay(1000);                                                                                                      \
    }
#endif  // LOGGING_H_
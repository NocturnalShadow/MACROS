#ifndef MACRO_H
#define MACRO_H

// Primitive concatenation
#define CONCAT_(arg1, ...) arg1##__VA_ARGS__

// Increment
#define INC(value) CONCAT_(INC_, value)
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9

// Decrement
#define DEC(value) CONCAT_(DEC_, value)
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8

// Multiple preprocessor scans
#define SCAN1(...)  __VA_ARGS__
#define SCAN2(...)  SCAN1(SCAN1(SCAN1(__VA_ARGS__)))
#define SCAN3(...)  SCAN2(SCAN2(SCAN2(__VA_ARGS__)))
#define SCAN4(...)  SCAN3(SCAN3(SCAN3(__VA_ARGS__)))
#define SCAN5(...)  SCAN4(SCAN4(SCAN4(__VA_ARGS__)))
#define SCAN6(...)  SCAN5(SCAN5(SCAN5(__VA_ARGS__)))
#define SCAN7(...)  SCAN6(SCAN6(SCAN6(__VA_ARGS__)))
#define SCAN8(...)  SCAN7(SCAN7(SCAN7(__VA_ARGS__)))

// Maximum scans
#ifdef _MSC_VER
    #define SCAN(...) SCAN6(__VA_ARGS__)
#elif __MINGW32__ || __MINGW64__
    #define SCAN(...) SCAN8(__VA_ARGS__)
#endif

// Defered execution
#define EXEC(macro, ...) SCAN1(DEFER1(macro)(__VA_ARGS__))

// Check 
#ifdef _MSC_VER
    #define CHECK(...) EXEC(ARG2, __VA_ARGS__, 0)
    #define KEY 0, 1,
#elif __MINGW32__
    #define CHECK(...) ARG2(__VA_ARGS__, 0)
    #define KEY 0, 1,
#endif

// Utility
#define VOID()
#define CONSUME(...)
#define ECHO(value) value
#define NOOP(...) (void) 0
#define DEFER1(...) __VA_ARGS__ VOID()
#define DEFER2(...) __VA_ARGS__ DEFER1(VOID)()

// Get argument n
#define ARG1(arg1, ...) arg1
#define ARG2(arg1, arg2, ...) arg2

// To String
#define STRINGIFY(...) #__VA_ARGS__
#define TOSTR(...) EXEC(STRINGIFY, __VA_ARGS__)

// Get first argument if exists
#define FIRST(...) EXEC(FIRST_, __VA_ARGS__,)
#define FIRST_(first, ...) first
// Get all argumets but the first
#define REST(...) EXEC(REST_, __VA_ARGS__)
#define REST_(first, ...) __VA_ARGS__

// If an argument list is empty evaluated to 1 else 0
#define ISEMPTY(...) EXEC(ISEMPTY_, FIRST(__VA_ARGS__))
#define ISEMPTY_(...) CHECK(EMPTY##__VA_ARGS__)
#define EMPTY KEY

// If and only if (condition is 0 or 1 only)
#define IIF(condition) CONCAT_(IIF_, condition)
#define IIF_0(true_, ...) __VA_ARGS__
#define IIF_1(true_, ...) true_

// Complement (value is 0 or 1 only)
#define COMPL(value) CONCAT_(COMPL_, value)
#define COMPL_0 1
#define COMPL_1 0

// Not (1 if and only if value is 0 - else 0)
#define NOT(value) CHECK(EXEC(CONCAT_, NOT_, value))
#define NOT_0 KEY

// Bool (0 if and only if value is 0 - else 1)
#define BOOL(value) COMPL(NOT(value))

// If
#define IF(condition) IIF(BOOL(condition))

// When
#define WHEN(condition) IF(condition)(SCAN1, CONSUME)

// WARNING: unteseted!
// Repeat loop
#define REPEAT(count, _operator, ...) \
    WHEN(count) \
    ( \
        DEFER2(REPEAT_INDIRECT)() ( \
            DEC(count), _operator, __VA_ARGS__ \
        ) \
        DEFER1(_operator) ( \
            DEC(count), __VA_ARGS__ \
        ) \
    )
#define REPEAT_INDIRECT() REPEAT

// WARNING: unteseted!
// For loop
#define FOR(count, _operator) \
    WHEN(count) \
    ( \
        DEFER2(FOR_INDIRECT)() ( \
            DEC(count), _operator \
        ) \
        DEFER1(_operator) ( \
            DEC(count) \
        ) \
    )
#define FOR_INDIRECT() FOR

// WARNING: unteseted!
// While loop
#define WHILE(predicate, _operator, ...) \
    IF(pred(__VA_ARGS__)) \
    ( \
        DEFER2(WHILE_INDIREDT) () ( \
            predicate, _operator, _operator(__VA_ARGS__) \
        ), \
        __VA_ARGS__ \
    )
#define WHILE_INDIREDCT() WHILE

// "Remove coma if no args" trick
#define FIX_COMA_AFTER(...) \
    IF(ISEMPTY(__VA_ARGS__)) (, __VA_ARGS__,)

// Argument count
#define COUNT(...) \
         COUNT_NOT_0(FIX_COMA_AFTER(__VA_ARGS__) ARG_NUMBERS())
#define COUNT_NOT_0(...) \
         EXEC(ARG_N, __VA_ARGS__)
#define ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63, N,...) N
#define ARG_NUMBERS() \
         63,62,61,60, \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

// Applies consequently a macro to each subsequent argument
#define FOR_EACH(macro, ...) SCAN(FOR_EACH_(macro, __VA_ARGS__))
#define FOR_EACH_(macro, ...) \
    WHEN(NOT(ISEMPTY(__VA_ARGS__))) \
    ( \
        EXEC(macro, FIRST(__VA_ARGS__)) \
        DEFER2(FOR_EACH_INDIRECT) () (macro, REST(__VA_ARGS__)) \
    )
#define FOR_EACH_INDIRECT() FOR_EACH_

#endif // MACRO_H

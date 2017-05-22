#ifndef MACRO_H
#define MACRO_H

#define CONCAT_(arg1, ...) arg1##__VA_ARGS__

// increment
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

// decrement
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

// multiple scans
#define SCAN1(...)  __VA_ARGS__
#define SCAN2(...)  SCAN1(SCAN1(SCAN1(__VA_ARGS__)))
#define SCAN3(...)  SCAN2(SCAN2(SCAN2(__VA_ARGS__)))
#define SCAN4(...)  SCAN3(SCAN3(SCAN3(__VA_ARGS__)))
#define SCAN5(...)  SCAN4(SCAN4(SCAN4(__VA_ARGS__)))
#define SCAN(...)   SCAN5(SCAN5(SCAN5(__VA_ARGS__)))

// if and only if
#define IIF(condition) CONCAT_(IIF_, condition)
#define IIF_0(true_, ...) __VA_ARGS__
#define IIF_1(true_, ...) true_

// complement
#define COMPL(value) CONCAT_(COMPL_, value)
#define COMPL_0 1
#define COMPL_1 0

#define ARG2(unused, arg, ...) arg

#define CHECK(...) ARG2(__VA_ARGS__, 0)
#define KEY 0, 1,

// not
#define NOT(value) CHECK(CONCAT_(NOT_, value))
#define NOT_0 KEY

// bool
#define BOOL(value) COMPL(NOT(value))

// if
#define IF(condition) IIF(BOOL(condition))

#define VOID()
#define EAT(...)
#define NOOP(...) (void) 0
#define DEFER1(macro) macro VOID()
#define OBSTRUCT(...) __VA_ARGS__ DEFER1(VOID)()

// when
#define WHEN(condition) IF(condition)(SCAN1, NOOP)

// repeate
#define REPEAT(count, macro, ...) \
    WHEN(count) \
    ( \
        OBSTRUCT(REPEAT_INDIRECT)() ( \
            DEC(count), macro, __VA_ARGS__ \
        ) \
        OBSTRUCT(macro) ( \
            DEC(count), __VA_ARGS__ \
        ) \
    )
#define REPEAT_INDIRECT() REPEAT

// for
#define FOR(count, macro)\
    WHEN(count) \
    ( \
        OBSTRUCT(FOR_INDIRECT)() ( \
            DEC(count), macro \
        ) \
        OBSTRUCT(macro) ( \
            DEC(count) \
        ) \
    )
#define FOR_INDIRECT() FOR

// argument count
#define COUNT(...) \
         COUNT_(__VA_ARGS__, ARG_NUMBERS())
#define COUNT_(...) \
         ARG_N(__VA_ARGS__)
#define ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63, N,...) N
#define ARG_NUMBERS() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0


#endif // MACRO_H

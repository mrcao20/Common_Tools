#pragma once

#define FILLING_PARAM_1(PARAM, args) PARAM(args)
#define FILLING_PARAM_2(PARAM, args, ...)                                      \
    PARAM(args), FILLING_PARAM_1(PARAM, __VA_ARGS__)
#define FILLING_PARAM_3(PARAM, args, ...)                                      \
    PARAM(args), FILLING_PARAM_2(PARAM, __VA_ARGS__)
#define FILLING_PARAM_4(PARAM, args, ...)                                      \
    PARAM(args), FILLING_PARAM_3(PARAM, __VA_ARGS__)
#define FILLING_PARAM_5(PARAM, args, ...)                                      \
    PARAM(args), FILLING_PARAM_4(PARAM, __VA_ARGS__)
#define FILLING_PARAM_6(PARAM, args, ...)                                      \
    PARAM(args), FILLING_PARAM_5(PARAM, __VA_ARGS__)
#define FILLING_PARAM_7(PARAM, args, ...)                                      \
    PARAM(args), FILLING_PARAM_6(PARAM, __VA_ARGS__)
#define FILLING_PARAM_8(PARAM, args, ...)                                      \
    PARAM(args), FILLING_PARAM_7(PARAM, __VA_ARGS__)
#define FILLING_PARAM_9(PARAM, args, ...)                                      \
    PARAM(args), FILLING_PARAM_8(PARAM, __VA_ARGS__)
#define FILLING_PARAM_10(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_9(PARAM, __VA_ARGS__)
#define FILLING_PARAM_11(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_10(PARAM, __VA_ARGS__)
#define FILLING_PARAM_12(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_11(PARAM, __VA_ARGS__)
#define FILLING_PARAM_13(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_12(PARAM, __VA_ARGS__)
#define FILLING_PARAM_14(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_13(PARAM, __VA_ARGS__)
#define FILLING_PARAM_15(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_14(PARAM, __VA_ARGS__)
#define FILLING_PARAM_16(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_15(PARAM, __VA_ARGS__)
#define FILLING_PARAM_17(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_16(PARAM, __VA_ARGS__)
#define FILLING_PARAM_18(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_17(PARAM, __VA_ARGS__)
#define FILLING_PARAM_19(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_18(PARAM, __VA_ARGS__)
#define FILLING_PARAM_20(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_19(PARAM, __VA_ARGS__)
#define FILLING_PARAM_21(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_20(PARAM, __VA_ARGS__)
#define FILLING_PARAM_22(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_21(PARAM, __VA_ARGS__)
#define FILLING_PARAM_23(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_22(PARAM, __VA_ARGS__)
#define FILLING_PARAM_24(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_23(PARAM, __VA_ARGS__)
#define FILLING_PARAM_25(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_24(PARAM, __VA_ARGS__)
#define FILLING_PARAM_26(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_25(PARAM, __VA_ARGS__)
#define FILLING_PARAM_27(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_26(PARAM, __VA_ARGS__)
#define FILLING_PARAM_28(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_27(PARAM, __VA_ARGS__)
#define FILLING_PARAM_29(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_28(PARAM, __VA_ARGS__)
#define FILLING_PARAM_30(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_29(PARAM, __VA_ARGS__)
#define FILLING_PARAM_31(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_30(PARAM, __VA_ARGS__)
#define FILLING_PARAM_32(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_31(PARAM, __VA_ARGS__)
#define FILLING_PARAM_33(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_32(PARAM, __VA_ARGS__)
#define FILLING_PARAM_34(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_33(PARAM, __VA_ARGS__)
#define FILLING_PARAM_35(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_34(PARAM, __VA_ARGS__)
#define FILLING_PARAM_36(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_35(PARAM, __VA_ARGS__)
#define FILLING_PARAM_37(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_36(PARAM, __VA_ARGS__)
#define FILLING_PARAM_38(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_37(PARAM, __VA_ARGS__)
#define FILLING_PARAM_39(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_38(PARAM, __VA_ARGS__)
#define FILLING_PARAM_40(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_39(PARAM, __VA_ARGS__)
#define FILLING_PARAM_41(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_40(PARAM, __VA_ARGS__)
#define FILLING_PARAM_42(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_41(PARAM, __VA_ARGS__)
#define FILLING_PARAM_43(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_42(PARAM, __VA_ARGS__)
#define FILLING_PARAM_44(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_43(PARAM, __VA_ARGS__)
#define FILLING_PARAM_45(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_44(PARAM, __VA_ARGS__)
#define FILLING_PARAM_46(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_45(PARAM, __VA_ARGS__)
#define FILLING_PARAM_47(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_46(PARAM, __VA_ARGS__)
#define FILLING_PARAM_48(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_47(PARAM, __VA_ARGS__)
#define FILLING_PARAM_49(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_48(PARAM, __VA_ARGS__)
#define FILLING_PARAM_50(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_49(PARAM, __VA_ARGS__)
#define FILLING_PARAM_51(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_50(PARAM, __VA_ARGS__)
#define FILLING_PARAM_52(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_51(PARAM, __VA_ARGS__)
#define FILLING_PARAM_53(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_52(PARAM, __VA_ARGS__)
#define FILLING_PARAM_54(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_53(PARAM, __VA_ARGS__)
#define FILLING_PARAM_55(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_54(PARAM, __VA_ARGS__)
#define FILLING_PARAM_56(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_55(PARAM, __VA_ARGS__)
#define FILLING_PARAM_57(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_56(PARAM, __VA_ARGS__)
#define FILLING_PARAM_58(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_57(PARAM, __VA_ARGS__)
#define FILLING_PARAM_59(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_58(PARAM, __VA_ARGS__)
#define FILLING_PARAM_60(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_59(PARAM, __VA_ARGS__)
#define FILLING_PARAM_61(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_60(PARAM, __VA_ARGS__)
#define FILLING_PARAM_62(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_61(PARAM, __VA_ARGS__)
#define FILLING_PARAM_63(PARAM, args, ...)                                     \
    PARAM(args), FILLING_PARAM_62(PARAM, __VA_ARGS__)

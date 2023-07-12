; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; Test lib call simplification of __strcpy_chk calls with various values
; for src, dst, and slen.
;
; RUN: opt < %s -passes=instcombine -S | FileCheck %s

target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:128:128"

@a = common global [60 x i8] zeroinitializer, align 1
@b = common global [60 x i8] zeroinitializer, align 1
@.str = private constant [12 x i8] c"abcdefghijk\00"

; Check cases where slen >= strlen (src).

define ptr @test_simplify1() {
; CHECK-LABEL: @test_simplify1(
; CHECK-NEXT:    call void @llvm.memcpy.p0.p0.i32(ptr noundef nonnull align 1 dereferenceable(12) @a, ptr noundef nonnull align 1 dereferenceable(12) @.str, i32 12, i1 false)
; CHECK-NEXT:    ret ptr @a
;

  %ret = call ptr @__strcpy_chk(ptr @a, ptr @.str, i32 60)
  ret ptr %ret
}

define ptr @test_simplify1_tail() {
; CHECK-LABEL: @test_simplify1_tail(
; CHECK-NEXT:    tail call void @llvm.memcpy.p0.p0.i32(ptr noundef nonnull align 1 dereferenceable(12) @a, ptr noundef nonnull align 1 dereferenceable(12) @.str, i32 12, i1 false)
; CHECK-NEXT:    ret ptr @a
;

  %ret = tail call ptr @__strcpy_chk(ptr @a, ptr @.str, i32 60)
  ret ptr %ret
}

define ptr @test_simplify2() {
; CHECK-LABEL: @test_simplify2(
; CHECK-NEXT:    call void @llvm.memcpy.p0.p0.i32(ptr noundef nonnull align 1 dereferenceable(12) @a, ptr noundef nonnull align 1 dereferenceable(12) @.str, i32 12, i1 false)
; CHECK-NEXT:    ret ptr @a
;

  %ret = call ptr @__strcpy_chk(ptr @a, ptr @.str, i32 12)
  ret ptr %ret
}

define ptr @test_simplify3() {
; CHECK-LABEL: @test_simplify3(
; CHECK-NEXT:    call void @llvm.memcpy.p0.p0.i32(ptr noundef nonnull align 1 dereferenceable(12) @a, ptr noundef nonnull align 1 dereferenceable(12) @.str, i32 12, i1 false)
; CHECK-NEXT:    ret ptr @a
;

  %ret = call ptr @__strcpy_chk(ptr @a, ptr @.str, i32 -1)
  ret ptr %ret
}

; Check cases where there are no string constants.

define ptr @test_simplify4() {
; CHECK-LABEL: @test_simplify4(
; CHECK-NEXT:    [[STRCPY:%.*]] = call ptr @strcpy(ptr noundef nonnull dereferenceable(1) @a, ptr noundef nonnull dereferenceable(1) @b)
; CHECK-NEXT:    ret ptr @a
;

  %ret = call ptr @__strcpy_chk(ptr @a, ptr @b, i32 -1)
  ret ptr %ret
}

define ptr @test_simplify4_tail() {
; CHECK-LABEL: @test_simplify4_tail(
; CHECK-NEXT:    [[STRCPY:%.*]] = tail call ptr @strcpy(ptr noundef nonnull dereferenceable(1) @a, ptr noundef nonnull dereferenceable(1) @b)
; CHECK-NEXT:    ret ptr @a
;

  %ret = tail call ptr @__strcpy_chk(ptr @a, ptr @b, i32 -1)
  ret ptr %ret
}

; Check case where the string length is not constant.

define ptr @test_simplify5() {
; CHECK-LABEL: @test_simplify5(
; CHECK-NEXT:    [[LEN:%.*]] = call i32 @llvm.objectsize.i32.p0(ptr @a, i1 false, i1 false, i1 false)
; CHECK-NEXT:    [[TMP1:%.*]] = call ptr @__memcpy_chk(ptr nonnull @a, ptr nonnull @.str, i32 12, i32 [[LEN]])
; CHECK-NEXT:    ret ptr [[TMP1]]
;

  %len = call i32 @llvm.objectsize.i32.p0(ptr @a, i1 false, i1 false, i1 false)
  %ret = call ptr @__strcpy_chk(ptr @a, ptr @.str, i32 %len)
  ret ptr %ret
}

; Check case where the source and destination are the same.

define ptr @test_simplify6() {
; CHECK-LABEL: @test_simplify6(
; CHECK-NEXT:    [[LEN:%.*]] = call i32 @llvm.objectsize.i32.p0(ptr @a, i1 false, i1 false, i1 false)
; CHECK-NEXT:    [[RET:%.*]] = call ptr @__strcpy_chk(ptr nonnull @a, ptr nonnull @a, i32 [[LEN]])
; CHECK-NEXT:    ret ptr [[RET]]
;

  %len = call i32 @llvm.objectsize.i32.p0(ptr @a, i1 false, i1 false, i1 false)
  %ret = call ptr @__strcpy_chk(ptr @a, ptr @a, i32 %len)
  ret ptr %ret
}

; Check cases where there are no string constants, and is a tail call.

define ptr @test_simplify7() {
; CHECK-LABEL: @test_simplify7(
; CHECK-NEXT:    [[STRCPY:%.*]] = tail call ptr @strcpy(ptr noundef nonnull dereferenceable(1) @a, ptr noundef nonnull dereferenceable(1) @b)
; CHECK-NEXT:    ret ptr @a
;

  %ret = tail call ptr @__strcpy_chk(ptr @a, ptr @b, i32 -1)
  ret ptr %ret
}

; Check case where slen < strlen (src).

define ptr @test_no_simplify1() {
; CHECK-LABEL: @test_no_simplify1(
; CHECK-NEXT:    [[RET:%.*]] = call ptr @__strcpy_chk(ptr nonnull @a, ptr nonnull @b, i32 8)
; CHECK-NEXT:    ret ptr [[RET]]
;

  %ret = call ptr @__strcpy_chk(ptr @a, ptr @b, i32 8)
  ret ptr %ret
}

define ptr @test_no_simplify2(ptr %dst, ptr %src, i32 %a) {
; CHECK-LABEL: @test_no_simplify2(
; CHECK-NEXT:    [[RET:%.*]] = musttail call ptr @__strcpy_chk(ptr [[DST:%.*]], ptr [[SRC:%.*]], i32 60)
; CHECK-NEXT:    ret ptr [[RET]]
;
  %ret = musttail call ptr @__strcpy_chk(ptr %dst, ptr %src, i32 60)
  ret ptr %ret
}

declare ptr @__strcpy_chk(ptr, ptr, i32) nounwind
declare i32 @llvm.objectsize.i32.p0(ptr, i1, i1, i1) nounwind readonly
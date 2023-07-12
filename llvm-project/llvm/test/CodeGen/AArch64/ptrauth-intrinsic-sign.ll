; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple arm64e-apple-darwin -verify-machineinstrs -global-isel=0 | FileCheck %s
; RUN: llc < %s -mtriple arm64e-apple-darwin -verify-machineinstrs -global-isel=1 -global-isel-abort=1 | FileCheck %s

define i64 @test_sign_ia(i64 %arg, i64 %arg1) {
; CHECK-LABEL: test_sign_ia:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    pacia x0, x1
; CHECK-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign(i64 %arg, i32 0, i64 %arg1)
  ret i64 %tmp
}

define i64 @test_sign_ia_zero(i64 %arg) {
; CHECK-LABEL: test_sign_ia_zero:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    paciza x0
; CHECK-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign(i64 %arg, i32 0, i64 0)
  ret i64 %tmp
}

define i64 @test_sign_ib(i64 %arg, i64 %arg1) {
; CHECK-LABEL: test_sign_ib:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    pacib x0, x1
; CHECK-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign(i64 %arg, i32 1, i64 %arg1)
  ret i64 %tmp
}

define i64 @test_sign_ib_zero(i64 %arg) {
; CHECK-LABEL: test_sign_ib_zero:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    pacizb x0
; CHECK-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign(i64 %arg, i32 1, i64 0)
  ret i64 %tmp
}

define i64 @test_sign_da(i64 %arg, i64 %arg1) {
; CHECK-LABEL: test_sign_da:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    pacda x0, x1
; CHECK-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign(i64 %arg, i32 2, i64 %arg1)
  ret i64 %tmp
}

define i64 @test_sign_da_zero(i64 %arg) {
; CHECK-LABEL: test_sign_da_zero:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    pacdza x0
; CHECK-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign(i64 %arg, i32 2, i64 0)
  ret i64 %tmp
}

define i64 @test_sign_db(i64 %arg, i64 %arg1) {
; CHECK-LABEL: test_sign_db:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    pacdb x0, x1
; CHECK-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign(i64 %arg, i32 3, i64 %arg1)
  ret i64 %tmp
}

define i64 @test_sign_db_zero(i64 %arg) {
; CHECK-LABEL: test_sign_db_zero:
; CHECK:       ; %bb.0:
; CHECK-NEXT:    pacdzb x0
; CHECK-NEXT:    ret
  %tmp = call i64 @llvm.ptrauth.sign(i64 %arg, i32 3, i64 0)
  ret i64 %tmp
}

declare i64 @llvm.ptrauth.sign(i64, i32, i64)
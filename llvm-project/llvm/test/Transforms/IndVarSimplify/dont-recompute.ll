; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -passes=indvars -S | FileCheck %s

; This tests that the IV is recomputed outside of the loop even when it is known
; to be computed by the loop and used in the loop any way, if it is cheap to do
; so. In the example below the value can be computed outside of the loop,
; and we should do so because after that IV is no longer used outside of
; the loop, which is likely beneficial for vectorization.
;
; extern void func(unsigned val);
;
; void test(unsigned m)
; {
;   unsigned a = 0;
;
;   for (int i=0; i<186; i++) {
;     a += m;
;     func(a);
;   }
;
;   func(a);
; }

declare void @func(i32)

define void @test(i32 %m) nounwind uwtable {
; CHECK-LABEL: @test(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    br label [[FOR_BODY:%.*]]
; CHECK:       for.body:
; CHECK-NEXT:    [[I_06:%.*]] = phi i32 [ 0, [[ENTRY:%.*]] ], [ [[INC:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[A_05:%.*]] = phi i32 [ 0, [[ENTRY]] ], [ [[ADD:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[ADD]] = add i32 [[A_05]], [[M:%.*]]
; CHECK-NEXT:    tail call void @func(i32 [[ADD]])
; CHECK-NEXT:    [[INC]] = add nuw nsw i32 [[I_06]], 1
; CHECK-NEXT:    [[EXITCOND:%.*]] = icmp eq i32 [[INC]], 186
; CHECK-NEXT:    br i1 [[EXITCOND]], label [[FOR_END:%.*]], label [[FOR_BODY]]
; CHECK:       for.end:
; CHECK-NEXT:    [[ADD_LCSSA:%.*]] = phi i32 [ [[ADD]], [[FOR_BODY]] ]
; CHECK-NEXT:    tail call void @func(i32 [[ADD_LCSSA]])
; CHECK-NEXT:    ret void
;
entry:
  br label %for.body

for.body:                                         ; preds = %for.body, %entry
  %i.06 = phi i32 [ 0, %entry ], [ %inc, %for.body ]
  %a.05 = phi i32 [ 0, %entry ], [ %add, %for.body ]
  %add = add i32 %a.05, %m
  tail call void @func(i32 %add)
  %inc = add nsw i32 %i.06, 1
  %exitcond = icmp eq i32 %inc, 186
  br i1 %exitcond, label %for.end, label %for.body

for.end:                                          ; preds = %for.body
  tail call void @func(i32 %add)
  ret void
}

define i32 @test2(i32 %m) nounwind uwtable {
; CHECK-LABEL: @test2(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    br label [[FOR_BODY:%.*]]
; CHECK:       for.body:
; CHECK-NEXT:    [[I_06:%.*]] = phi i32 [ 0, [[ENTRY:%.*]] ], [ [[INC:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[A_05:%.*]] = phi i32 [ 0, [[ENTRY]] ], [ [[ADD:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[ADD]] = add i32 [[A_05]], [[M:%.*]]
; CHECK-NEXT:    tail call void @func(i32 [[ADD]])
; CHECK-NEXT:    [[INC]] = add nuw nsw i32 [[I_06]], 1
; CHECK-NEXT:    [[EXITCOND:%.*]] = icmp eq i32 [[INC]], 186
; CHECK-NEXT:    br i1 [[EXITCOND]], label [[FOR_END:%.*]], label [[FOR_BODY]]
; CHECK:       for.end:
; CHECK-NEXT:    [[ADD_LCSSA:%.*]] = phi i32 [ [[ADD]], [[FOR_BODY]] ]
; CHECK-NEXT:    ret i32 [[ADD_LCSSA]]
;
entry:
  br label %for.body

for.body:                                         ; preds = %for.body, %entry
  %i.06 = phi i32 [ 0, %entry ], [ %inc, %for.body ]
  %a.05 = phi i32 [ 0, %entry ], [ %add, %for.body ]
  %add = add i32 %a.05, %m
  tail call void @func(i32 %add)
  %inc = add nsw i32 %i.06, 1
  %exitcond = icmp eq i32 %inc, 186
  br i1 %exitcond, label %for.end, label %for.body

for.end:                                          ; preds = %for.body
  ret i32 %add
}

define void @test3(i32 %m) nounwind uwtable {
; CHECK-LABEL: @test3(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    br label [[FOR_BODY:%.*]]
; CHECK:       for.body:
; CHECK-NEXT:    [[I_06:%.*]] = phi i32 [ 0, [[ENTRY:%.*]] ], [ [[INC:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[A_05:%.*]] = phi i32 [ 0, [[ENTRY]] ], [ [[ADD:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[ADD]] = add i32 [[A_05]], [[M:%.*]]
; CHECK-NEXT:    tail call void @func(i32 [[ADD]])
; CHECK-NEXT:    [[INC]] = add nuw nsw i32 [[I_06]], 1
; CHECK-NEXT:    [[EXITCOND:%.*]] = icmp eq i32 [[INC]], 186
; CHECK-NEXT:    br i1 [[EXITCOND]], label [[FOR_END:%.*]], label [[FOR_BODY]]
; CHECK:       for.end:
; CHECK-NEXT:    [[ADD_LCSSA:%.*]] = phi i32 [ [[ADD]], [[FOR_BODY]] ]
; CHECK-NEXT:    tail call void @func(i32 [[ADD_LCSSA]])
; CHECK-NEXT:    ret void
;
entry:
  br label %for.body

for.body:                                         ; preds = %for.body, %entry
  %i.06 = phi i32 [ 0, %entry ], [ %inc, %for.body ]
  %a.05 = phi i32 [ 0, %entry ], [ %add, %for.body ]
  %add = add i32 %a.05, %m
  mul i32 %add, 1
  mul i32 %add, 1
  mul i32 %add, 1
  mul i32 %add, 1
  mul i32 %add, 1
  mul i32 %add, 1
  tail call void @func(i32 %add)
  %inc = add nsw i32 %i.06, 1
  %exitcond = icmp eq i32 %inc, 186
  br i1 %exitcond, label %for.end, label %for.body

for.end:                                          ; preds = %for.body
  tail call void @func(i32 %add)
  ret void
}

define void @test4(i32 %m) nounwind uwtable {
; CHECK-LABEL: @test4(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    br label [[FOR_BODY:%.*]]
; CHECK:       for.body:
; CHECK-NEXT:    [[I_06:%.*]] = phi i32 [ 0, [[ENTRY:%.*]] ], [ [[INC:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[A_05:%.*]] = phi i32 [ 0, [[ENTRY]] ], [ [[ADD:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[ADD]] = add i32 [[A_05]], [[M:%.*]]
; CHECK-NEXT:    tail call void @func(i32 [[ADD]])
; CHECK-NEXT:    [[INC]] = add nuw nsw i32 [[I_06]], 1
; CHECK-NEXT:    [[EXITCOND:%.*]] = icmp eq i32 [[INC]], 186
; CHECK-NEXT:    br i1 [[EXITCOND]], label [[FOR_END:%.*]], label [[FOR_BODY]]
; CHECK:       for.end:
; CHECK-NEXT:    [[ADD_LCSSA:%.*]] = phi i32 [ [[ADD]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[SOFT_USE:%.*]] = add i32 [[ADD_LCSSA]], 123
; CHECK-NEXT:    tail call void @func(i32 [[SOFT_USE]])
; CHECK-NEXT:    ret void
;
entry:
  br label %for.body

for.body:                                         ; preds = %for.body, %entry
  %i.06 = phi i32 [ 0, %entry ], [ %inc, %for.body ]
  %a.05 = phi i32 [ 0, %entry ], [ %add, %for.body ]
  %add = add i32 %a.05, %m
  tail call void @func(i32 %add)
  %inc = add nsw i32 %i.06, 1
  %exitcond = icmp eq i32 %inc, 186
  br i1 %exitcond, label %for.end, label %for.body

for.end:                                          ; preds = %for.body
  %soft_use = add i32 %add, 123
  tail call void @func(i32 %soft_use)
  ret void
}

define void @test5(i32 %m) nounwind uwtable {
; CHECK-LABEL: @test5(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    br label [[FOR_BODY:%.*]]
; CHECK:       for.body:
; CHECK-NEXT:    [[I_06:%.*]] = phi i32 [ 0, [[ENTRY:%.*]] ], [ [[INC:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[A_05:%.*]] = phi i32 [ 0, [[ENTRY]] ], [ [[ADD:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[ADD]] = add i32 [[A_05]], [[M:%.*]]
; CHECK-NEXT:    [[SOFT_USE:%.*]] = add i32 [[ADD]], 123
; CHECK-NEXT:    tail call void @func(i32 [[SOFT_USE]])
; CHECK-NEXT:    [[INC]] = add nuw nsw i32 [[I_06]], 1
; CHECK-NEXT:    [[EXITCOND:%.*]] = icmp eq i32 [[INC]], 186
; CHECK-NEXT:    br i1 [[EXITCOND]], label [[FOR_END:%.*]], label [[FOR_BODY]]
; CHECK:       for.end:
; CHECK-NEXT:    [[ADD_LCSSA:%.*]] = phi i32 [ [[ADD]], [[FOR_BODY]] ]
; CHECK-NEXT:    tail call void @func(i32 [[ADD_LCSSA]])
; CHECK-NEXT:    ret void
;
entry:
  br label %for.body

for.body:                                         ; preds = %for.body, %entry
  %i.06 = phi i32 [ 0, %entry ], [ %inc, %for.body ]
  %a.05 = phi i32 [ 0, %entry ], [ %add, %for.body ]
  %add = add i32 %a.05, %m
  %soft_use = add i32 %add, 123
  tail call void @func(i32 %soft_use)
  %inc = add nsw i32 %i.06, 1
  %exitcond = icmp eq i32 %inc, 186
  br i1 %exitcond, label %for.end, label %for.body

for.end:                                          ; preds = %for.body
  tail call void @func(i32 %add)
  ret void
}

define void @test6(i32 %m, ptr %p) nounwind uwtable {
; CHECK-LABEL: @test6(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    br label [[FOR_BODY:%.*]]
; CHECK:       for.body:
; CHECK-NEXT:    [[I_06:%.*]] = phi i32 [ 0, [[ENTRY:%.*]] ], [ [[INC:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[A_05:%.*]] = phi i32 [ 0, [[ENTRY]] ], [ [[ADD:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[ADD]] = add i32 [[A_05]], [[M:%.*]]
; CHECK-NEXT:    [[SOFT_USE:%.*]] = add i32 [[ADD]], 123
; CHECK-NEXT:    [[PIDX:%.*]] = getelementptr i32, ptr [[P:%.*]], i32 [[ADD]]
; CHECK-NEXT:    store i32 [[SOFT_USE]], ptr [[PIDX]]
; CHECK-NEXT:    [[INC]] = add nuw nsw i32 [[I_06]], 1
; CHECK-NEXT:    [[EXITCOND:%.*]] = icmp eq i32 [[INC]], 186
; CHECK-NEXT:    br i1 [[EXITCOND]], label [[FOR_END:%.*]], label [[FOR_BODY]]
; CHECK:       for.end:
; CHECK-NEXT:    [[ADD_LCSSA:%.*]] = phi i32 [ [[ADD]], [[FOR_BODY]] ]
; CHECK-NEXT:    tail call void @func(i32 [[ADD_LCSSA]])
; CHECK-NEXT:    ret void
;
entry:
  br label %for.body

for.body:                                         ; preds = %for.body, %entry
  %i.06 = phi i32 [ 0, %entry ], [ %inc, %for.body ]
  %a.05 = phi i32 [ 0, %entry ], [ %add, %for.body ]
  %add = add i32 %a.05, %m
  %soft_use = add i32 %add, 123
  %pidx = getelementptr i32, ptr %p, i32 %add
  store i32 %soft_use, ptr %pidx
  %inc = add nsw i32 %i.06, 1
  %exitcond = icmp eq i32 %inc, 186
  br i1 %exitcond, label %for.end, label %for.body

for.end:                                          ; preds = %for.body
  tail call void @func(i32 %add)
  ret void
}
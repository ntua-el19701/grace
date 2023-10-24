@vars_int = private global [11 x i32] zeroinitializer, align 16
@vars_char = private global [5 x i8] zeroinitializer, align 16
@nl = private constant [2 x i8] c"\0A\00", align 1

declare void @writeInteger(i32)

declare void @writeString(ptr)


define void @main() {
main-entry:
  store i32 5, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  store i32 7, ptr getelementptr (ptr, ptr @vars_int, i32 6), align 4
  %y = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  %z = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 6), align 4
  %0 = call i32 @solve(i32 %y, i32 %z)
  store i32 %0, ptr getelementptr (ptr, ptr @vars_int, i32 4), align 4
  ret void
}

define i32 @solve(i32 %0, i32 %1) {
solve-entry:
  store i32 %0, ptr getelementptr (ptr, ptr @vars_int, i32 1), align 4
  store i32 %1, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  %t1 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 1), align 4
  %t2 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  %addtmp = add i32 %t1, %t2
  store i32 %addtmp, ptr getelementptr (ptr, ptr @vars_int, i32 3), align 4
  %m = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 3), align 4
  ret i32 %m
}
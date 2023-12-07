; ModuleID = 'Grace program'
source_filename = "Grace program"

@vars_int = private global [14 x i32] zeroinitializer, align 16
@vars_char = private global [9 x i8] zeroinitializer, align 16
@Array_Int_vars = private global [5 x i32] zeroinitializer, align 16
@Array_Char_vars = private global [5 x i8] zeroinitializer, align 16
@nl = private constant [2 x i8] c"\0A\00", align 1
@varName = private unnamed_addr constant [13 x i8] c"Checking if \00", align 1
@varName.1 = private unnamed_addr constant [16 x i8] c" is equal to 1.\00", align 1
@varName.2 = private unnamed_addr constant [13 x i8] c"Checking if \00", align 1
@varName.3 = private unnamed_addr constant [22 x i8] c" is a capital letter.\00", align 1
@varName.4 = private unnamed_addr constant [13 x i8] c"Checking if \00", align 1
@varName.5 = private unnamed_addr constant [13 x i8] c" is between \00", align 1
@varName.6 = private unnamed_addr constant [6 x i8] c" and \00", align 1
@varName.7 = private unnamed_addr constant [2 x i8] c".\00", align 1
@varName.8 = private unnamed_addr constant [51 x i8] c"\\'isOne\\' function called only for variable \\'x\\'.\00", align 1
@varName.9 = private unnamed_addr constant [36 x i8] c"This message will never be printed.\00", align 1
@varName.10 = private unnamed_addr constant [2 x i8] c"\\\00", align 1
@varName.11 = private unnamed_addr constant [36 x i8] c"This message will never be printed.\00", align 1
@varName.12 = private unnamed_addr constant [69 x i8] c"\\'isUpperCase\\' function call should only happen for variable \\'k\\'.\00", align 1
@varName.13 = private unnamed_addr constant [2 x i8] c"\\\00", align 1
@varName.14 = private unnamed_addr constant [57 x i8] c"Only \\'isWithinLimit\\' function call should happen here.\00", align 1
@varName.15 = private unnamed_addr constant [54 x i8] c"\\'isOne\\' function call should only happen once here.\00", align 1
@varName.16 = private unnamed_addr constant [2 x i8] c"\\\00", align 1
@varName.17 = private unnamed_addr constant [37 x i8] c"This messaged will never be printed.\00", align 1
@varName.18 = private unnamed_addr constant [54 x i8] c"\\'isOne\\' function call should only happen once here.\00", align 1
@varName.19 = private unnamed_addr constant [58 x i8] c"\\'isWithinLimit\\' function call should never happen here.\00", align 1

declare void @writeInteger(i64)

declare void @writeString(ptr)

declare void @writeChar(i8)

declare i32 @readInteger()

declare i8 @readChar()

declare i32 @ascii(i8)

declare i8 @chr(i64)

define i32 @main() {
entry:
  call void @main.1()
  ret i32 0
}

define void @main.1() {
main.1-entry:
  store i32 1, ptr getelementptr (ptr, ptr @vars_int, i32 3), align 4
  store i32 42, ptr getelementptr (ptr, ptr @vars_int, i32 4), align 4
  %x = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 3), align 4
  %isOne-a = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  %0 = call i32 @isOne(i32 %x)
  store i32 %isOne-a, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  %1 = icmp eq i32 %0, 1
  %y = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 4), align 4
  %isOne-a1 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  %2 = call i32 @isOne(i32 %y)
  store i32 %isOne-a1, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  %3 = icmp eq i32 %2, 1
  %4 = or i1 %1, %3
  %if_cond = icmp ne i1 %4, false
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %main.1-entry
  call void @writeString(ptr @varName.8)
  call void @writeString(ptr @nl)
  br label %endif

else:                                             ; preds = %main.1-entry
  call void @writeString(ptr @varName.9)
  call void @writeString(ptr @nl)
  br label %endif

endif:                                            ; preds = %else, %then
  call void @writeString(ptr @varName.10)
  call void @writeString(ptr @nl)
  store i8 110, ptr getelementptr (ptr, ptr @vars_char, i32 2), align 1
  store i8 83, ptr getelementptr (ptr, ptr @vars_char, i32 3), align 1
  %k = load i8, ptr getelementptr (ptr, ptr @vars_char, i32 2), align 1
  %isUpperCase-asciiNum = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 6), align 4
  %isUpperCase-c = load i32, ptr getelementptr (ptr, ptr @vars_char, i32 4), align 4
  %5 = call i32 @isUpperCase(i8 %k)
  store i32 %isUpperCase-asciiNum, ptr getelementptr (ptr, ptr @vars_int, i32 6), align 4
  store i32 %isUpperCase-c, ptr getelementptr (ptr, ptr @vars_char, i32 4), align 4
  %6 = icmp eq i32 %5, 1
  %l = load i8, ptr getelementptr (ptr, ptr @vars_char, i32 3), align 1
  %isUpperCase-asciiNum2 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 6), align 4
  %isUpperCase-c3 = load i32, ptr getelementptr (ptr, ptr @vars_char, i32 4), align 4
  %7 = call i32 @isUpperCase(i8 %l)
  store i32 %isUpperCase-asciiNum2, ptr getelementptr (ptr, ptr @vars_int, i32 6), align 4
  store i32 %isUpperCase-c3, ptr getelementptr (ptr, ptr @vars_char, i32 4), align 4
  %8 = icmp eq i32 %7, 1
  %9 = and i1 %6, %8
  %if_cond4 = icmp ne i1 %9, false
  br i1 %if_cond4, label %then5, label %else6

then5:                                            ; preds = %endif
  call void @writeString(ptr @varName.11)
  call void @writeString(ptr @nl)
  br label %endif7

else6:                                            ; preds = %endif
  call void @writeString(ptr @varName.12)
  call void @writeString(ptr @nl)
  br label %endif7

endif7:                                           ; preds = %else6, %then5
  call void @writeString(ptr @varName.13)
  call void @writeString(ptr @nl)
  store i32 41, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  br label %loop

loop:                                             ; preds = %body, %endif7
  %i = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  %isWithinLimit-highLimit = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 9), align 4
  %isWithinLimit-lowLimit = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 8), align 4
  %isWithinLimit-value = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 7), align 4
  %10 = call i32 @isWithinLimit(i32 %i, i32 17, i32 42)
  store i32 %isWithinLimit-highLimit, ptr getelementptr (ptr, ptr @vars_int, i32 9), align 4
  store i32 %isWithinLimit-lowLimit, ptr getelementptr (ptr, ptr @vars_int, i32 8), align 4
  store i32 %isWithinLimit-value, ptr getelementptr (ptr, ptr @vars_int, i32 7), align 4
  %11 = icmp eq i32 %10, 1
  %i8 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  %isOne-a9 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  %12 = call i32 @isOne(i32 %i8)
  store i32 %isOne-a9, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  %13 = icmp eq i32 %12, 1
  %14 = or i1 %11, %13
  %while_cond = icmp ne i1 %14, false
  br i1 %while_cond, label %body, label %endwhile

body:                                             ; preds = %loop
  call void @writeString(ptr @varName.14)
  call void @writeString(ptr @nl)
  %i10 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  %addtmp = add i32 %i10, 1
  store i32 %addtmp, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  br label %loop

endwhile:                                         ; preds = %loop
  call void @writeString(ptr @varName.15)
  call void @writeString(ptr @nl)
  call void @writeString(ptr @varName.16)
  call void @writeString(ptr @nl)
  store i32 0, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  br label %loop11

loop11:                                           ; preds = %body12, %endwhile
  %i14 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  %isOne-a15 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  %15 = call i32 @isOne(i32 %i14)
  store i32 %isOne-a15, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  %16 = icmp eq i32 %15, 1
  %i16 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  %isWithinLimit-highLimit17 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 9), align 4
  %isWithinLimit-lowLimit18 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 8), align 4
  %isWithinLimit-value19 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 7), align 4
  %17 = call i32 @isWithinLimit(i32 %i16, i32 -1, i32 1)
  store i32 %isWithinLimit-highLimit17, ptr getelementptr (ptr, ptr @vars_int, i32 9), align 4
  store i32 %isWithinLimit-lowLimit18, ptr getelementptr (ptr, ptr @vars_int, i32 8), align 4
  store i32 %isWithinLimit-value19, ptr getelementptr (ptr, ptr @vars_int, i32 7), align 4
  %18 = icmp eq i32 %17, 1
  %19 = and i1 %16, %18
  %while_cond20 = icmp ne i1 %19, false
  br i1 %while_cond20, label %body12, label %endwhile13

body12:                                           ; preds = %loop11
  call void @writeString(ptr @varName.17)
  call void @writeString(ptr @nl)
  %i21 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  %addtmp22 = add i32 %i21, 1
  store i32 %addtmp22, ptr getelementptr (ptr, ptr @vars_int, i32 2), align 4
  br label %loop11

endwhile13:                                       ; preds = %loop11
  call void @writeString(ptr @varName.18)
  call void @writeString(ptr @nl)
  call void @writeString(ptr @varName.19)
  call void @writeString(ptr @nl)
  ret void
}

define i32 @isOne(i32 %0) {
isOne-entry:
  store i32 %0, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  call void @writeString(ptr @varName)
  %a = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  %ext = sext i32 %a to i64
  call void @writeInteger(i64 %ext)
  call void @writeString(ptr @varName.1)
  call void @writeString(ptr @nl)
  %a1 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 5), align 4
  %1 = icmp eq i32 %a1, 1
  %if_cond = icmp ne i1 %1, false
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %isOne-entry
  ret i32 1

else:                                             ; preds = %isOne-entry
  ret i32 0

endif:                                            ; No predecessors!
  ret i32 0
}

define i32 @isUpperCase(i8 %0) {
isUpperCase-entry:
  store i8 %0, ptr getelementptr (ptr, ptr @vars_char, i32 4), align 1
  call void @writeString(ptr @varName.2)
  %c = load i8, ptr getelementptr (ptr, ptr @vars_char, i32 4), align 1
  call void @writeChar(i8 %c)
  call void @writeString(ptr @nl)
  call void @writeString(ptr @varName.3)
  call void @writeString(ptr @nl)
  %c1 = load i8, ptr getelementptr (ptr, ptr @vars_char, i32 4), align 1
  %1 = call i32 @ascii(i8 %c1)
  store i32 %1, ptr getelementptr (ptr, ptr @vars_int, i32 6), align 4
  %asciiNum = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 6), align 4
  %2 = icmp sge i32 %asciiNum, 65
  %asciiNum2 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 6), align 4
  %3 = icmp sle i32 %asciiNum2, 91
  %4 = and i1 %2, %3
  %if_cond = icmp ne i1 %4, false
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %isUpperCase-entry
  ret i32 1

else:                                             ; preds = %isUpperCase-entry
  ret i32 0

endif:                                            ; No predecessors!
  ret i32 0
}

define i32 @isWithinLimit(i32 %0, i32 %1, i32 %2) {
isWithinLimit-entry:
  store i32 %0, ptr getelementptr (ptr, ptr @vars_int, i32 7), align 4
  store i32 %1, ptr getelementptr (ptr, ptr @vars_int, i32 8), align 4
  store i32 %2, ptr getelementptr (ptr, ptr @vars_int, i32 9), align 4
  call void @writeString(ptr @varName.4)
  %value = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 7), align 4
  %ext = sext i32 %value to i64
  call void @writeInteger(i64 %ext)
  call void @writeString(ptr @varName.5)
  %lowLimit = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 8), align 4
  %ext1 = sext i32 %lowLimit to i64
  call void @writeInteger(i64 %ext1)
  call void @writeString(ptr @varName.6)
  %highLimit = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 9), align 4
  %ext2 = sext i32 %highLimit to i64
  call void @writeInteger(i64 %ext2)
  call void @writeString(ptr @varName.7)
  call void @writeString(ptr @nl)
  %value3 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 7), align 4
  %lowLimit4 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 8), align 4
  %3 = icmp sgt i32 %value3, %lowLimit4
  %value5 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 7), align 4
  %highLimit6 = load i32, ptr getelementptr (ptr, ptr @vars_int, i32 9), align 4
  %4 = icmp slt i32 %value5, %highLimit6
  %5 = and i1 %3, %4
  %if_cond = icmp ne i1 %5, false
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %isWithinLimit-entry
  ret i32 1

else:                                             ; preds = %isWithinLimit-entry
  ret i32 0

endif:                                            ; No predecessors!
  ret i32 0
}

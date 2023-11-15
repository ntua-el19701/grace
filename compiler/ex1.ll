
; ModuleID = 'Grace program'
source_filename = "Grace program"

@vars_int = private global [5 x i32] zeroinitializer, align 16
@vars_char = private global [6 x i8] zeroinitializer, align 16
@Array_Int_vars = private global [5 x i32] zeroinitializer, align 16
@Array_Char_vars = private global [5 x i8] zeroinitializer, align 16
@nl = private constant [2 x i8] c"\0A\00", align 1
@varName = private unnamed_addr constant [5 x i8] c"\22hi\22\00", align 1

declare void @writeInteger(i64)

declare void @writeString(ptr)

declare void @writeChar(i8)

define i32 @main() {
entry:
  call void @main.1()
  ret i32 0
}

define void @main.1() {
main.1-entry:
  store i8 97, ptr @vars_int, align 1
  call void @writeInteger(i64 5)
  call void @writeString(ptr @nl)
  call void @writeString(ptr @varName)
  call void @writeString(ptr @nl)
  ret void
}


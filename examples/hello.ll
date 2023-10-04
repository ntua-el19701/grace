@.str = private constant [14 x i8] c"Hello, LLVM!\0A\00"

declare i32 @printf(i8*, ...)

define i32 @main() {
    ; Call the printf function to print the string
    call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i32 0, i32 0))
    ; Return 0 to indicate successful execution
    ret i32 0
}

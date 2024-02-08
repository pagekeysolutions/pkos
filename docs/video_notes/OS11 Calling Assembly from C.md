# OS11: Calling Asm from C
Saturday, July 11, 2020
6:43 PM
 
-   We figure out how to call stuff in our asm file from our C kernel file
-   This will be essential for understanding how we write to IO memory, which is covered in the next lesson
-   We already access C code from the assembly file - we call the main method in kernel.c
-   Now we\'ll be going the other way - calling a function defined in assembly from C
-   Just do a screen cap
    1.  Add the assembly function
        i.  How we use the stack to grab variables
    1.  Add global in the assembly file to make it accessible to C
    2.  In the C file, define the header
    3.  Use the function in the C file and try it out

Info for the stack reference:
<https://en.wikipedia.org/wiki/Call_stack>
<https://en.wikipedia.org/wiki/X86_calling_conventions>
<https://stackoverflow.com/questions/25896145/what-happens-to-ebp-when-calling-a-function>

section .data
    three dq 3.0
    two dq 2.0
    six dq 6.0
    zero_six dq 0.6
section .text
global function3
function3:
    enter 0, 0
    finit
    fld qword [three]
    fld qword [ebp + 8]
    ; st0 = x
    ; st1 = 3
    fdivp ; st0 = 3 / x
    leave
    ret
global function3_derivative
function3_derivative:
    enter 0, 0
    finit
    fld qword [ebp + 8]
    fld qword [ebp + 8]
    fmulp
    fld qword [three]
    fchs
    fld st1
    ; st0 = x ^ 2
    ; st1 = -3
    fdivp
    ; st0 = -3 / x ^ 2
    leave
    ret

global function2
function2:
    enter 0, 0
    finit
    fld qword [ebp + 8]
    fld qword [two]
    ; st0 = 2
    ; st1 = x
    fsubp
    ; st0 = x - 2
    fld st0
    fld st0
    ; st0 = x - 2
    ; st1 = x - 2
    ; st2 = x - 2
    fmulp st1, st0; st0 = (x - 2) ^ 2
    fmulp st1, st0
    fld1
    ; st0 = 1
    ; st1 = (x - 2) ^ 3
    fsubp ; st0 = (x - 2) ^ 3 - 1
    leave
    ret
global function2_derivative
function2_derivative:
    enter 0, 0
    finit
    fld qword [ebp + 8]
    fld qword [two]
    ; st0 = 2
    ; st1 = x
    fsubp
    ; st0 = x - 2
    fld st0
    fld qword[three]
    fmulp
    fmulp
    ; st0 = 3(x - 2) ^ 2
    leave 
    ret
global function1
function1:
    enter 0, 0
    finit
    fld qword[ebp + 8]
    fld qword[zero_six]
    ; st0 = 0.6
    ; st1 = x
    fmulp
    ; st0 = 0.6x
    fld qword[three]
    faddp
    ; st0 = 0.6x + 3
    leave
    ret
global function1_derivative
function1_derivative:
    enter 0, 0
    finit
    fld qword[zero_six]
    ; st0 = 0.6
    leave 
    ret
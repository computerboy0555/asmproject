;sound
include \masm32\include\winmm.inc
includelib \masm32\lib\winmm.lib 


.code

Key_pressed_space proc ;func that check if the space is pressed and active jump if it is
mov ebx, edi
add ebx, SPACE_OFST
invoke GetAsyncKeyState,[ebx] ;throw to eax 1 if key pressed
cmp eax, 0
jne jumpfunc
ret
jumpfunc:
mov ecx,JUMPING
mov [edi+isJump_adr], ecx

ret
Key_pressed_space endp

jump proc adrObj:DWORD ;func that do the jump
	
	mov edi, adrObj
	mov ecx, JUMPING
	cmp [edi+isJump_adr],ecx  
	jne dontjump
	xor edx,edx
	mov eax, JUMP_POWER
	mov ebx, [edi+JUMP_LVL_OFST]
	cmp ebx, 0
	je reset
	mov ebx, 2	
	div ebx 
	mov ebx, [edi+JUMP_LVL_OFST]
	cmp eax, ebx
	jl jumpp
	jg drop
	jumpp:
	
	sub [edi + DINO_Y_OFST], ecx
	sub [edi+JUMP_LVL_OFST], ecx
	ret
	drop:
	
	add [edi + DINO_Y_OFST], ecx
	sub [edi+JUMP_LVL_OFST], ecx
	
	mov ecx, [edi+JUMP_LVL_OFST]
	cmp ecx, 0
	je dontjump
	ret

	
dontjump:
mov ecx, STANDING
mov [edi+isJump_adr], ecx
ret
reset:

mov ecx, 2
add [edi + DINO_Y_OFST], ecx
mov eax, JUMP_POWER
mov [edi+JUMP_LVL_OFST],eax

ret
jump endp











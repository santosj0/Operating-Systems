[BITS 16]
[ORG 0x0000]	;Bootloader jumped to this position (0x1000:0x000)
				;Which is physical address 0x10000. ORG represents the
				;the offset from the beginning of our segment
				
;Out bootloader jumped to 0x1000:0x0000 which sets cx=0x1000 and IP=0x0000
;Now we have to manually set the DS register so it can properly find our variables

mov ax, cs
mov ds, ax		;Copy cs to ds (cannot be done directly, so ax is mediator)

call pumpkin              ;Calls the pumpkin function
cli                       ;Stop interrupts
hlt                       ;Halts system until interrupt call

;---------------------------------------------------------
;Variable section
data:
	xaxis dw 21
	yaxis dw 6
	color dw 02h
	cloop db 0
	counter db 0
	
;---------------------------------------------------------
;Pumpkin Function

pumpkin:
	;Order of section jmps
	;Set video mode to 0Dh
	;Determine/Increment CounterP
	;Determine Color/Position
	;Draw the Pumpkin
	;Cause Delay
	;Reset Video Mode
;--------------------------------------------------------------
.video
	mov ah, 00h             ;Interrupt Call / Set Video Mode
	mov al, 0Dh     		;0Dh - graphical mode
							;320 x 200 w/ 16 colors
							;x-axis: 0-319 | y-axis: 0-199
	int 10h			  		;Runs the interrupt call
	jmp .counterpumpkin

;--------------------------------------------------------------
.counterpumpkin
	;First makes a check then
	;Increase the counter
	cmp byte [cloop], 5
	je .resetcounter
	inc byte [cloop]
	jmp .colpos
.resetcounter
	mov byte [cloop], 0
	jmp .colpos
	
;--------------------------------------------------------------
.colpos
	cmp byte [cloop], 1
	je .color1
	cmp byte [cloop], 2
	je .color2
	cmp byte [cloop], 3
	je .color3
	cmp byte [cloop], 4
	je .color4
	cmp byte [cloop], 5
	je .color5
.color1
	mov word [color], 0Bh
	mov word [xaxis], 21
	mov word [yaxis], 6
	jmp .pixel
.color2
	mov word [color], 0Ah
	mov word [xaxis], 100
	mov word [yaxis], 100
	jmp .pixel
.color3
	mov word [color], 0Ch
	mov word [xaxis], 280
	mov word [yaxis], 20
	jmp .pixel
.color4
	mov word [color], 0Dh
	mov word [xaxis], 40
	mov word [yaxis], 150
	jmp .pixel
.color5
	mov word [color], 0Fh
	mov word [xaxis], 280
	mov word [yaxis], 160
	jmp .pixel

;--------------------------------------------------------------
;Start creating the pumpkin
;First position
.pixel
	mov ah, 0Ch			  ;Interrupt Call / Set Graphical Pixel
	mov al, 02h		  	  ;Color - Green
	mov bh, 0			  ;Page number / First Page
	mov cx, [xaxis]		  ;X coordinate
	mov dx, [yaxis]		  ;Y coordinate 
	int 10h			  	  ;Runs the interrupt call
	
;Stem
.row1
	inc cx
	int 10h
.row2
	inc dx
	int 10h
	inc cx
	int 10h
.row3
	inc dx
	int 10h
	dec cx
	int 10h
.row4
	inc dx
	int 10h
	inc cx
	int 10h
	inc cx
	int 10h
.row5
	inc dx
	sub cx, 3
	int 10h
.loop
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 4
	je .row6
	jmp .loop
.row6
	inc dx
	int 10h
	sub cx, 2
	int 10h
	sub cx, 2
	int 10h

;Body
.r1_b_p1				;r stands for row, b stands for body, p stands for part
	sub dx, 2
	sub cx, 5
	mov al, [color]				;Changes color to an ugly not orange color
	int 10h
	mov byte [counter], 0
.loopr1_b_p1
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 3
	je .r1_b_p2
	jmp .loopr1_b_p1
.r1_b_p2
	add cx, 7
	int 10h
	mov byte [counter], 0
.loopr1_b_p2
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 3
	je .r2_b_p1										
	jmp .loopr1_b_p2
.r2_b_p1
	inc dx
	sub cx, 14
	int 10h
	mov byte [counter], 0
.loopr2_b_p1
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 5
	je .r2_b_p2
	jmp .loopr2_b_p1
.r2_b_p2
	add cx, 6
	int 10h
	mov byte [counter], 0
.loopr2_b_p2
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 4
	je .r3_b_p1				
	jmp .loopr2_b_p2		
.r3_b_p1
	inc dx
	sub cx, 16
	int 10h
	mov byte [counter], 0
.loopr3_b_p1
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 6
	je .r3_b_p2
	jmp .loopr3_b_p1
.r3_b_p2
	add cx, 2
	int 10h
	add cx, 2
	int 10h
	add cx, 2
	int 10h
	mov byte [counter], 0
.loopr3_b_p2
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 5
	je .r4_b_p1
	jmp .loopr3_b_p2
.r4_b_p1
	inc dx
	sub cx, 18
	int 10h
	mov byte [counter], 0
.loopr4_b_p1
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 19
	je .r5_b_p1
	jmp .loopr4_b_p1
.r5_b_p1
	inc dx
	int 10h
	mov byte [counter], 0
.loopr5_b_p1
	dec cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 4
	je .r5_b_p2
	jmp .loopr5_b_p1
.r5_b_p2
	sub cx, 2
	int 10h
	mov byte [counter], 0
.loopr5_b_p2
	dec cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 6
	je .r5_b_p3
	jmp .loopr5_b_p2
.r5_b_p3
	sub cx, 2
	int 10h
	mov byte [counter], 0
.loopr5_b_p3
	dec cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 5
	je .r6_b_p1					
	jmp .loopr5_b_p3
.r6_b_p1
	inc dx
	dec cx
	int 10h
	mov byte [counter], 0
.loopr6_b_p1
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 5
	je .r6_b_p2
	jmp .loopr6_b_p1				
.r6_b_p2
	add cx, 4
	int 10h
	mov byte [counter], 0
.loopr6_b_p2
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 4
	je .r6_b_p3
	jmp .loopr6_b_p2
.r6_b_p3
	add cx, 4
	int 10h
	mov byte [counter], 0
.loopr6_b_p3
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 4
	je .r7_b_p1
	jmp .loopr6_b_p3
.r7_b_p1
	inc dx
	int 10h
	mov byte [counter], 0
.loopr7_b_p1
	dec cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 3
	je .r7_b_p2
	jmp .loopr7_b_p1
.r7_b_p2
	sub cx, 6
	int 10h
	sub cx, 2
	int 10h
	sub cx, 6
	int 10h
	mov byte [counter], 0
.loopr7_b_p2
	dec cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 4
	je .r8_b_p1
	jmp .loopr7_b_p2
.r8_b_p1
	inc dx
	int 10h
	mov byte [counter], 0
.loopr8_b_p1
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 9
	je .r8_b_p2
	jmp .loopr8_b_p1
.r8_b_p2
	add cx, 4
	int 10h
	mov byte [counter], 0
.loopr8_b_p2
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 8
	je .r9_b_p1
	jmp .loopr8_b_p2
.r9_b_p1
	inc dx
	int 10h
	mov byte [counter], 0
.loopr9_b_p1
	dec cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 7
	je .r9_b_p2
	jmp .loopr9_b_p1
.r9_b_p2
	sub cx, 6
	int 10h
	mov byte [counter], 0
.loopr9_b_p2
	dec cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 8
	je .r10_b_p1
	jmp .loopr9_b_p2
.r10_b_p1
	inc dx
	int 10h
	mov byte [counter], 0
.loopr10_b_p1
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 21
	je .r11_b_p1
	jmp .loopr10_b_p1
.r11_b_p1
	inc dx
	int 10h
	mov byte [counter], 0
	dec cx
	int 10h
	dec cx
	int 10h
	sub cx, 4
	int 10h
	dec cx
	int 10h
	sub cx, 5
	int 10h
	dec cx
	int 10h
	sub cx, 4
	int 10h
.loopr11_b_p1
	dec cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 4
	je .r12_b_p1
	jmp .loopr11_b_p1
.r12_b_p1
	inc dx
	inc cx
	int 10h
	mov byte [counter], 0
.loopr12_b_p1
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 4
	je .r12_b_p2
	jmp .loopr12_b_p1
.r12_b_p2
	add cx, 13
	int 10h
	mov byte [counter], 0
	inc cx
	int 10h
	inc cx
	int 10h
.r13_b_p1
	inc dx
	int 10h
.loopr13_b_p1
	dec cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 3
	je .r13_b_p2
	jmp .loopr13_b_p1
.r13_b_p2
	sub cx, 11
	int 10h
	mov byte [counter], 0
.loopr13_b_p2
	dec cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 5
	je .r14_b_p1
	jmp .loopr13_b_p2
.r14_b_p1
	inc dx
	inc cx
	int 10h
	mov byte [counter], 0
.loopr14_b_p1
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 5
	je .r14_b_p2
	jmp .loopr14_b_p1
.r14_b_p2
	add cx, 4
	int 10h
	inc cx
	int 10h
	add cx, 3
	int 10h
	mov byte [counter], 0
.loopr14_b_p2
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 4
	je .r15_b_p1
	jmp .loopr14_b_p2
.r15_b_p1
	inc dx
	dec cx
	int 10h
	mov byte [counter], 0
.loopr15_b_p1
	dec cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 15
	je .r16_b_p1
	jmp .loopr15_b_p1
.r16_b_p1
	inc dx
	add cx, 2
	int 10h
	mov byte [counter], 0
.loopr16_b_p1
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 4
	je .r16_b_p2
	jmp .loopr16_b_p1
.r16_b_p2
	add cx, 3
	int 10h
	mov byte [counter], 0
.loopr16_b_p2
	inc cx
	int 10h
	inc byte [counter]
	cmp byte [counter], 4
	je .delay
	jmp .loopr16_b_p2
;--------------------------------------------------------
;Delay function
.delay
	;Creates a 1 second delay
	mov byte [counter], 0
	mov cx, 0Fh			  
	mov dx, 4240h		  
	mov ah, 86h
	int 15h
	jmp .reset

;--------------------------------------------------------
;Reset Function
.reset
	;Clears the screen
	mov ah, 00h
	mov al, 00h
	int 10h
	jmp .video		
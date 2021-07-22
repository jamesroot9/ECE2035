#=================================================================
# Copyright 2020 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================

# P1-2
# Student Name: James Root
# Date: 10/6/20
#
#     
#
# This routine finds an exact match of George's face in a crowd.
# The result is stored in $2 and reported by swi 553.

.data
Image:  .alloc	1024

.text

FindGeorge:	addi $1, $0, Image					# Image array base addr
			swi	551								# generate crowd
	    	addiu $2, $0, 5 					# set up initial pixel counter at index 5
	    	addi $11, $0, 2						# Hat color value (red)
	    	addi $12, $0, 1						# Hat pattern value (white)
	    	addi $13, $0, 5						# George face/no glasses value
	    	addi $14, $0, 3						# Eye color values
	    	addi $15, $0, 8						# Curved mouth value
	    	addiu $16, $0, 7					# Collar color value
Pixel:		lbu $6, Image($2)					# load pixel value
			slti $6, $6, 3						# check to see if pixel is white or red
			beq $6, $0 PxlEnd					# if not red/white go to PxlEnd
ExaminPrep: add $4, $1, $2						# store temporary pixel examining value
Examine:	lbu $8, 1($4)						# load pixel value for pixel underneath address stored at $4
			lbu $9, 64($4)						# load pixel value for pixel to the right of address stored at $4
			slti $8, $8, 9						# store truth of below pixel being red or white
			slti $9, $9, 9						# store truth of right pixel being non background
If:			beq $9, $0, Verify					# bottom right of hat reached, test face
			bne $8, $0, Right 					# if right pixel is not a background block, move there
Down:		addiu $4, $4, 64					# increment temp variable by 64 (move down)
			j Examine 							# jump to top of iterative loop
Right:		addi $4, $4, 1						# increment temp variable by 1 (move right)
			j Examine 							# jump to top of iterative loop
Verify:		lbu $6, -197($4)					# load pixel value for $4
			bne $6, $12, PxlEnd					# check to see if pixel is white
			lbu $6, 59($4)						# load pixel value for $4
			bne $6, $13, PxlEnd					# check to see if pixel is yellow
			lbu $6, 60($4)						# load pixel value for $4
			bne $6, $14, PxlEnd					# check to see if pixel is blue
			lbu $6, 189($4)						# load pixel value for $4
			bne $6, $15, PxlEnd					# check to see if pixel is black
			lbu $6, 443($4)						# load pixel value for $4
			beq $6, $16, Found					# check to see if pixel is green
PxlEnd:		addi $2, $2, 20						# increment pixel counter by 20
			j Pixel 							# jump back to the top of Pixel loop
Found:		addi $2, $4, -261					# store the top of hat pixel address for george in $2
			sub $2, $2, $1						# subtract Image address from $2 to get top of hat pixel #
			swi	553								# submit answer and check
			jr	$31								# otherwise return to caller

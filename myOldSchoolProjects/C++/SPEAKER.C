/* -------------------------------------------------
File name: speaker.c
 Course: Real Time
 Subject: Using the 8254 (PIT) to control the speaker.
 Author: Arie Guttman
 --------------------------------------------------*/

#include<stdio.h>
#include<dos.h>

#define     ON                  1
#define     OFF                 0
#define     FREQUENCY           1193180L
#define     WORD                0377
#define     WORD_LEN            8

/* -----------------14/5/98 10:20PM------------------
Port addreses of the 8254
 --------------------------------------------------*/
#define     COUNTER_0_PORT      0x40
#define     COUNTER_1_PORT      0x41
#define     COUNTER_2_PORT      0x42
#define     CTRL_WORD_PORT      0x43

/* -----------------14/5/98 11:00PM------------------
Port address for the speaker
 --------------------------------------------------*/
#define     SPEAKER_PORT        0x61


/* ----------------------------------------------------
function name: SetFreq
 Purpose:  Set the frequency of the oscillator feeding
	    the speaker thorough the 8254 counter 2.
 Description:
		1) Calculate the divisor.
		2) program the 8254 sending the
		    a control word.
		3) Init the counter 2 (LSB)
		4) Init the counter 2 (MSB).
 Input :
  unsigned hertz : frequency of the tone.

 Output: none.
 --------------------------------------------------*/
void SetFreq(unsigned hertz)
{
    unsigned divisor = (unsigned)FREQUENCY/hertz;

    /* -----------------14/5/98 10:35PM------------------
    Write the control word:
     0xB6 == 10 11 011 0
     counter 2, R/W LSB first, Mode 3, Binary counter 16 bits.
     --------------------------------------------------*/
    outportb(CTRL_WORD_PORT, 0xB6);
    delay(300);
	 /* -----------------14/5/98 10:41PM------------------
	 Init the counter 2, first the LSB, ther the MSB
	  --------------------------------------------------*/
	 outportb(COUNTER_2_PORT, divisor & WORD);
	 delay(300);
	 outportb(COUNTER_2_PORT, divisor >> WORD_LEN);
	 delay(300);
}
/* ----------------------------------------------------
function name: Speaker
 Purpose:  Set Turn the speaker on or off
 Description:
					 1) Read a word from the speaker (8255 - Port b).
					 2) Connect or disconnect the speaker to the 8254..
					 3) Write the new word to the 8255

 Input :
  int on : status desired for the speaker.

 Output: none.
 --------------------------------------------------*/
void Speaker(int on)
{
	 unsigned PortValue;

	 /* -----------------14/5/98 10:54PM------------------
	 Read the port value.
	  --------------------------------------------------*/
	 PortValue = inportb(SPEAKER_PORT) ;
	  delay(300);
	 /* -----------------14/5/98 10:55PM------------------
	 Connect or disconnect the speaker to the 8254.
	  --------------------------------------------------*/
	 if (on)   PortValue |= 03 ;
	 else      PortValue &= ~03 ;

	 /* -----------------14/5/98 10:55PM------------------
	 Write the result to the port.
	  --------------------------------------------------*/
	 outportb(SPEAKER_PORT, PortValue) ;
	 delay(300);
}
main()
{
	 Speaker(OFF);                       /* Close the speaker */
	 delay(300);
	 SetFreq(200);                       /* Set frequency to 200 Hertz */
	 delay(300);
	 Speaker(ON);                        /* Open the speaker */
	 delay(300);
	 Speaker(OFF);                       /* Close the speaker */
	 return(0);
}
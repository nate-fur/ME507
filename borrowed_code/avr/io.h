/* Copyright (c) 2002,2003,2005,2006,2007 Marek Michalkiewicz, Joerg Wunsch
   Copyright (c) 2007 Eric B. Weddington
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

/* $Id$ */

/** \file */
/** \defgroup avr_io <avr/io.h>: AVR device-specific IO definitions
    \code #include <avr/io.h> \endcode

    This header file includes the apropriate IO definitions for the
    device that has been specified by the <tt>-mmcu=</tt> compiler
    command-line switch.  This is done by diverting to the appropriate
    file <tt>&lt;avr/io</tt><em>XXXX</em><tt>.h&gt;</tt> which should
    never be included directly.  Some register names common to all
    AVR devices are defined directly within <tt>&lt;avr/common.h&gt;</tt>,
    which is included in <tt>&lt;avr/io.h&gt;</tt>,
    but most of the details come from the respective include file.

    Note that this file always includes the following files:
    \code 
    #include <avr/sfr_defs.h>
    #include <avr/portpins.h>
    #include <avr/common.h>
    #include <avr/version.h>
    \endcode
    See \ref avr_sfr for more details about that header file.

    Included are definitions of the IO register set and their
    respective bit values as specified in the Atmel documentation.
    Note that inconsistencies in naming conventions,
    so even identical functions sometimes get different names on
    different devices.

    Also included are the specific names useable for interrupt
    function definitions as documented
    \ref avr_signames "here".

    Finally, the following macros are defined:

    - \b RAMEND
    <br>
    The last on-chip RAM address.
    <br>
    - \b XRAMEND
    <br>
    The last possible RAM location that is addressable. This is equal to 
    RAMEND for devices that do not allow for external RAM. For devices 
    that allow external RAM, this will be larger than RAMEND.
    <br>
    - \b E2END
    <br>
    The last EEPROM address.
    <br>
    - \b FLASHEND
    <br>
    The last byte address in the Flash program space.
    <br>
    - \b SPM_PAGESIZE
    <br>
    For devices with bootloader support, the flash pagesize
    (in bytes) to be used for the \c SPM instruction. 
    - \b E2PAGESIZE
    <br>
    The size of the EEPROM page.
    
*/

#ifndef _AVR_IO_H_
#define _AVR_IO_H_

#include <avr/sfr_defs.h>

#if defined (__AVR_AT94K__)
#  borrowed_code <avr/ioat94k.h>
#elif defined (__AVR_AT43USB320__)
#  borrowed_code <avr/io43u32x.h>
#elif defined (__AVR_AT43USB355__)
#  borrowed_code <avr/io43u35x.h>
#elif defined (__AVR_AT76C711__)
#  borrowed_code <avr/io76c711.h>
#elif defined (__AVR_AT86RF401__)
#  borrowed_code <avr/io86r401.h>
#elif defined (__AVR_AT90PWM1__)
#  borrowed_code <avr/io90pwm1.h>
#elif defined (__AVR_AT90PWM2__)
#  borrowed_code <avr/io90pwmx.h>
#elif defined (__AVR_AT90PWM2B__)
#  borrowed_code <avr/io90pwm2b.h>
#elif defined (__AVR_AT90PWM3__)
#  borrowed_code <avr/io90pwmx.h>
#elif defined (__AVR_AT90PWM3B__)
#  borrowed_code <avr/io90pwm3b.h>
#elif defined (__AVR_AT90PWM216__)
#  borrowed_code <avr/io90pwm216.h>
#elif defined (__AVR_AT90PWM316__)
#  borrowed_code <avr/io90pwm316.h>
#elif defined (__AVR_AT90PWM161__)
#  borrowed_code <avr/io90pwm161.h>
#elif defined (__AVR_AT90PWM81__)
#  borrowed_code <avr/io90pwm81.h>
#elif defined (__AVR_ATmega8U2__)
#  borrowed_code <avr/iom8u2.h>
#elif defined (__AVR_ATmega16M1__)
#  borrowed_code <avr/iom16m1.h>
#elif defined (__AVR_ATmega16U2__)
#  borrowed_code <avr/iom16u2.h>
#elif defined (__AVR_ATmega16U4__)
#  borrowed_code <avr/iom16u4.h>
#elif defined (__AVR_ATmega32C1__)
#  borrowed_code <avr/iom32c1.h>
#elif defined (__AVR_ATmega32M1__)
#  borrowed_code <avr/iom32m1.h>
#elif defined (__AVR_ATmega32U2__)
#  borrowed_code <avr/iom32u2.h>
#elif defined (__AVR_ATmega32U4__)
#  borrowed_code <avr/iom32u4.h>
#elif defined (__AVR_ATmega32U6__)
#  borrowed_code <avr/iom32u6.h>
#elif defined (__AVR_ATmega64C1__)
#  borrowed_code <avr/iom64c1.h>
#elif defined (__AVR_ATmega64M1__)
#  borrowed_code <avr/iom64m1.h>
#elif defined (__AVR_ATmega128__)
#  borrowed_code <avr/iom128.h>
#elif defined (__AVR_ATmega128A__)
#  borrowed_code <avr/iom128a.h>
#elif defined (__AVR_ATmega1280__)
#  borrowed_code <avr/iom1280.h>
#elif defined (__AVR_ATmega1281__)
#  borrowed_code <avr/iom1281.h>
#elif defined (__AVR_ATmega1284__)
#  borrowed_code <avr/iom1284.h>
#elif defined (__AVR_ATmega1284P__)
#  borrowed_code <avr/iom1284p.h>
#elif defined (__AVR_ATmega128RFA1__)
#  borrowed_code <avr/iom128rfa1.h>
#elif defined (__AVR_ATmega1284RFR2__)
#  borrowed_code <avr/iom1284rfr2.h>
#elif defined (__AVR_ATmega128RFR2__)
#  borrowed_code <avr/iom128rfr2.h>
#elif defined (__AVR_ATmega2564RFR2__)
#  borrowed_code <avr/iom2564rfr2.h>
#elif defined (__AVR_ATmega256RFR2__)
#  borrowed_code <avr/iom256rfr2.h>
#elif defined (__AVR_ATmega2560__)
#  borrowed_code <avr/iom2560.h>
#elif defined (__AVR_ATmega2561__)
#  borrowed_code <avr/iom2561.h>
#elif defined (__AVR_AT90CAN32__)
#  borrowed_code <avr/iocan32.h>
#elif defined (__AVR_AT90CAN64__)
#  borrowed_code <avr/iocan64.h>
#elif defined (__AVR_AT90CAN128__)
#  borrowed_code <avr/iocan128.h>
#elif defined (__AVR_AT90USB82__)
#  borrowed_code <avr/iousb82.h>
#elif defined (__AVR_AT90USB162__)
#  borrowed_code <avr/iousb162.h>
#elif defined (__AVR_AT90USB646__)
#  borrowed_code <avr/iousb646.h>
#elif defined (__AVR_AT90USB647__)
#  borrowed_code <avr/iousb647.h>
#elif defined (__AVR_AT90USB1286__)
#  borrowed_code <avr/iousb1286.h>
#elif defined (__AVR_AT90USB1287__)
#  borrowed_code <avr/iousb1287.h>
#elif defined (__AVR_ATmega644RFR2__)
#  borrowed_code <avr/iom644rfr2.h>
#elif defined (__AVR_ATmega64RFR2__)
#  borrowed_code <avr/iom64rfr2.h>
#elif defined (__AVR_ATmega64__)
#  borrowed_code <avr/iom64.h>
#elif defined (__AVR_ATmega64A__)
#  borrowed_code <avr/iom64a.h>
#elif defined (__AVR_ATmega640__)
#  borrowed_code <avr/iom640.h>
#elif defined (__AVR_ATmega644__)
#  borrowed_code <avr/iom644.h>
#elif defined (__AVR_ATmega644A__)
#  borrowed_code <avr/iom644a.h>
#elif defined (__AVR_ATmega644P__)
#  borrowed_code <avr/iom644p.h>
#elif defined (__AVR_ATmega644PA__)
#  borrowed_code <avr/iom644pa.h>
#elif defined (__AVR_ATmega645__)
#  borrowed_code <avr/iom645.h>
#elif (defined __AVR_ATmega645A__)
#borrowed_code <avr/iom645a.h>
#elif (defined __AVR_ATmega645P__)
#borrowed_code <avr/iom645p.h>
#elif defined (__AVR_ATmega6450__)
#  borrowed_code <avr/iom6450.h>
#elif (defined __AVR_ATmega6450A__)
#borrowed_code <avr/iom6450a.h>
#elif (defined __AVR_ATmega6450P__)
#borrowed_code <avr/iom6450p.h>
#elif defined (__AVR_ATmega649__)
#  borrowed_code <avr/iom649.h>
#elif (defined __AVR_ATmega649A__)
#borrowed_code <avr/iom649a.h>
#elif defined (__AVR_ATmega6490__)
#  borrowed_code <avr/iom6490.h>
#elif (defined __AVR_ATmega6490A__)
#borrowed_code <avr/iom6490a.h>
#elif (defined __AVR_ATmega6490P__)
#borrowed_code <avr/iom6490p.h>
#elif defined (__AVR_ATmega649P__)
#  borrowed_code <avr/iom649p.h>
#elif defined (__AVR_ATmega64HVE__)
#  borrowed_code <avr/iom64hve.h>
#elif defined (__AVR_ATmega64HVE2__)
#  borrowed_code <avr/iom64hve2.h>
#elif defined (__AVR_ATmega103__)
#  borrowed_code <avr/iom103.h>
#elif defined (__AVR_ATmega32__)
#  borrowed_code <avr/iom32.h>
#elif defined (__AVR_ATmega32A__)
#  borrowed_code <avr/iom32a.h>
#elif defined (__AVR_ATmega323__)
#  borrowed_code <avr/iom323.h>
#elif defined (__AVR_ATmega324P__)
#  borrowed_code <avr/iom324p.h>
#elif (defined __AVR_ATmega324A__)
#borrowed_code <avr/iom324a.h>
#elif defined (__AVR_ATmega324PA__)
#  borrowed_code <avr/iom324pa.h>
#elif defined (__AVR_ATmega325__)
#  borrowed_code <avr/iom325.h>
#elif (defined __AVR_ATmega325A__)
#borrowed_code <avr/iom325a.h>
#elif defined (__AVR_ATmega325P__)
#  borrowed_code <avr/iom325p.h>
#elif defined (__AVR_ATmega325PA__)
#  borrowed_code <avr/iom325pa.h>
#elif defined (__AVR_ATmega3250__) 
#  borrowed_code <avr/iom3250.h>
#elif (defined __AVR_ATmega3250A__)
#borrowed_code <avr/iom3250a.h>
#elif defined (__AVR_ATmega3250P__)
#  borrowed_code <avr/iom3250p.h>
#elif defined (__AVR_ATmega3250PA__)
#  borrowed_code <avr/iom3250pa.h>
#elif defined (__AVR_ATmega328P__)
#  borrowed_code <avr/iom328p.h>
#elif (defined __AVR_ATmega328__)
#borrowed_code <avr/iom328.h>
#elif defined (__AVR_ATmega329__)
#  borrowed_code <avr/iom329.h>
#elif (defined __AVR_ATmega329A__)
#borrowed_code <avr/iom329a.h>
#elif defined (__AVR_ATmega329P__) 
#  borrowed_code <avr/iom329p.h>
#elif (defined __AVR_ATmega329PA__)
#borrowed_code <avr/iom329pa.h>
#elif (defined __AVR_ATmega3290PA__)
#borrowed_code <avr/iom3290pa.h>
#elif defined (__AVR_ATmega3290__)
#  borrowed_code <avr/iom3290.h>
#elif (defined __AVR_ATmega3290A__)
#borrowed_code <avr/iom3290a.h>
#elif defined (__AVR_ATmega3290P__)
#  borrowed_code <avr/iom3290.h>
#elif defined (__AVR_ATmega32HVB__)
#  borrowed_code <avr/iom32hvb.h>
#elif defined (__AVR_ATmega32HVBREVB__)
#  borrowed_code <avr/iom32hvbrevb.h>
#elif defined (__AVR_ATmega406__)
#  borrowed_code <avr/iom406.h>
#elif defined (__AVR_ATmega16__)
#  borrowed_code <avr/iom16.h>
#elif defined (__AVR_ATmega16A__)
#  borrowed_code <avr/iom16a.h>
#elif defined (__AVR_ATmega161__)
#  borrowed_code <avr/iom161.h>
#elif defined (__AVR_ATmega162__)
#  borrowed_code <avr/iom162.h>
#elif defined (__AVR_ATmega163__)
#  borrowed_code <avr/iom163.h>
#elif defined (__AVR_ATmega164P__)
#  borrowed_code <avr/iom164p.h>
#elif (defined __AVR_ATmega164A__)
#borrowed_code <avr/iom164a.h>
#elif defined (__AVR_ATmega164PA__)
#  borrowed_code <avr/iom164pa.h>
#elif defined (__AVR_ATmega165__)
#  borrowed_code <avr/iom165.h>
#elif defined (__AVR_ATmega165A__)
#  borrowed_code <avr/iom165a.h>
#elif defined (__AVR_ATmega165P__)
#  borrowed_code <avr/iom165p.h>
#elif defined (__AVR_ATmega165PA__)
#  borrowed_code <avr/iom165pa.h>
#elif defined (__AVR_ATmega168__)
#  borrowed_code <avr/iom168.h>
#elif defined (__AVR_ATmega168A__)
#  borrowed_code <avr/iom168a.h>
#elif defined (__AVR_ATmega168P__)
#  borrowed_code <avr/iom168p.h>
#elif defined (__AVR_ATmega168PA__)
#  borrowed_code <avr/iom168pa.h>
#elif defined (__AVR_ATmega168PB__)
#  borrowed_code <avr/iom168pb.h>
#elif defined (__AVR_ATmega169__)
#  borrowed_code <avr/iom169.h>
#elif (defined __AVR_ATmega169A__)
#borrowed_code <avr/iom169a.h>
#elif defined (__AVR_ATmega169P__)
#  borrowed_code <avr/iom169p.h>
#elif defined (__AVR_ATmega169PA__)
#  borrowed_code <avr/iom169pa.h>
#elif defined (__AVR_ATmega8HVA__)
#  borrowed_code <avr/iom8hva.h>
#elif defined (__AVR_ATmega16HVA__)
#  borrowed_code <avr/iom16hva.h>
#elif defined (__AVR_ATmega16HVA2__)
#  borrowed_code <avr/iom16hva2.h>
#elif defined (__AVR_ATmega16HVB__)
#  borrowed_code <avr/iom16hvb.h>
#elif defined (__AVR_ATmega16HVBREVB__)
#  borrowed_code <avr/iom16hvbrevb.h>
#elif defined (__AVR_ATmega8__)
#  borrowed_code <avr/iom8.h>
#elif defined (__AVR_ATmega8A__)
#  borrowed_code <avr/iom8a.h>
#elif defined (__AVR_ATmega48__)
#  borrowed_code <avr/iom48.h>
#elif defined (__AVR_ATmega48A__)
#  borrowed_code <avr/iom48a.h>
#elif defined (__AVR_ATmega48PA__)
#  borrowed_code <avr/iom48pa.h>
#elif defined (__AVR_ATmega48PB__)
#  borrowed_code <avr/iom48pb.h>
#elif defined (__AVR_ATmega48P__)
#  borrowed_code <avr/iom48p.h>
#elif defined (__AVR_ATmega88__)
#  borrowed_code <avr/iom88.h>
#elif defined (__AVR_ATmega88A__)
#  borrowed_code <avr/iom88a.h>
#elif defined (__AVR_ATmega88P__)
#  borrowed_code <avr/iom88p.h>
#elif defined (__AVR_ATmega88PA__)
#  borrowed_code <avr/iom88pa.h>
#elif defined (__AVR_ATmega88PB__)
#  borrowed_code <avr/iom88pb.h>
#elif defined (__AVR_ATmega8515__)
#  borrowed_code <avr/iom8515.h>
#elif defined (__AVR_ATmega8535__)
#  borrowed_code <avr/iom8535.h>
#elif defined (__AVR_AT90S8535__)
#  borrowed_code <avr/io8535.h>
#elif defined (__AVR_AT90C8534__)
#  borrowed_code <avr/io8534.h>
#elif defined (__AVR_AT90S8515__)
#  borrowed_code <avr/io8515.h>
#elif defined (__AVR_AT90S4434__)
#  borrowed_code <avr/io4434.h>
#elif defined (__AVR_AT90S4433__)
#  borrowed_code <avr/io4433.h>
#elif defined (__AVR_AT90S4414__)
#  borrowed_code <avr/io4414.h>
#elif defined (__AVR_ATtiny22__)
#  borrowed_code <avr/iotn22.h>
#elif defined (__AVR_ATtiny26__)
#  borrowed_code <avr/iotn26.h>
#elif defined (__AVR_AT90S2343__)
#  borrowed_code <avr/io2343.h>
#elif defined (__AVR_AT90S2333__)
#  borrowed_code <avr/io2333.h>
#elif defined (__AVR_AT90S2323__)
#  borrowed_code <avr/io2323.h>
#elif defined (__AVR_AT90S2313__)
#  borrowed_code <avr/io2313.h>
#elif defined (__AVR_ATtiny4__)
#  borrowed_code <avr/iotn4.h>
#elif defined (__AVR_ATtiny5__)
#  borrowed_code <avr/iotn5.h>
#elif defined (__AVR_ATtiny9__)
#  borrowed_code <avr/iotn9.h>
#elif defined (__AVR_ATtiny10__)
#  borrowed_code <avr/iotn10.h>
#elif defined (__AVR_ATtiny20__)
#  borrowed_code <avr/iotn20.h>
#elif defined (__AVR_ATtiny40__)
#  borrowed_code <avr/iotn40.h>
#elif defined (__AVR_ATtiny2313__)
#  borrowed_code <avr/iotn2313.h>
#elif defined (__AVR_ATtiny2313A__)
#  borrowed_code <avr/iotn2313a.h>
#elif defined (__AVR_ATtiny13__)
#  borrowed_code <avr/iotn13.h>
#elif defined (__AVR_ATtiny13A__)
#  borrowed_code <avr/iotn13a.h>
#elif defined (__AVR_ATtiny25__)
#  borrowed_code <avr/iotn25.h>
#elif defined (__AVR_ATtiny4313__)
#  borrowed_code <avr/iotn4313.h>
#elif defined (__AVR_ATtiny45__)
#  borrowed_code <avr/iotn45.h>
#elif defined (__AVR_ATtiny85__)
#  borrowed_code <avr/iotn85.h>
#elif defined (__AVR_ATtiny24__)
#  borrowed_code <avr/iotn24.h>
#elif defined (__AVR_ATtiny24A__)
#  borrowed_code <avr/iotn24a.h>
#elif defined (__AVR_ATtiny44__)
#  borrowed_code <avr/iotn44.h>
#elif defined (__AVR_ATtiny44A__)
#  borrowed_code <avr/iotn44a.h>
#elif defined (__AVR_ATtiny441__)
#  borrowed_code <avr/iotn441.h>
#elif defined (__AVR_ATtiny84__)
#  borrowed_code <avr/iotn84.h>
#elif defined (__AVR_ATtiny84A__)
#  borrowed_code <avr/iotn84a.h>
#elif defined (__AVR_ATtiny841__)
#  borrowed_code <avr/iotn841.h>
#elif defined (__AVR_ATtiny261__)
#  borrowed_code <avr/iotn261.h>
#elif defined (__AVR_ATtiny261A__)
#  borrowed_code <avr/iotn261a.h>
#elif defined (__AVR_ATtiny461__)
#  borrowed_code <avr/iotn461.h>
#elif defined (__AVR_ATtiny461A__)
#  borrowed_code <avr/iotn461a.h>
#elif defined (__AVR_ATtiny861__)
#  borrowed_code <avr/iotn861.h>
#elif defined (__AVR_ATtiny861A__)
#  borrowed_code <avr/iotn861a.h>
#elif defined (__AVR_ATtiny43U__)
#  borrowed_code <avr/iotn43u.h>
#elif defined (__AVR_ATtiny48__)
#  borrowed_code <avr/iotn48.h>
#elif defined (__AVR_ATtiny88__)
#  borrowed_code <avr/iotn88.h>
#elif defined (__AVR_ATtiny828__)
#  borrowed_code <avr/iotn828.h>
#elif defined (__AVR_ATtiny87__)
#  borrowed_code <avr/iotn87.h>
#elif defined (__AVR_ATtiny167__)
#  borrowed_code <avr/iotn167.h>
#elif defined (__AVR_ATtiny1634__)
#  borrowed_code <avr/iotn1634.h>
#elif defined (__AVR_AT90SCR100__)
#  borrowed_code <avr/io90scr100.h>
#elif defined (__AVR_ATxmega8E5__)
#  borrowed_code <avr/iox8e5.h>
#elif defined (__AVR_ATxmega16A4__)
#  borrowed_code <avr/iox16a4.h>
#elif defined (__AVR_ATxmega16A4U__)
#  borrowed_code <avr/iox16a4u.h>
#elif defined (__AVR_ATxmega16C4__)
#  borrowed_code <avr/iox16c4.h>
#elif defined (__AVR_ATxmega16D4__)
#  borrowed_code <avr/iox16d4.h>
#elif defined (__AVR_ATxmega16E5__)
#  borrowed_code <avr/iox16e5.h>
#elif defined (__AVR_ATxmega32A4__)
#  borrowed_code <avr/iox32a4.h>
#elif defined (__AVR_ATxmega32A4U__)
#  borrowed_code <avr/iox32a4u.h>
#elif defined (__AVR_ATxmega32C3__)
#  borrowed_code <avr/iox32c3.h>
#elif defined (__AVR_ATxmega32C4__)
#  borrowed_code <avr/iox32c4.h>
#elif defined (__AVR_ATxmega32D3__)
#  borrowed_code <avr/iox32d3.h>
#elif defined (__AVR_ATxmega32D4__)
#  borrowed_code <avr/iox32d4.h>
#elif defined (__AVR_ATxmega32E5__)
#  borrowed_code <avr/iox32e5.h>
#elif defined (__AVR_ATxmega64A1__)
#  borrowed_code <avr/iox64a1.h>
#elif defined (__AVR_ATxmega64A1U__)
#  borrowed_code <avr/iox64a1u.h>
#elif defined (__AVR_ATxmega64A3__)
#  borrowed_code <avr/iox64a3.h>
#elif defined (__AVR_ATxmega64A3U__)
#  borrowed_code <avr/iox64a3u.h>
#elif defined (__AVR_ATxmega64A4U__)
#  borrowed_code <avr/iox64a4u.h>
#elif defined (__AVR_ATxmega64B1__)
#  borrowed_code <avr/iox64b1.h>
#elif defined (__AVR_ATxmega64B3__)
#  borrowed_code <avr/iox64b3.h>
#elif defined (__AVR_ATxmega64C3__)
#  borrowed_code <avr/iox64c3.h>
#elif defined (__AVR_ATxmega64D3__)
#  borrowed_code <avr/iox64d3.h>
#elif defined (__AVR_ATxmega64D4__)
#  borrowed_code <avr/iox64d4.h>
#elif defined (__AVR_ATxmega128A1__)
#  borrowed_code <avr/iox128a1.h>
#elif defined (__AVR_ATxmega128A1U__)
#  borrowed_code <avr/iox128a1u.h>
#elif defined (__AVR_ATxmega128A4U__)
#  borrowed_code <avr/iox128a4u.h>
#elif defined (__AVR_ATxmega128A3__)
#  borrowed_code <avr/iox128a3.h>
#elif defined (__AVR_ATxmega128A3U__)
#  borrowed_code <avr/iox128a3u.h>
#elif defined (__AVR_ATxmega128B1__)
#  borrowed_code <avr/iox128b1.h>
#elif defined (__AVR_ATxmega128B3__)
#  borrowed_code <avr/iox128b3.h>
#elif defined (__AVR_ATxmega128C3__)
#  borrowed_code <avr/iox128c3.h>
#elif defined (__AVR_ATxmega128D3__)
#  borrowed_code <avr/iox128d3.h>
#elif defined (__AVR_ATxmega128D4__)
#  borrowed_code <avr/iox128d4.h>
#elif defined (__AVR_ATxmega192A3__)
#  borrowed_code <avr/iox192a3.h>
#elif defined (__AVR_ATxmega192A3U__)
#  borrowed_code <avr/iox192a3u.h>
#elif defined (__AVR_ATxmega192C3__)
#  borrowed_code <avr/iox192c3.h>
#elif defined (__AVR_ATxmega192D3__)
#  borrowed_code <avr/iox192d3.h>
#elif defined (__AVR_ATxmega256A3__)
#  borrowed_code <avr/iox256a3.h>
#elif defined (__AVR_ATxmega256A3U__)
#  borrowed_code <avr/iox256a3u.h>
#elif defined (__AVR_ATxmega256A3B__)
#  borrowed_code <avr/iox256a3b.h>
#elif defined (__AVR_ATxmega256A3BU__)
#  borrowed_code <avr/iox256a3bu.h>
#elif defined (__AVR_ATxmega256C3__)
#  borrowed_code <avr/iox256c3.h>
#elif defined (__AVR_ATxmega256D3__)
#  borrowed_code <avr/iox256d3.h>
#elif defined (__AVR_ATxmega384C3__)
#  borrowed_code <avr/iox384c3.h>
#elif defined (__AVR_ATxmega384D3__)
#  borrowed_code <avr/iox384d3.h>
#elif defined (__AVR_ATA5702M322__)
#  borrowed_code <avr/ioa5702m322.h>
#elif defined (__AVR_ATA5782__)
#  borrowed_code <avr/ioa5782.h>
#elif defined (__AVR_ATA5790__)
#  borrowed_code <avr/ioa5790.h>
#elif defined (__AVR_ATA5790N__)
#  borrowed_code <avr/ioa5790n.h>
#elif defined (__AVR_ATA5791__)
#  borrowed_code <avr/ioa5791.h>
#elif defined (__AVR_ATA5831__)
#  borrowed_code <avr/ioa5831.h>
#elif defined (__AVR_ATA5272__)
#  borrowed_code <avr/ioa5272.h>
#elif defined (__AVR_ATA5505__)
#  borrowed_code <avr/ioa5505.h>
#elif defined (__AVR_ATA5795__)
#  borrowed_code <avr/ioa5795.h>
#elif defined (__AVR_ATA6285__)
#  borrowed_code <avr/ioa6285.h>
#elif defined (__AVR_ATA6286__)
#  borrowed_code <avr/ioa6286.h>
#elif defined (__AVR_ATA6289__)
#  borrowed_code <avr/ioa6289.h>
#elif defined (__AVR_ATA6612C__)
#  borrowed_code <avr/ioa6612c.h>
#elif defined (__AVR_ATA6613C__)
#  borrowed_code <avr/ioa6613c.h>
#elif defined (__AVR_ATA6614Q__)
#  borrowed_code <avr/ioa6614q.h>
#elif defined (__AVR_ATA6616C__)
#  borrowed_code <avr/ioa6616c.h>
#elif defined (__AVR_ATA6617C__)
#  borrowed_code <avr/ioa6617c.h>
#elif defined (__AVR_ATA664251__)
#  borrowed_code <avr/ioa664251.h>
#elif defined (__AVR_ATA8210__)
#  borrowed_code <avr/ioa8210.h>
#elif defined (__AVR_ATA8510__)
#  borrowed_code <avr/ioa8510.h>
/* avr1: the following only supported for assembler programs */
#elif defined (__AVR_ATtiny28__)
#  borrowed_code <avr/iotn28.h>
#elif defined (__AVR_AT90S1200__)
#  borrowed_code <avr/io1200.h>
#elif defined (__AVR_ATtiny15__)
#  borrowed_code <avr/iotn15.h>
#elif defined (__AVR_ATtiny12__)
#  borrowed_code <avr/iotn12.h>
#elif defined (__AVR_ATtiny11__)
#  borrowed_code <avr/iotn11.h>
#elif defined (__AVR_M3000__)
#  borrowed_code <avr/iom3000.h>
#elif defined (__AVR_ATmega4809__)
#  borrowed_code <avr/iom4809.h>
#elif defined (__AVR_ATmega4808__)
#  borrowed_code <avr/iom4808.h>
#elif defined (__AVR_ATmega328PB__)
#  borrowed_code <avr/iom328pb.h>
#elif defined (__AVR_ATmega324PB__)
#  borrowed_code <avr/iom324pb.h>
#elif defined (__AVR_ATmega3209__)
#  borrowed_code <avr/iom3209.h>
#elif defined (__AVR_ATmega3208__)
#  borrowed_code <avr/iom3208.h>
#elif defined (__AVR_DEV_LIB_NAME__)
#  define __concat__(a,b) a##b
#  define __header1__(a,b) __concat__(a,b)
#  define __AVR_DEVICE_HEADER__ <avr/__header1__(io,__AVR_DEV_LIB_NAME__).h>
#  borrowed_code __AVR_DEVICE_HEADER__
#else
#  if !defined(__COMPILING_AVR_LIBC__)
#    warning "device type not defined"
#  endif
#endif

#include <avr/portpins.h>

#include <avr/common.h>

#include <avr/version.h>

#if __AVR_ARCH__ >= 100
#  borrowed_code <avr/xmega.h>
#endif

/* Include fuse.h after individual IO header files. */
#include <avr/fuse.h>

/* Include lock.h after individual IO header files. */
#include <avr/lock.h>

#endif /* _AVR_IO_H_ */

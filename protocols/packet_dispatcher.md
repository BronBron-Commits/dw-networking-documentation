Packet Dispatcher: switchD\_1029eeac



Overview

The Delta Worlds client uses a jump-table–based dispatcher to route

incoming packets based on an opcode value stored in EAX.



Dispatcher address:

0x1029eeac





Core Dispatch Instruction



1029eeac  JMP dword ptr \[EAX\*4 + switchdataD\_1029ef28]



\- EAX = packet opcode

\- No bounds checking is performed

\- Invalid values fall through to the default handler





Default / Error Cases



caseD\_ffffffff:

&nbsp;   OR  EAX, 0xFFFFFFFF

&nbsp;   RET 4



caseD\_0:

&nbsp;   MOV EAX, 3

&nbsp;   RET 4



These cases appear to signal protocol errors or ignored packets.





Jump Table Location



switchdataD\_1029ef28



Each entry is a 32-bit pointer to a packet handler.





Observed Opcode Coverage



\- 0x01 – 0x31

\- 0x32 – 0x35

\- 0x36 – 0x3F

\- 0x40 – 0x7F

\- 0x80 – 0xBB

\- 0xBC

\- 0xFFFFFFFF (default)



Conclusions



\- Opcode is a small integer (likely uint8)

\- Single-byte primary opcode

\- Classic ActiveWorlds-style protocol dispatcher

\- All packet handling funnels through this switch




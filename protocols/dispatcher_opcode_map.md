\# Opcode Dispatcher: switchD\_1029eeac



Location:

0x1029eeac



Purpose:

Maps raw packet opcode byte to internal handler index.



Mechanism:

Computed jump table:

JMP \[EAX \* 4 + switchdataD\_1029ef28]



This function does NOT parse packets.

It normalizes opcode values into a small contiguous range

used by downstream logic.



---



\## Direct Mappings (Observed)



Opcode (hex) -> Internal Code (EAX return)



0xFFFFFFFF -> 0

0x4C       -> 1

0x32       -> 2

0x44       -> 4

0x33       -> 5

0x34       -> 6

0x3C       -> 7

0x4E       -> 8

0x62       -> 9

0x35       -> 10

0xBC       -> 11

(default)  -> -1



---



\## Example: caseD\_32



Assembly:

MOV EAX, 0x2

RET 4



Meaning:

Opcode 0x32 is normalized to internal handler ID 2



---



\## Notes



\- This dispatcher is a pure lookup table

\- Actual packet handling occurs AFTER this mapping

\- Internal handler IDs are reused across many opcodes

\- This explains why many packet types share logic paths



---



Next Step:

Locate functions that consume the returned EAX value.

Search for comparisons against small integers (0–12).




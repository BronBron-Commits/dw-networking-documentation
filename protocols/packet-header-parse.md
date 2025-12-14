\# Packet Header Parsing (FUN\_102a14b0)



\## Role



This function validates and normalizes the \*\*network packet header\*\* after bytes are received from the socket.

It performs byte-order conversion (`ntohs`) and enforces structural constraints before a packet is accepted.



This is the \*\*earliest confirmed protocol-boundary function\*\* in the client.



---



\## Decompiled Function



```c

void FUN\_102a14b0(uint64\_t \*buf, uint bufLen, uint \*outPacketLen)

{

&nbsp;   uint16\_t tmp;

&nbsp;   int i;

&nbsp;   uint64\_t header;

&nbsp;   uint16\_t field5;

&nbsp;   uint cookie;



&nbsp;   cookie = DAT\_1055f600 ^ (uint)\&header;



&nbsp;   // Minimum header size check

&nbsp;   if (bufLen < 10) {

&nbsp;       return;

&nbsp;   }



&nbsp;   header = \*buf;

&nbsp;   field5 = \*(uint16\_t \*)(buf + 1);



&nbsp;   // Convert first 5 uint16 fields from network byte order

&nbsp;   for (i = 0; i < 5; i++) {

&nbsp;       tmp = ntohs(\*(uint16\_t \*)((uint8\_t \*)\&header + i \* 2));

&nbsp;       \*(uint16\_t \*)((uint8\_t \*)\&header + i \* 2) = tmp;

&nbsp;   }



&nbsp;   // header\[0]: packet length

&nbsp;   if ((uint16\_t)header <= bufLen) {



&nbsp;       // Structural validation

&nbsp;       if (

&nbsp;           (

&nbsp;               (header >> 48 < 4) ||                // field\[3] < 4

&nbsp;               ((header >> 32 \& 0xFFFF) == 0x65)    // field\[2] == 0x65

&nbsp;           ) \&\&

&nbsp;           (field5 < 0x401) \&\&

&nbsp;           (

&nbsp;               (header >> 48 != 0) ||

&nbsp;               ((header >> 32 \& 0xFFFF) == 0x65)

&nbsp;           )

&nbsp;       ) {

&nbsp;           \*outPacketLen = (uint16\_t)header;



&nbsp;           // Special-case rejection

&nbsp;           if (((header >> 32 \& 0xFFFF) == 0xFFFF) \&\& (header >> 48 != 0)) {

&nbsp;               return;

&nbsp;           }



&nbsp;           return;

&nbsp;       }

&nbsp;   }

}

Header Layout (Inferred)



The function treats the first 10 bytes as five 16-bit fields:



Offset	Size	Meaning (Inferred)

0x00	u16	Packet length

0x02	u16	Message / opcode

0x04	u16	Subtype / flags

0x06	u16	Channel / class

0x08	u16	Version / bounds-checked field



All fields arrive in network byte order.



Key Behaviors



Rejects packets smaller than 10 bytes



Converts header fields using ntohs



Validates declared packet length against received buffer



Applies protocol-specific constraints:



Certain opcodes allowed only with specific field combinations



Upper bound check on final header field (< 0x401)



Outputs validated packet length via outPacketLen



What This Function Does NOT Do



❌ Does not parse packet payload



❌ Does not dispatch opcodes



❌ Does not allocate memory



❌ Does not modify socket state



This function only validates and sizes a packet header.








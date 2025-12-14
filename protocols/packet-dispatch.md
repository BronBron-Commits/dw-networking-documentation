\# Packet Dispatch and Processing (FUN\_1029e4d0)



\## Role



This function is the \*\*core inbound packet dispatcher\*\*.  

It is invoked after socket receive and header validation and is responsible for:



\- Handling partial packets

\- Parsing validated packet headers

\- Dispatching packets based on type

\- Managing receive buffer state

\- Invoking higher-level packet handlers



This is the \*\*first function that consumes validated packets\*\*.



---



\## Decompiled Function



```c

void \_\_fastcall FUN\_1029e4d0(int \*ctx)

{

&nbsp;   char result;

&nbsp;   int rc;

&nbsp;   uint packetLen;

&nbsp;   CAWPacket packet;



&nbsp;   // Guard: prevent re-entrancy

&nbsp;   if (\*(char \*)((int)ctx + 0xad1) \&\& (char)ctx\[0x2b4]) {

&nbsp;       result = FUN\_1029e3a0();

&nbsp;       if (result) return;

&nbsp;       \*(char \*)(ctx + 1) = 1;

&nbsp;       \*(char \*)((int)ctx + 0xad1) = 0;

&nbsp;       return;

&nbsp;   }



&nbsp;   // Initialize packet object

&nbsp;   packet.vftable = CAWPacket::vftable;

&nbsp;   packet.data = NULL;

&nbsp;   packet.len = 0;

&nbsp;   packet.flags = 0;



&nbsp;   FUN\_102a13d0();           // stack cookie / guard

&nbsp;   \*(char \*)(ctx + 0x2b4) = 0;



&nbsp;   // Handle leftover buffered data

&nbsp;   if ((char)ctx\[0x268]) {

&nbsp;       int offset = ctx\[0x2b3];

&nbsp;       if (offset < ctx\[0x8d]) {

&nbsp;           FUN\_102a1e30(ctx\[0x8c] + offset, ctx\[0x8d] - offset);

&nbsp;           ctx\[0x2b3] = ctx\[0x8d];

&nbsp;       }

&nbsp;   }



&nbsp;   // Validate header

&nbsp;   rc = FUN\_102a14b0(ctx\[0x8c], ctx\[0x8d], \&packetLen);



&nbsp;   if (rc == 3) {

&nbsp;       \*(char \*)((int)ctx + 0xad1) = 0;



&nbsp;       // Parse extended header

&nbsp;       rc = FUN\_102a15d0(ctx\[0x8c], ctx\[0x8d], \&packetLen);

&nbsp;       if (rc == 0) {

&nbsp;           \*(uint16\_t \*)(ctx + 0x2b2) = packet.subtype;

&nbsp;           \*(uint16\_t \*)((int)ctx + 0xaca) = packet.opcode;



&nbsp;           FUN\_1029e2f0(packetLen);



&nbsp;           if (ctx\[0x8d] != 0)

&nbsp;               \*(char \*)(ctx + 0x2b4) = 1;



&nbsp;           // Dispatch packet

&nbsp;           (\*\*(code \*\*)(\*ctx + 0x38))(\&packet);

&nbsp;       } else if (rc != 2) {

&nbsp;           \*(char \*)(ctx + 1) = 1;

&nbsp;       }

&nbsp;   }

&nbsp;   else if (rc == 4) {

&nbsp;       ctx\[0x2b5] = packetLen;

&nbsp;       ctx\[0x2b6] = 0xffff;



&nbsp;       if (packetLen > 9 \&\&

&nbsp;           FUN\_102a1e90(ctx\[0x8c] + 10, packetLen - 10) == 0) {



&nbsp;           ctx\[0x2b8] = ctx\[0x2b7];

&nbsp;           \*(uint16\_t \*)(ctx + 0x2b4) = 0x101;



&nbsp;           result = FUN\_1029e3a0();

&nbsp;           if (!result)

&nbsp;               \*(char \*)((int)ctx + 0xad1) = 0;

&nbsp;       }

&nbsp;       \*(char \*)(ctx + 1) = 1;

&nbsp;   }



&nbsp;   // Cleanup

&nbsp;   packet.vftable = CAWPacket::vftable;

&nbsp;   FUN\_102a13d0();

&nbsp;   if (packet.data)

&nbsp;       free(packet.data);

}

Observed Behaviors



Calls FUN\_102a14b0 for initial header validation



Calls FUN\_102a15d0 for extended header parsing



Handles fragmented packets



Maintains receive buffer offsets



Dispatches packets via:



vtable + 0x38





Uses CAWPacket abstraction for decoded packets



recv()

&nbsp; ↓

FUN\_102a14b0  (basic header)

&nbsp; ↓

FUN\_102a15d0  (extended header)

&nbsp; ↓

FUN\_1029e4d0  (dispatcher)

&nbsp; ↓

handler(vtable + 0x38)



What This Function Does NOT Do



❌ Does not decode payload contents



❌ Does not interpret opcode semantics



❌ Does not modify world state directly



Payload interpretation occurs in downstream handlers.




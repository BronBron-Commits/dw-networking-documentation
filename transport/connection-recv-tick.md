\# Connection Receive Tick Layer



\## Overview



Above the low-level Winsock recv wrapper, the DeltaWorlds client implements

a connection-level receive tick responsible for:



\- Managing connection state

\- Handling disconnect conditions

\- Accumulating received byte counts

\- Timestamping inbound activity

\- Delegating packet parsing to higher layers



This layer does \*\*not\*\* parse packets or interpret protocol semantics.



---



\## Decompiled Function



Identified in Ghidra as `FUN\_102a2bf0`:



```c

int \_\_thiscall FUN\_102a2bf0(

&nbsp;   int \*param\_1,

&nbsp;   undefined4 param\_2,

&nbsp;   undefined4 param\_3,

&nbsp;   int \*param\_4)

{

&nbsp;   int iVar1;

&nbsp;   int iVar2;



&nbsp;   \*param\_4 = 0;



&nbsp;   iVar1 = FUN\_1029a980(param\_1, param\_2, param\_3, param\_4);



&nbsp;   if (((iVar1 != 0) \&\& (iVar1 == 1)) \&\& (param\_1\[3] == 2)) {

&nbsp;       iVar1 = \*param\_1;

&nbsp;       \*param\_4 = 0;

&nbsp;       param\_1\[3] = 4;

&nbsp;       (\*\*(code \*\*)(iVar1 + 8))();

&nbsp;       return 1;

&nbsp;   }



&nbsp;   if ((char)param\_1\[1] != '\\0') {

&nbsp;       \*param\_4 = 0;

&nbsp;       return 0x2733;

&nbsp;   }



&nbsp;   iVar2 = FUN\_10433824(0);

&nbsp;   param\_1\[6] = iVar2;

&nbsp;   param\_1\[8] = param\_1\[8] + \*param\_4;



&nbsp;   return iVar1;

}




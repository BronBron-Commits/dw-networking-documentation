\# Winsock recv Wrapper



\## Overview



The DeltaWorlds native client uses raw Winsock (WS2\_32) sockets for gameplay

traffic. Sockets are configured in non-blocking mode.



All inbound data is received through a thin wrapper around `recv`.



---



\## Decompiled recv Wrapper



Identified function (Ghidra):



```c

int FUN\_1029a980(int param\_1, undefined4 param\_2, undefined4 param\_3, int \*param\_4)

{

&nbsp;   int iVar1;



&nbsp;   iVar1 = recv(\*(undefined4 \*)(param\_1 + 8), param\_2, param\_3, 0);

&nbsp;   \*param\_4 = iVar1;



&nbsp;   if (iVar1 == -1) {

&nbsp;       iVar1 = WSAGetLastError();

&nbsp;       if (iVar1 == 0x2733) {

&nbsp;           \*param\_4 = 0;

&nbsp;           return 0;

&nbsp;       }

&nbsp;       if (iVar1 == 0x2746) {

&nbsp;           \*param\_4 = 0;

&nbsp;           return 1;

&nbsp;       }

&nbsp;   }

&nbsp;   else {

&nbsp;       if (iVar1 == 0) {

&nbsp;           WSAGetLastError();

&nbsp;           return 1;

&nbsp;       }

&nbsp;       iVar1 = 0;

&nbsp;   }

&nbsp;   return iVar1;

}




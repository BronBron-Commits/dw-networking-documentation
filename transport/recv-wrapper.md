\# Winsock recv Wrapper



\## Overview



The DeltaWorlds native client uses raw Winsock (WS2\_32) sockets for gameplay

traffic. Sockets are configured in non-blocking mode.



All inbound data is received through a thin wrapper around `recv`.



---



\## Decompiled recv Wrapper



Identified function (Ghidra):



int FUN_1029a980(
    int param_1,
    char *param_2,
    int param_3,
    int *param_4)
{
    int iVar1;

    iVar1 = recv(*(SOCKET *)(param_1 + 8), param_2, param_3, 0);
    *param_4 = iVar1;

    if (iVar1 == -1) {
        iVar1 = WSAGetLastError();
        if (iVar1 == 0x2733) {
            *param_4 = 0;
            return 0;
        }
        if (iVar1 == 0x2746) {
            *param_4 = 0;
            return 1;
        }
    }
    else {
        if (iVar1 == 0) {
            WSAGetLastError();
            return 1;
        }
        iVar1 = 0;
    }
    return iVar1;
}





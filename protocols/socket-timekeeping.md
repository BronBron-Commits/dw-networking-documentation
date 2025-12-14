\# Socket Timekeeping Utility (FUN\_10433824)



\## Purpose



This function generates a \*\*Unix-style timestamp (seconds since 1970-01-01)\*\* from the Windows system clock.  

It is used by the DeltaWorlds client networking layer for \*\*connection timing, timeouts, and state tracking\*\*.



This function is \*\*not related to packet parsing or protocol decoding\*\*.



---



\## Decompiled Function



```c

void FUN\_10433824(uint32\_t \*outSeconds)

{

&nbsp;   uint32\_t result;

&nbsp;   uint64\_t seconds;

&nbsp;   FILETIME ft;



&nbsp;   GetSystemTimeAsFileTime(\&ft);



&nbsp;   // Convert Windows FILETIME (100ns since 1601) to Unix epoch seconds

&nbsp;   seconds = (

&nbsp;       ((uint64\_t)ft.dwHighDateTime << 32 | ft.dwLowDateTime)

&nbsp;       - 0x01B21DD213814000ULL

&nbsp;   ) / 10000000ULL;



&nbsp;   // Clamp to signed 32-bit range

&nbsp;   if (seconds > 0x7FFFD27F)

&nbsp;       result = 0xFFFFFFFF;

&nbsp;   else

&nbsp;       result = (uint32\_t)seconds;



&nbsp;   if (outSeconds != NULL)

&nbsp;       \*outSeconds = result;

}




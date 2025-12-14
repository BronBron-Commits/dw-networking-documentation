\# Network Pump and Select Loop



\## Overview



The DeltaWorlds native client uses a select()-driven network pump to manage

connection state and inbound data.



This layer is responsible for:

\- select()-based readiness polling

\- connection state transitions

\- invoking recv ticks

\- accumulating receive buffers

\- delegating packet parsing to callbacks



---



\## Decompiled Function



Identified in Ghidra as `FUN\_102a2ce0`.



This function:

\- Builds fd\_sets from connection state

\- Calls select()

\- Handles non-blocking connect completion

\- Invokes the connection receive tick

\- Accumulates data into a large receive buffer

\- Triggers packet parsing via a virtual callback



---



\## Receive Buffer Management



The connection maintains a large receive buffer:



\- Buffer size: `0x20000` bytes (128 KB)

\- Base pointer: `param\_1\[0x8c]`

\- Current offset: `param\_1\[0x8d]`



Incoming data is appended:



recvBuffer\[rxOffset ... rxOffset + bytesRead]



Packet parsing is deferred to a higher-level callback.



---



\## Connection States



Observed connection states:



| Value | Meaning |

|------:|--------|

| 1 | Connecting |

| 2 | Connected |

| 3 | Closing |

| 4 | Disconnected |



---



\## Position in Receive Chain



recv → recv wrapper → recv tick → network pump → packet framing


Packet framing and opcode dispatch occur \*\*above\*\* this layer.





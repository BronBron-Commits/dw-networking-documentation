\# Initial Network Observations



\## Session Overview

\- Date:

\- OS: Windows

\- Capture Tool: Wireshark + Npcap

\- Client: DeltaWorlds (regular client)



\## Transport Summary



\### Classic SDK Traffic

\- Protocol: TCP

\- Port: 6671

\- Encryption: None observed

\- Direction: Client ↔ Remote Server

\- Notes:

&nbsp; - Matches Classic SDK behavior

&nbsp; - Used for login, chat, presence



\### Modern Client Traffic

\- Protocol: TCP

\- Port: 443

\- Encryption: TLSv1.2

\- Direction: Client ↔ Remote Servers

\- Notes:

&nbsp; - Primary data channel

&nbsp; - Likely contains world and object data

&nbsp; - Payload not readable without decryption



\### UDP Traffic

\- Observed but not primary

\- Likely auxiliary services



\## Conclusions

\- Object data is not available via Classic SDK

\- Object data is transmitted over encrypted TLS channels

\- Any object mirroring must observe or hook the modern client




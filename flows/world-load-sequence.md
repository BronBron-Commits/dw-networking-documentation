\# World Load Sequence (Observed)



This document describes the high-level packet flow during

login and world entry.



\## Sequence (Initial)



Client → Server: Login request  

Server → Client: Login response  

Client → Server: Enter world  

Server → Client: World metadata  

Server → Client: Object stream begin (observed, not decoded)



\## Notes

Packet contents not yet decoded.

Order is based on timing observation.




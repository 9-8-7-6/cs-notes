# WebRTC(Web Real Time Communication)

## Overview
* P2P with **standardize API** exchange media(vedio and audio) in efficient and low latency way

### Connection Process
1. **Discovery**  
   - A finds out all possible ways the public can connect to it.  
   - B does the same.  

2. **Signaling**  
   - A and B exchange connection/session information via an external signaling channel (not defined by WebRTC).  
   - Examples: WhatsApp, QR code, Tweet, WebSockets, HTTP fetch, etc.

3. **Establishing Connection**  
   - A connects to B via the **most optimal path** (using ICE to select the best candidate: direct, STUN, or TURN).  

4. **Capability Exchange**  
   - Both peers exchange supported **media formats** and **security parameters** to ensure compatibility and end-to-end encryption.  

## Summary
- WebRTC focuses on **real-time, secure, peer-to-peer communication**.
- The signaling mechanism is **application-defined**, not part of WebRTC itself.
- Once established, the connection is **direct and encrypted**, **minimizing latency**.
- Supports not only **audio/video streaming** but also **arbitrary data transfer** through DataChannels.  

---

*Notes taken from [WebRTC Crash Course by Hussein Nasser](https://youtu.be/FExZvpVvYxA), for educational purposes only.*

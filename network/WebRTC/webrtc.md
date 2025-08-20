# WebRTC(Web Real Time Communication)

## Overview
* P2P with **standardized API** exchange media(video and audio) in efficient and low latency way

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

## Concept
* Network Address Translation(NAT)
   * If target is not under same subnet, can't connect directly
   * Gateway create a **NAT table** ![](https://d2cest1yk6hx2d.cloudfront.net/uninets-001/store/3057/article%20images/network-address-translation-table.jpg)
   * NAT Translations Method
      * One to One NAT(Static NAT)
         * Port on the router always maps to internal IP(fixed mapping)
      * Address restricted NAT
         * Allowed to receive only if the internal host has sent first(matching IP only)
      * Port restricted NAT
         * Allowed to receive only if the internal host has sent first (matching IP + Port)
      * Symmetric NAT
         * Allowed to receive only if the full 4-tuple (Internal IP, Internal Port → Target IP, Target Port) matches
         * Mapping is unique per destination, cannot be reused for different targets
* STUN
   * Session Traversal Utilities for NAT(STUN)
   * Get real **public IP** and **Port**
   * Both client know public after STUN, then initiate the connection
   * **Symmetric NAT cannot use STUN** to connect because the pair is only for one use
* TURN
   * It’s a proxy server that relays packets
   * In the case **Symmetric NAT we use TURN**
* ICE(Interactive Connectivity Establishment)
   * Collect all available ways(ice candidates), and choose the **best communication**
   * Integrate **STUN + TURN + candidates**
   * All collected addresses are then sent to peer via **SDP**
* SDP(Session Description Protocol)
   * A **format** that describes candidates, networking, options...and more info
* Signaling the SDP
   * Send the SDP to the other party we want to communicate
   * The way to signaling could be HTTP request, WebSockets... and more, thE method doesn’t matter

## Connection Flow
1. Initiation
   * A wants to connect to B

2. Create Offer
   * A creates an offer(basically the SDP)
   * Gathers all ICE candidates (possible network paths)
   * Generates an SDP

3. Send Offer
   * A sends the offer to B
   * This requires a signaling channel (e.g., WhatsApp, WebSocket, HTTP, etc.)

4. Create Answer
   * B receives A’s offer and sets it locally
   * B creates an answer

5. Send Answer
   * B sends the answer back to A through the signaling channel

6. Connection Established
   * Both peers perform ICE connectivity checks
   * The best available path is selected (direct, STUN, or TURN)
   * Peer-to-peer connection is established

## Summary
- WebRTC focuses on **real-time, secure, peer-to-peer communication**.
- The signaling mechanism is **application-defined**, not part of WebRTC itself.
- Once established, the connection is **direct and encrypted**, **minimizing latency**.
- Supports not only **audio/video streaming** but also **arbitrary data transfer** through DataChannels.  

## Resource
* Public STUN servers
   * stun.l.google.com:19302
   * stun1.l.google.com:19302
   * stun2.l.google.com:19302
   * stun3.l.google.com:19302
   * stun4.l.google.com:19302
---

*Notes taken from [WebRTC Crash Course by Hussein Nasser](https://youtu.be/FExZvpVvYxA), for educational purposes only.*

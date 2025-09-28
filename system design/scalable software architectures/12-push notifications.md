# Push Notifications

---

## Device Register

### App
1. App registers to **Push Server** to get an **ID**  
2. App sends **ID** to **App Server**  
3. App Server sends **ID + payload** to **Push Server**  
4. Push Server delivers **payload** to the App device  

### Web Browser
1. **Pull data** from servers  
2. Use **WebSocket** connection  
3. Use **Long-Polling** when WebSocket is not available  

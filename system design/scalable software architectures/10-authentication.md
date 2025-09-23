# Authentication

---

## Approaches

### 1. Password in Every Request
- The simplest method.  
- User includes their **username/password** with each request.  
- **Drawback**: insecure and inefficient (credentials repeatedly exposed).  

### 2. Session Key (Temporary Password)
- When the user logs in:  
  1. Backend generates a **random session key**.  
  2. Stores it in the database.  
  3. Returns it to the client.  
- Client includes the **session key** in all future requests (often in an HTTP header).  
- More secure and efficient than sending the password each time.  

---

## API Keys
- An **authentication token** issued by the server.  
- Usually associated with a user, app, or service.  
- Sent in headers (e.g., `Authorization: Bearer <API_KEY>`) to authenticate requests.  
- Often used for server-to-server communication or external integrations.  

---

## Two-Factor Authentication (2FA)

---

### Concept
- **Two-Factor Authentication (2FA)** is an additional security layer that requires **two different forms of verification** before granting access.  
- It combines something you **know**, something you **have**, or something you **are**.  

---

### Factors of Authentication
1. **Something you know**  
   - Password, PIN, security questions.  
2. **Something you have**  
   - Smartphone, hardware token, smart card.  
3. **Something you are**  
   - Biometrics: fingerprint, face recognition, iris scan.  

---

### Common 2FA Methods
- **SMS / Email Code**  
  - One-time code sent to the user’s phone or email.  
- **Authenticator Apps** (TOTP, e.g., Google Authenticator, Authy)  
  - Generates time-based one-time passwords (valid for ~30s).  
- **Push Notifications**  
  - Mobile app notification to approve/deny login.  
- **Hardware Tokens**  
  - Physical devices (e.g., YubiKey, RSA SecurID).  
- **Biometrics**  
  - Fingerprint or facial recognition in combination with password.  

---

### Advantages
- Provides stronger security compared to password-only authentication.  
- Reduces risk from stolen or leaked passwords.  

### Drawbacks
- Additional step may reduce convenience.  
- Vulnerable if the second factor is compromised (e.g., SIM swap attacks for SMS).  

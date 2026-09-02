# CS50x Project - Final Project

## 📖 Distinctiveness and Complexity
**Enigma** stands out as a unique project due to its focus on privacy-first note sharing, built entirely with modern web technologies such as **Cloudflare Workers**, **GraphQL**, and **JWT-based encryption**. Unlike typical note-sharing applications, **Enigma** introduces advanced features that let users limit how many times a note can be viewed (1–5 times) and optionally protect it with a password. Users can also supply their email to receive a notification once the note self-destructs.

At the core of **Enigma** is the **zero-knowledge model**: even administrators cannot access the contents of a note, thanks to the use of encrypted JSON Web Tokens (JWTs). This ensures a high level of data confidentiality.

The application was built using Next.js for the frontend, **Cloudflare Workers** for the backend, and KV as the embedded database. All communication between client and server happens over GraphQL, using `@apollo/client` and `@apollo/server`. Tailwind CSS was used to create a clean, responsive UI.

**Key technical challenges** I overcame included:
  - Implementing JWT-based encrypted note payloads that work serverlessly.
  - Setting up a GraphQL API inside Cloudflare Workers that communicates securely with KV.
  - Handling rate-limited view counters with automatic deletion.
  - Sending transactional emails through Brevo's SMTP API via Workers.
  - Ensuring security and scalability, even without traditional backend servers.

These complexities, combined with the privacy-first approach and modern stack, make **Enigma** a distinctive, technically challenging, and relevant project.

## 🗂️ Project Structure
The project structure is based on Next.js application with Cloudflare integration:

```
  final-project/
  ├── .gitignore
  ├── eslint.config.mjs
  ├── jsconfig.json
  ├── LICENSE
  ├── next.config.mjs
  ├── open-next.config.ts
  ├── package.json
  ├── pnpm-lock.yaml
  ├── postcss.config.mjs
  ├── wrangler.jsonc                    # A file containing settings for the Cloudflare Workers service such as environment variables.
  ├── .vscode/
  │   └── settings.json
  ├── database/
  │   └── schema.sql
  ├── public/                           # Public files
  │   ├── _headers
  │   ├── _redirects
  │   └── logo.svg
  └── src/                              # Source files
      ├── lib/                          # Folder with files that add additional features to the application
      │   └── env.js                    # Script to load all environment variables in the application frontend
      └── app/                          # Main application folder
          ├── favicon.ico               # Favicon icon
          ├── layout.js                 # Layout file
          ├── not-found.js              # Not found page
          ├── page.js                   # Main page
          ├── utils.js                  # Utils frontend file
          ├── api/                      # A folder to create a backend for the application.
          │   ├── Sf19GHAdWc/
          │   │   └── route.js
          │   └── utils/
          │       ├── headers.js
          │       ├── resolvers.js
          │       ├── schema.js
          │       └── utils.js
          ├── client/
          │   ├── client.js
          │   ├── mutation.js
          │   └── query.js
          ├── components/
          │   ├── copy.jsx
          │   ├── footer.jsx
          │   ├── form.jsx
          │   ├── header.jsx
          │   ├── info.jsx
          │   ├── loader.jsx
          │   ├── message.jsx
          │   └── buttons/
          │        └── theme-button.jsx
          ├── context/
          │   └── theme-context.jsx
          ├── created/
          │   └── page.jsx
          ├── notate/
          │   └── page.jsx
          └── notate/
              └── page.jsx
```

---

## ✅ Features Overview
### 🔐 Secure Notes
  - Create encrypted notes that self-destruct after 1–5 views.
  - Deletion is enforced via Cloudflare KV and handled through GraphQL API.

### 🔑 Optional Password Protection
  - Notes can be protected with a password.
  - Decryption occurs client-side using token-embedded data.

### ✉️ Email Notifications
  - Optional email notification via Brevo.
  - Users are notified once a note is deleted after its final view.

### 🧪 Encrypted Storage with JWT
  - Each note is stored as an encrypted JWT token.
  - All sensitive data remains encrypted, including in the database.

### 🔧 GraphQL API
  - All operations (create, fetch, delete) go through a GraphQL API.
  - Built on Cloudflare Workers using @apollo/server.

### 🎨 Modern Frontend
  - Responsive UI built with Tailwind CSS and Next.js.
  - Follows modern design and UX principles.

### 🛡️ Bot Protection & Authentication
  - Cloudflare Turnstile is integrated into all forms.
  - A one-time token is used as a Bearer token in the Authentication header for secure GraphQL queries.

---

## ⚙️ Example Workflow
1. **Create a Note**
  - Visit homepage
  - Fill in note content
  - Optionally set view limit (1–5), password, or email
  - Click **Create note** button

2. **Receive a Link**
  - After creation, you’ll get a link like: `https://enigma.realnormanik.workers.dev/notate?=QwErTy`
  - Accessing a Note
  - Open the link
  - If password-protected, enter the password
  - View the note (each view reduces the counter)

3. **Note Expiry**
  - After max views, note is deleted from the KV
  - If email was provided, a notification is sent

## 🧱 Technologies Used
  - **Frontend**
    - Next.js (React-based framework)
    - Tailwind CSS
    - Apollo Client

  - **Backend**
    - Cloudflare Workers
    - GraphQL with Apollo Server
    - Cloudflare KV

  - **Other**
    - JWT (for encrypted token generation)
    - Brevo (formerly Sendinblue) for transactional email
    - Cloudflare Turnstile for Authorization user

---

## 🧩 Tech Stack & Dependencies
To run the application, make sure you have the following dependencies installed:
  ```json
  {
    "next": "16.3.4",
    "react": "^19.2.8",
    "react-dom": "^19.2.8",
    "@opennextjs/cloudflare": "^1.20.5",
    "@as-integrations/cloudflare-workers": "^1.1.1",
    "@apollo/client": "^4.2.12",
    "@apollo/server": "^5.5.1",
    "graphql": "^17.0.2"
  }
  ```

To install all dependencies, run:
  ```sh
  pnpm install
  ```

## 🚀 Running the Application
### Running the Application in Development Mode
To start the application in development mode, run the following commands:
  ```sh
  pnpm dev
  ```

### Building and Previewing the Application
To build the application in production mode, use:
  ```sh
  pnpm prod
  ```

To preview the production build locally, run:
  ```sh
  pnpm preview
  ```

### Deploying to the Server
To deploy the application, use the command:
  ```sh
  pnpm deploy
  ```

## 🕸️ GraphQL Operations
Below are the core GraphQL operations used in the Enigma app to manage encrypted notes:
  - Create note:
    ```graphql
    mutation CreateMessage($message: String!, $password: String, $email: String, $display: Int!) {
      createMessage(message: $message, password: $password, email: $email, display: $display) {
        id
      }
    }
    ```

  - Delete note:
    ```graphql
    mutation DeleteMessage($id: ID!) {
      deleteMessage(id: $id) {
        message
      }
    }
    ```

  - Verify password:
    ```graphql
    mutation VerifyPassword($id: String!, $password: String!) {
      verifyPassword(id: $id, password: $password) {
        message
      }
    }
    ```

  - Get message:
    ```graphql
    query GetMessage($id: ID!) {
      getMessage(id: $id) {
        message
      }
    }
    ```

---

## 🎥 Demo

You can view a working version of the project here:
👉 https://enigma.realnormanik.workers.dev/

Video walkthrough of the specification:
🎥 https://youtu.be/jDPhSrNDSfg

## 📜 Certification

This project was submitted as part of the CS50x including ten problem sets and one final project.
Upon successful completion, I was awarded a certificate, which is available here:

🎓 [View Certificate](https://certificates.cs50.io/5a0d47b5-d702-41c1-955d-087b0f25129c.pdf)
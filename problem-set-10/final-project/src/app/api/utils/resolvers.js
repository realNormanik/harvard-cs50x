import { signJWT, encryptMessage, decryptMessage, generateUniqueShortId, hashPassword, verifyPassword, sendDeletionEmail } from "./utils";

export const resolvers = {
  Query: {
    getMessage: async (_, { id }, context) => {
      const { myKv } = context;

      // Fetch message record from KV by its short ID
      const message = await myKv.get(id, { type: "json" });

      // If no message found, throw an error
      if (!message) {
        throw new Error("Message not found");
      };

      // Increment the number of times the message has been seen
      const newSeen = message.seen + 1;

      // If the new seen count exceeds the allowed display limit, delete the message
      if (newSeen > message.display) {
        await myKv.delete(id);

        // Delete the message and send an email if email is provided
        if (message.email) {
          await sendDeletionEmail(message.email, id);
        };

        throw new Error("Message not found");
      } else {
        // Otherwise, update the seen count in KV
        const updatedMessage = { ...message, seen: newSeen };
        await myKv.put(id, JSON.stringify(updatedMessage));
      };

      // Decrypt the message before returning it
      let decryptedMessage;
      try {
        decryptedMessage = await decryptMessage(message.message);
      } catch (error) {
        throw new Error("Failed to decrypt message");
      };

      // Prepare the data payload to include in the JWT token
      const messageData = {
        id: message.id,
        message: decryptedMessage, // Use the decrypted message
        created_at: message.created_at,
        password: message.password,
        email: message.email,
        display: message.display,
        seen: newSeen,
      };

      // Sign the message data payload into a JWT token
      const token = await signJWT(messageData);

      // Return the JWT token containing the message information
      return { message: token };
    },
  },

  Mutation: {
    createMessage: async (_, { message, password, email, display }, context) => {
      const { myKv } = context;

      // Generate current timestamp in ISO format for message creation
      const created_at = new Date().toISOString();

      // Generate a short (up to 6 chars), collision-checked ID for KV lookups
      const id = await generateUniqueShortId(myKv);

      // Use provided display count or default to 1
      const displayCount = display !== undefined ? display : 1;

      // Initialize seen count to zero for new message
      const seen = 0;

      // If a password is provided and not empty, hash it before storing
      let hashedPassword = null;
      if (password && password.trim() !== "") {
        hashedPassword = await hashPassword(password);
      };

      // Encrypt the message before saving it to KV
      let encryptedMessage;
      try {
        encryptedMessage = await encryptMessage(message);
      } catch (error) {
        throw new Error("Failed to encrypt message");
      };

      // Build the record and store it in KV under the generated short id
      const record = {
        id,
        message: encryptedMessage,
        created_at,
        password: hashedPassword,
        email,
        display: displayCount,
        seen,
      };

      await myKv.put(id, JSON.stringify(record));

      // Return the plain short ID (NOT a JWT). This is the ID the client
      // will use later (e.g. in getMessage) to look up the message in KV.
      // The JWT containing full message details is only ever issued from
      // getMessage, as a "message" field, once the record is fetched.
      return { id };
    },

    deleteMessage: async (_, { id }, context) => {
      const { myKv } = context;

      // Check if a message with the given short ID exists
      const existing = await myKv.get(id, { type: "json" });

      // If no message found, return an informative message
      if (!existing) {
        return { message: "Message not found" };
      };

      // Delete the message from KV by ID
      await myKv.delete(id);

      // Send an email about the deletion if there is an email
      if (existing.email) {
        await sendDeletionEmail(existing.email, id);
      };

      // Return success confirmation message
      return { message: "Message deleted successfully" };
    },

    verifyPassword: async (_, { id, password }, context) => {
      const { myKv } = context;

      // Retrieve the record for the message with the given short ID
      const message = await myKv.get(id, { type: "json" });

      // If message not found, indicate failure
      if (!message) {
        return { success: false, message: "Message not found" };
      };

      try {
        // Verify that the provided password matches the stored hashed password
        const isValid = await verifyPassword(password, message.password);

        // Return a message indicating whether the password is correct or invalid
        return { message: isValid ? "Password correct" : "Invalid password" };
      } catch (error) {
        // If error occurs during verification, return error message
        return { message: "Error verifying password" };
      };
    },
  },
};

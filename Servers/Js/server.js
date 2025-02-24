import express from "express";
import http from "http";
import { Server } from "socket.io";
import cors from "cors";
import mongoose from "mongoose";

mongoose.connect("mongodb://localhost:27017/babble-chat", {
})
   .then(() => console.log("MongoDB connection established"))
   .catch((error) => console.log("MongoDB connection error: ", error))

const userScheme = new mongoose.Schema({
   username: { type: String, required: true, unique: true },
   fullname: { type: String, required: true },
   password: { type: String, required: true }
}, { timestamps: true });

const User = mongoose.model("User", userScheme);

const app = express();
const server = http.createServer(app);

app.use(cors({
   origin: "http://127.0.0.1:5173",
   methods: ["GET", "POST"]
   }
));

const io = new Server(server, {
   cors : {
      origin: "http://127.0.0.1:5173",
      methods: ["GET", "POST"]
   }
});

app.use(express.json());

io.on("connection", (socket) => {
   console.log("A user connected: ", socket.id);

   socket.on("signUp", async (userData) => {
      console.log("Received sign-up data: ", userData);

      try {
         const isUserExists = await User.findOne({
            $or: [
               { username: userData.username }
            ]
         });
   
         if (isUserExists) {
            socket.emit("signUpError", { message: "User with this username already exists" });
         } else {
            const newUser = new User({
               username: userData.username,
               fullname: userData.fullname,
               password: userData.password
            });
   
            await newUser.save();
            console.log("New user created: ", newUser);
   
            socket.emit("signUpSuccess", { message: "User successfully registered!" });
         }
      } catch (error) {
         console.error("Error during sign-up:", error);
         socket.emit("signUpError", { message: "An error occured during sign-up"});
      }
   })

   server.on("disconnect", () => {
      console.log("A user disconnected: ", socket.id);
   })
});

server.listen(9000, () => {
   console.log("Server is running on http://localhost:9000");
});
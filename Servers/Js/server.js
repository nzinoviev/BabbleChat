import express from "express";
import http from "http";
import { Server } from "socket.io";
import cors from "cors";

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

   socket.on("signUp", (userData) => {
      console.log("Received sign-up data: ", userData);
   })

   server.on("disconnect", () => {
      console.log("A user disconnected: ", socket.id);
   })
});

server.listen(9000, () => {
   console.log("Server is running on http://localhost:9000");
});
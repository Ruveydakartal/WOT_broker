import express from "express";
import http from "http";
import dotenv from "dotenv";
import cors from "cors";
import { startTimer, stopTimer } from "./controllers/timer.js";
import timerSingleton from "./lib/timerSingleton.js";
import { Server } from "socket.io";
import {
  puzzleCompleteProp1,
  startChallenge1,
} from "./controllers/challenge1.js";

import {
  puzzleCompleteProp2,
  startChallenge2,
} from "./controllers/challenge2.js";

import {
  puzzleCompleteProp3,
  startChallenge3,
} from "./controllers/challenge3.js";

import {
  puzzleCompleteProp4,
  startChallenge4,
  restartArduinoProp4,
} from "./controllers/challenge4.js";

import {
  puzzleCompleteProp5,
  startChallenge5,
} from "./controllers/challenge5.js";

dotenv.config();

// Create Express app
const app = express();

// Define the HTTP server
const httpServer = http.createServer(app);

// Enable CORS
app.use(cors());

// Socket IO
const io = new Server(httpServer, {
  cors: {
    origin: "*",
    methods: ["GET", "POST"],
  },
});

// For testing purposes
io.on("connection", (socket) => {
  console.log("New user connected!");
  socket.on("disconnect", function () {
    console.log("User disconnected...");
  });
});

// Whenever we have a tick
timerSingleton.getInstance().onTick = (elapsedTime) =>
  io.emit("timerTick", elapsedTime);

// Define routes
app.get("/", (req, res) => {
  res.send("The LED API is working!");
});
app.get("/startTimer", startTimer);
app.get("/stopTimer", stopTimer);

// challenge 1
app.get("/startChallenge1", startChallenge1);
app.get("/puzzleCompleteProp1", puzzleCompleteProp1);

// // challenge 2
app.get("/startChallenge2", startChallenge2);
app.get("/puzzleCompleteProp2", puzzleCompleteProp2);

// // challenge 3
app.get("/startChallenge3", startChallenge3);
app.get("/puzzleCompleteProp3", puzzleCompleteProp3);

// challenge 4
app.get("/startChallenge4", startChallenge4);
app.get("/puzzleCompleteProp4", puzzleCompleteProp4);
app.get("/restartProp4", restartArduinoProp4);


// challenge 5
app.get("/puzzleCompleteProp5", puzzleCompleteProp5);

// Start server
const PORT = process.env.PORT || 3000;
httpServer.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}`);
});


// Export app for testing purposes
export default app;

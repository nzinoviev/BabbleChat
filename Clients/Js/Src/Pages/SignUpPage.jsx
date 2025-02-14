import React, { useEffect, useState } from "react";
import io from "socket.io-client";
import "./SignUpPage.css";

import babbleLogoPng from "../Assets/babble-logo.png";

function SignUpPage() {
   const [socket, setSocket] = useState(null);
   const [username, setUsername] = useState("");
   const [fullName, setFullName] = useState("");
   const [password, setPassword] = useState("");
   const [confirmPassword, setConfirmPassowrd] = useState("");

   useEffect(() => {
      const newSocket = io("http://localhost:9000", { autoConnect: false });
      setSocket(newSocket);
      return () => newSocket.disconnect();
   }, []);

   const sendDataViaWebSocket = () => {
      if (!socket) return;

      if (!username || !password || password !== confirmPassword) {
         alert("Please fill in all fields correctly");
         return;
      }

      socket.connect();
      const userData = { fullName, username, password };
      socket.emit("signUp", userData);
   }

   return (
      <div className="sign-up-form">
         <h1>BabbleChat</h1>

         <img src={babbleLogoPng} alt="babble-logo.png not found" className="sign-up-form__logo"/>

         <div className="sign-up-form__input-group">
            <label htmlFor="" className="sign-up-form__input-group-label">Full Name</label>
            <input type="text" className="sign-up-form__input-text" value={fullName} onChange={(e) => setFullName(e.target.value)}/>
         </div>

         <div className="sign-up-form__input-group">
            <label htmlFor="" className="sign-up-form__input-group-label">Login</label>
            <input type="text" className="sign-up-form__input-text" value={username} onChange={(e) => setUsername(e.target.value)}/>
         </div>

         <div className="sign-up-form__input-group">
            <label htmlFor="" className="sign-up-form__input-group-label">Password</label>
            <input type="text" className="sign-up-form__input-text" value={password} onChange={(e) => setPassword(e.target.value)}/>
         </div>

         <div className="sign-up-form__input-group">
            <label htmlFor="" className="sign-up-form__input-group-label">Confirm Password</label>
            <input type="text" className="sign-up-form__input-text" value={confirmPassword} onChange={(e) => setConfirmPassowrd(e.target.value)}/>
         </div>

         <button className="sign-up-form__sign-up-btn" onClick={sendDataViaWebSocket}>Sign up</button>

      </div>
   );
};

export default SignUpPage;
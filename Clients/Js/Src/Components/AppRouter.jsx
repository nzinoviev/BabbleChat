import React from "react";
import { Route, Routes } from "react-router-dom";
import SignUpPage from "../Pages/SignUpPage";

const AppRouter = () => {
   return (
      <Routes>
         <Route path="/signup" element={<SignUpPage/>} />
      </Routes>
   );
};

export default AppRouter;
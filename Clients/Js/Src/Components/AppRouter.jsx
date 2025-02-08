import React from "react";
import { Route, Routes } from "react-router-dom";
import RegistrationPage from "../Pages/RegistrationPage";

const AppRouter = () => {
   return (
      <Routes>
         <Route path="/registration" element={<RegistrationPage/>} />
      </Routes>
   );
};

export default AppRouter;
import React, { useContext } from "react";
import { Routes, Route, Navigate } from 'react-router-dom';
import { authRoutes, publicRoutes, adminRoutes } from "../Routes";
import { BOOKS_ROUTE, LOGIN_ROUTE, REGISTRATION_ROUTE } from "../utils/const";
import { Context } from "../index";
import { authorRoutes } from "../Routes"
import Auth from "../pages/Auth";

const AppRouter = () => {
    const {user} = useContext(Context);
    const isAdmin = user.checkAdmin();
    const isAuthor = user.checkAuthor();

    const token = localStorage.getItem("token");

    return (
        <Routes>
            {!token ? (
                <>
                    <Route path={LOGIN_ROUTE} element={<Auth />} />
                    <Route path={REGISTRATION_ROUTE} element={<Auth />} />
                    <Route path="*" element={<Navigate to={LOGIN_ROUTE} />} />
                </>
            ) : (
                <>
                {user.isAuth && authRoutes.map(({ path, element }) => (
                    <Route key={path} path={path} Component={element} exact />
                    ))}
                    {publicRoutes.map(({ path, element }) => (
                        <Route key={path} path={path} Component={element} exact />
                    ))}
                    {isAdmin && adminRoutes.map(({ path, element }) => (
                        <Route key={path} path={path} Component={element} exact />
                    ))}
                    {isAuthor && authorRoutes.map(({ path, element }) => (
                        <Route key={path} path={path} Component={element} exact />
                    ))}
                    <Route path="*" element={<Navigate to={BOOKS_ROUTE} />} />
                </>
            )}
        </Routes>
    );
};

export default AppRouter;
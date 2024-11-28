import React, { useContext } from "react";
import { Navbar, Nav, Container, Button } from "react-bootstrap";
import { Context } from "../index";
import { ADMIN_ROUTE, BOOKS_ROUTE, LOGIN_ROUTE, REGISTRATION_ROUTE, USER_ROUTE } from "../utils/const";
import { observer } from "mobx-react-lite";
import { logout } from "../http/userAPI";
import { Link } from 'react-router-dom';

const NavBar = observer(() => {
  const { user } = useContext(Context);
  const id = localStorage.getItem('id');
  const role = localStorage.getItem('role');
  const name = localStorage.getItem('name');

  const logOut = () => {
    user.setIsAuth(false);
    localStorage.removeItem('token');
    localStorage.removeItem('id');
    localStorage.removeItem('role');
    localStorage.removeItem('name');
  };

  return (
    <Navbar bg="dark" variant="dark">
      <Container>
        <Navbar.Brand href={BOOKS_ROUTE}>Reading Books</Navbar.Brand>
        <Nav className="justify-content-end">
          {user.isAuth ? (
            <>
              <Link to={`${USER_ROUTE}/${id}`} className="nav-link" title="Перейти в профиль">
                <img 
                  src={`${process.env.REACT_APP_API_URL}/User${id}.jpg`} 
                  className="rounded-circle" 
                  style={{ width: '40px', height: '40px', objectFit: 'cover', marginRight: '10px' }} 
                  alt="Avatar" 
                />
                <span className="d-none d-md-inline">{name}</span>
              </Link>
              {role === 'ADMIN' && (
                <Button variant="outline-light" href={ADMIN_ROUTE} className="mx-2 d-flex align-items-center">
                  <span className="d-inline-block text-truncate">Админ-панель</span>
                </Button>
              )}
              {role === 'AUTHOR' && (
                <Button variant="outline-light" href="/author-panel" className="mx-2 d-flex align-items-center">
                  <span className="d-inline-block text-truncate">Панель автора</span>
                </Button>
              )}
              <Button variant="outline-light" onClick={logOut} className="mx-2">Выйти</Button>
            </>
          ) : (
            <>
              <Button variant="outline-light" href={LOGIN_ROUTE} className="mx-2">Войти</Button>
              <Button variant="outline-light" href={REGISTRATION_ROUTE} className="mx-2">Зарегистрироваться</Button>
            </>
          )}
        </Nav>
      </Container>
    </Navbar>
  );
});
export default NavBar;

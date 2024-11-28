import React, { useContext, useState } from 'react';
import { Container, Form, Card, Button, Row } from 'react-bootstrap';
import { BOOKS_ROUTE, REGISTRATION_ROUTE } from '../utils/const';
import { LOGIN_ROUTE } from '../utils/const';
import { NavLink, useLocation, useNavigate } from 'react-router-dom';
import { registration, login } from '../http/userAPI';
import { observer } from 'mobx-react-lite';
import { Context } from '../index';
import { Alert } from 'react-bootstrap';
import { useEffect } from 'react';

const Auth = observer(() => {
  const location = useLocation();
  console.log(location);
  const { user } = useContext(Context);
  const isLogin = location.pathname === LOGIN_ROUTE;
  const navigate = useNavigate();
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [emailError, setEmailError] = useState('');
  const [passwordError, setPasswordError] = useState('');

  let [alertshow, setAlertshow] = React.useState(false);
  const [variant, setVariant] = React.useState('success');
  const [alertText, setAlertText] = React.useState('Книга успешно изменена');
  const [role, setRole] = useState('USER');

  const validateEmail = () => {
    // Простая проверка наличия символа @ в адресе электронной почты
    const isValid = email.includes('@');
    setEmailError(isValid ? '' : 'Введите корректный email');
    return isValid;
  };

  const validatePassword = () => {
    // Пример проверки длины пароля
    const isValid = password.length >= 3;
    setPasswordError(isValid ? '' : 'Пароль должен содержать не менее 3 символов');
    return isValid;
  };

  const click = async () => {
    try {
        let data;
        if (isLogin) {
            data = await login(email, password);
        } else {
            data = await registration(email, password, role);
            console.log(data);
        }
        user.setUser(data);
        user.setIsAuth(true);
        navigate(BOOKS_ROUTE, {}, { key: Math.random().toString() });
        window.location.reload();
    } catch (e) {
        setAlertshow(true);
        setVariant('danger');
        setAlertText('Произошла ошибка: ' + e.response.data.message);
    }
  };

  return (
    <Container
      className="d-flex justify-content-center align-items-center"
      style={{ height: window.innerHeight - 54 }}
    >
      <Card style={{ width: 450 }} className="p-5">
        {alertshow && (
          <Alert variant={variant} className="mt-3" onClose={() => setAlertshow(false)} dismissible>
            {alertText}
          </Alert>
        )}
        <h2 className="m-auto">{isLogin ? 'Авторизация' : 'Регистрация'}</h2>
        <Form className="d-flex flex-column">
          <Form.Control
            className={`mt-3 ${emailError && 'is-invalid'}`}
            placeholder="Введите ваш email..."
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            onBlur={validateEmail} // Проверяем поле ввода при потере фокуса
          />
          {emailError && <div className="invalid-feedback">{emailError}</div>}
          <Form.Control
            className={`mt-3 ${passwordError && 'is-invalid'}`}
            placeholder="Введите ваш пароль..."
            type="password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            onBlur={validatePassword} // Проверяем поле ввода при потере фокуса
          />
          <Form.Select
              className="mt-3"
              value={role}
              onChange={(e) => setRole(e.target.value)}
              disabled={isLogin} // Скрываем выбор роли при авторизации
          >
              <option value="USER">Пользователь</option>
              <option value="AUTHOR">Автор</option>
          </Form.Select>
          {passwordError && <div className="invalid-feedback">{passwordError}</div>}
          <Row className="d-flex justify-content mt-3 m-2">
            {isLogin ? (
              <div>
                Нет аккаунта? <NavLink to={REGISTRATION_ROUTE}>Зарегистрируйтесь!</NavLink>
              </div>
            ) : (
              <div>
                Есть аккаунт? <NavLink to={LOGIN_ROUTE}>Войдите!</NavLink>
              </div>
            )}
            <Button className="pr-10" variant="outline-success" onClick={click}>
              {isLogin ? 'Войти' : 'Зарегистрироваться'}
            </Button>
          </Row>
        </Form>
      </Card>
    </Container>
  );
});

export default Auth;

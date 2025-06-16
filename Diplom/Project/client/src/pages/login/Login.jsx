import React, {useEffect, useRef, useState} from "react";
import {Link, useNavigate} from "react-router-dom";
import {
  Alert,
  Avatar,
  Box,
  Button,
  Center,
  Container,
  Divider, Group,
  Paper,
  PasswordInput,
  Stack,
  Text,
  TextInput,
  Title, useMantineColorScheme,
  useMantineTheme,
} from "@mantine/core";
import {IconAlertCircle, IconArrowRight, IconLock, IconUser} from "@tabler/icons-react";
import Store from "../../store/store";
import logo from "../../images/logo.png";
import ImageBackground from "../../images/background.jpg";
import ThemeSwitcher from "../../components/header/ThemeSwitcher";

const Login = () => {
  const [credentials, setCredentials] = useState({
    login: undefined,
    password: undefined,
  });
  const [error, setError] = useState(null);
  const [loading, setLoading] = useState(false);
  const navigate = useNavigate();
  const messageRef = useRef(null);
  const inputPasswordRef = useRef(null);
  const inputLoginRef = useRef(null);
  const store = new Store();
  const theme = useMantineTheme();
  const {colorScheme} = useMantineColorScheme()

  const handleChange = (e) => {
    const { id, value } = e.target;
    setCredentials((prev) => ({ ...prev, [id]: value }));
    setError(null); // Сбрасываем ошибку при изменении полей
  };

  const handleClick = async (e) => {
    e.preventDefault();
    try {
      setError(null);
      setLoading(true);
      
      if (inputPasswordRef.current) {
        inputPasswordRef.current.classList.remove("error");
      }
      if (inputLoginRef.current) {
        inputLoginRef.current.classList.remove("error");
      }

      const res = await store.login(credentials.login, credentials.password);
      navigate("/AdminHome");
    } catch (err) {
      const error = err.response.data;

      if (error.errors) {
        if (error.errors.includes("password")) {
          inputPasswordRef.current?.classList.add("error");
        }
        if (error.errors.includes("login")) {
          inputLoginRef.current?.classList.add("error");
        }
      }

      setError(error.message);
    } finally {
      setLoading(false);
    }
  };

  return (
      <Box
          style={{
            minHeight: "100vh",
            width: "100%",
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
            flexDirection: "column",
            
          }}
      >
        <Box
            style={{
              position: 'absolute',
              top: 0,
              left: 0,
              right: 0,
              bottom: 0,
              backgroundImage: `linear-gradient(to bottom, rgba(0, 0, 0, 0) 60%, rgba(0, 0, 0, 0.6) 100%), url(${ImageBackground})`,
              backgroundSize: "cover",
              backgroundRepeat: "no-repeat",
              backgroundPosition: "center",
              filter: colorScheme === 'dark' ? 'brightness(60%)' : 'brightness(120%)',
              zIndex: -1
            }}
        />
        <Container style={{position: 'absolute', top: '10px', right: '10px'}}>
          <ThemeSwitcher />
        </Container>
        <Container size="md">
        <Stack spacing={30} justify="center" align="center">
          <Stack spacing="xs" align="center">
            <Text size="xl" fw={700} style={{fontSize: "36px"}} align="center" c="white">
              Добро пожаловать в онлайн-кинотеатр Hm
            </Text>
            <Text size="lg" align="center" c="white">
              Войдите в свой аккаунт для продолжения
            </Text>
          </Stack>

          <Paper radius="md" p="xl" withBorder shadow="md" style={{ minWidth: '450px', maxWidth: '450px' }}>
            <Stack spacing="xl">
              <Center>
                <Avatar
                  src={logo}
                  size={132}
                  radius="xl"
                  alt="User avatar"
                />
              </Center>
              
              {error && (
                  <Alert
                      icon={<IconAlertCircle size="1rem" />}
                      color="red"
                      variant="filled"
                      style={{ wordBreak: 'break-word', whiteSpace: 'normal' }}
                  >
                    {error}
                  </Alert>
              )}

              <form onSubmit={handleClick}>
                <Stack spacing="md">
                  <TextInput
                    ref={inputLoginRef}
                    id="login"
                    label="Логин"
                    placeholder="Введите ваш логин"
                    icon={<IconUser size="1rem" />}
                    value={credentials.login || ""}
                    onChange={handleChange}
                    required
                    size="md"
                    error={error && error.includes("login") ? "Неверный логин" : null}
                  />

                  <PasswordInput
                    ref={inputPasswordRef}
                    id="password"
                    label="Пароль"
                    placeholder="Введите ваш пароль"
                    icon={<IconLock size="1rem" />}
                    value={credentials.password || ""}
                    onChange={handleChange}
                    required
                    size="md"
                    error={error && error.includes("password") ? "Неверный пароль" : null}
                  />

                  <Button
                    type="submit"
                    size="md"
                    loading={loading}
                    rightIcon={<IconArrowRight size="1.1rem" />}
                    fullWidth
                  >
                    Войти
                  </Button>
                </Stack>
              </form>

              <Divider label="Нет аккаунта?" labelPosition="center" />

              <Button
                component={Link}
                to="/register"
                variant="light"
                color={theme.primaryColor}
                size="md"
                fullWidth
              >
                Зарегистрироваться
              </Button>
            </Stack>
          </Paper>
        </Stack>
      </Container>
    </Box>
  );
};

export default Login;
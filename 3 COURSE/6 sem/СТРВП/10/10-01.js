const express = require('express');
const jwt = require('jsonwebtoken');
const bodyParser = require('body-parser');
const dotenv = require('dotenv');
const session = require('express-session');
const userRouter = require('./routers/user.router');
const reposRouter = require('./routers/repos.router');
const { PrismaClient } = require('@prisma/client');
const prisma = new PrismaClient();
const app = express();

const PORT = 3000;

dotenv.config();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(session({ secret: 'secret', resave: false, saveUninitialized: true }));

const generateAccessToken = (user) => {
  return jwt.sign(user, process.env.ACCESS_TOKEN_SECRET, { expiresIn: '10m' });
}

// Middleware для проверки ролей пользователей и ограничения доступа к маршрутам
const accessControlMiddleware = (req, res, next) => {
  try {
    const userRole = req.session.user ? req.session.user.role : 'guest';

    const allowedRoutes = {
      admin: ['/api/repos', '/logout', '/profile'],
      user: ['/api/user', '/logout', '/profile'],
      guest: ['/login', '/register']
    };

    if (!allowedRoutes[userRole].includes(req.path)) {
      return res.status(403).send('Доступ запрещен');
    }

    next();
  } catch (error) {
    console.error('Ошибка при проверке доступа:', error);
    res.status(500).json({ error: error.message });
  }
};

app.use(accessControlMiddleware);
app.use("/api/user", userRouter);
app.use("/api/repos", reposRouter);

app.get("/register", (req, res) => {
  res.send(`
        <form action="/register" method="post">
            <div>
                <label for="username">Username:</label>
                <input type="text" id="username" name="username">
            </div>
            <div>
                <label for="password">Password:</label>
                <input type="password" id="password" name="password">
            </div>
            <div>
                <input type="submit" value="Register">
            </div>
        </form>
    `);
});

app.post('/register', async (req, res) => {
  try {
    const { username, password } = req.body;
    if (!username || !password) {
      return res.status(400).send('Не указаны все необходимые данные для регистрации');
    }

    const user = await prisma.users.findUnique({ where: { username: username } });

    if (user) {
      return res.status(400).send('Пользователь с таким именем уже существует');
    } else {
      await prisma.users.create({
        data: {
          username: username,
          password: password,
          role: "user"
        }
      });
      const token = generateAccessToken(user);
      return res.status(201).send('Пользователь успешно создан' + token);
    }
  } catch (e) {
    console.log(e);
    return res.status(500).send(e.message);
  }
});

app.get('/login', (req, res) => {
  res.send(`<form action="/login" method="post">
            <div>
        <label>Username:</label>
        <input type="text" name="username">
            </div>
             <div>
        <label>Password:</label>
        <input type="password" name="password">
            </div>
        <div>
        <input type="submit" value="Log In"></div>
        </form>`);
});

app.post('/login', async (req, res) => {
  const { username, password } = req.body;
  const user = await prisma.users.findUnique({ where: { username: username } });
  if (user && user.password === password) {
    req.session.user = user; // Устанавливаем пользовательские данные в сессию
    const token = generateAccessToken(user);
    res.send('Вы успешно вошли в систему ' + token);
  } else {
    res.status(401).send('Неправильный логин или пароль');
  }
});

const authenticateSession = (req, res, next) => {
  if (req.session && req.session.user) {
    next();
  } else {
    res.status(401).send('Вы не авторизованы');
  }
}

app.get('/profile', authenticateSession, (req, res) => {
  res.json({ user: req.session.user });
});

app.get('/logout', (req, res) => {
  req.session.destroy();
  res.send('Вы успешно вышли из системы');
});

app.all('*', (req, res) => {
  res.status(404).send('404 Not Found');
});

const main = () => {
  try {
    app.listen(PORT, () => {
      console.log(`Server is listening at http://localhost:${PORT}`);
    });
  } catch (e) {
    console.error(e);
  }
}

main();

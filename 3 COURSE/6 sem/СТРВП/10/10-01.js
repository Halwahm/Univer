const express = require('express');
const jwt = require('jsonwebtoken');
const bodyParser = require('body-parser');
const dotenv = require('dotenv');
const session = require('express-session');
const userRouter = require('./routers/user.router');
const reposRouter = require('./routers/repos.router');
const { PrismaClient } = require('@prisma/client');
const { AbilityBuilder, Ability } = require('@casl/ability');
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

const accessControlMiddleware = (req, res, next) => {
  try {
    const userRole = req.session.user ? req.session.user.role : 'guest';
    const ability = defineAbilitiesFor(userRole);
    req.ability = ability;

    const allowedRoutes = {
      admin: ['/api/repos', '/api/repos/:id', '/api/repos/:id/commits', '/api/repos/:id/commits/:commitId', 
      '/api/user', '/api/user/:id', '/api/repos/commits/:id',
      '/logout', '/profile', '/api/ability'],
      user: ['/api/repos', '/api/repos/:id', '/api/repos/:id/commits', '/api/repos/:id/commits/:commitId', 
      '/api/user/:id', '/api/repos/commits/:id',
      '/logout', '/profile', '/api/ability'],
      guest: ['/login', '/register', '/api/ability', '/api/repos', '/api/repos/:id/commits']
    };

    const allowedPaths = allowedRoutes[userRole];
    const isAllowed = allowedPaths.some(route => {
      const pattern = new RegExp(`^${route.replace(/\/:[^/]+/g, '/[^/]+')}$`);
      return pattern.test(req.path);
    });

    if (!isAllowed) {
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
      return res.status(201).send('Пользователь успешно создан');
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
    req.session.user = user; 
    console.log (req.session.user)
    const token = generateAccessToken(user);
    res.send('Вы успешно вошли в систему ' + token);
  } else {
    res.status(401).send('Неправильный логин или пароль');
  }
});

app.get('/api/ability', async (req, res) => {
  try {
    const user = req.session.user || { role: 'guest' }; 
    const ability = req.ability;
    if (!ability) 
      return res.status(401).send('Не удалось определить набор привилегий');

    const userAbilities = defineAbilitiesFor(user);

    res.json({ permissions: userAbilities.rules });
  } catch (error) {
    console.error('Ошибка при получении набора привилегий:', error);
    res.status(500).json({ error: error.message });
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

const defineAbilitiesFor = (user) => {
  const { can, rules } = new AbilityBuilder(Ability);

  if (user.role === 'guest') {
      can('read', 'ability');
      can('read', 'commit');
      can('read', 'repository');
  }

  if (user.role === 'user') {
      can('read', 'ability');
      can('read', 'commit');
      can('read', 'repository');
      can('create', 'repository', {authorId: user.id});
      can('create', 'commit', {repo: {authorId: user.id}});
      can('update', 'repository', { authorId: user.id });
      can('update', 'commit', { repo: { authorId: user.id } });
      can('delete', 'repository', {authorId: user.id});
      can('delete', 'commit', {repo: {authorId: user.id}});
  }

  if (user.role === 'admin') {
      can('read', 'ability');
      can('read', 'commit');
      can('read', 'repository');
      can('read', 'user');
      can('create', 'repository');
      can('create', 'commit');
      can('update', ['repository', 'commit']);
      can('delete', ['repository', 'commit']);
  }

  return new Ability(rules);
};

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

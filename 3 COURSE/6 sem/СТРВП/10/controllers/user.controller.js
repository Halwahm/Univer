const userService = require('../services/user.service');

class UserController {
  async getAllUsers(req, res) {
    const UserRole = req.session.user.role;
    try {
      const users = await userService.getAllUsers(UserRole);
      res.json(users);
    } catch (error) {
      res.status(500).json({ error: error.message });
    }
  }

  async getUserById(req, res) {
    const { id } = req.params;
    const UserId = req.session.user.id;
    const UserRole = req.session.user.role;
    try {
      const user = await userService.getUserById(id, UserId, UserRole);
      if (!user) {
        res.status(404).json({ error: 'User not found' });
      } else {
        res.json(user);
      }
    } catch (error) {
      res.status(500).json({ error: error.message });
    }
  }
}

module.exports = new UserController();

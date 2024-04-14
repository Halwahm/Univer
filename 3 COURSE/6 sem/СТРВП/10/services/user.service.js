const { PrismaClient } = require('@prisma/client');
const prisma = new PrismaClient();

class UserService {
    async getAllUsers(requestingUserRole) {
        try {
            if (requestingUserRole !== 'admin') {
                throw new Error('User is not allowed to access this resource');
            }
            const users = await prisma.users.findMany();
            return users;
        } catch (error) {
            throw new Error(error.message);
        }
    }
    async getUserById(id, requestingUserId, requestingUserRole) {
        try {
            // Проверяем, совпадает ли запрашиваемый id с id авторизованного пользователя
            if (parseInt(id) !== parseInt(requestingUserId) && requestingUserRole !== 'admin') {
                throw new Error('User is not allowed to access this user data');
            }
            const user = await prisma.users.findUnique({
                where: { id: parseInt(id) }
            });
            if (!user) {
                throw new Error('User with this Id is not found');
            }
            return user;
        } catch (error) {
            throw new Error(error.message);
        }
    }
}

module.exports = new UserService();
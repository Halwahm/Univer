const { PrismaClient } = require('@prisma/client');
const prisma = new PrismaClient();

class ReposService {
    async getAllRepos(){
        const repos = await prisma.repos.findMany();
        return repos;
    }

    async getRepoById(id){
        const repo = await prisma.repos.findUnique({
            where: { id: parseInt(id) }
        });
        if (!repo) {
            throw new Error('Repo with this Id is not found');
        }
        return repo;
    }

    async createRepo(data){
        try {
            if(!data.name) throw new Error('Missing data');
            const isRepoExist = await prisma.repos.findMany({
                where: { name: data.name }
            });
            if(isRepoExist.length) throw new Error('Repo already exist');
            const repo = await prisma.repos.create({
                data: {
                    name: data.name,
                    authorId: parseInt(data.authorId)
                }
            });
            return repo;
        } catch (error) {
            throw new Error(error);
        }
    }

    async updateRepoById(id, newData, userId) {
        try {
            if (!id) throw new Error('Missing repo id');
            const repo = await prisma.repos.findUnique({
                where: { id: parseInt(id) }
            });
            if (!repo) {
                throw new Error('Repo with this Id is not found');
            }
            // Проверяем, что пользователь обновляет свой репозиторий
            if (parseInt(userId) !== parseInt(repo.authorId)) {
                throw new Error('User is not allowed to update this repo');
            }
            if (!newData.name && !newData.authorId) {
                throw new Error('Missing data');
            }
            const isRepoExist = await prisma.repos.findMany({
                where: { name: newData.name }
            });
            if(isRepoExist.length) throw new Error('Repo already exist');
            const updatedRepo = await prisma.repos.update({
                where: { id: parseInt(id) },
                data: {
                    name: newData.name,
                    authorId: parseInt(userId)
                }
            });
            return updatedRepo;
        } catch (error) {
            throw new Error('Unable to update repo: ' + error.message);
        }
    }
    async deleteRepoById(id, userId) {
        try {
            if (!id) throw new Error('Missing repo id');
            // Проверяем, что пользователь удаляет свой репозиторий
            if (parseInt(userId) !== parseInt(repo.authorId)) {
                throw new Error('User is not allowed to delete this repo');
            }
            const repo = await prisma.repos.delete({
                where: { id: parseInt(id) }
            });
            return repo;
        } catch (error) {
            throw new Error('Unable to delete repo: ' + error.message);
        }
    }

    async getReposByIdIncludeCommits(id, userId, userRole){
        try {
            if (!(await this.checkAccess(userRole, userId, id))) {
                throw new Error('User is not allowed to access commits of this repo');
            }
            // Возвращаем репозиторий включая коммиты
            return await prisma.repos.findUnique({
                where: { id: parseInt(id) },
                include: { commits: true }
            });
        } catch (error) {
            throw new Error(error.message);
        }
    }
    
    async getReposByIdIncludeCommit(idRepos, userId, userRole, idCommit){
        try {
            if (!(await this.checkAccess(userRole, userId, idRepos, idCommit))) {
                throw new Error('User is not allowed to access commits of this repo');
            }
            // Возвращаем репозиторий включая только определенный коммит
            return await prisma.repos.findUnique({
                where: { id: parseInt(idRepos) },
                include: { 
                    commits: { 
                        where: { id: parseInt(idCommit) } 
                    } 
                }
            });
        } catch (error) {
            throw new Error(error.message);
        }
    }
     

    async createCommit(data) {
        try {
            if (!data.message || !data.repoId) throw new Error('Missing data');
            if (!(await this.checkAccess(data.userRole, data.userId, data.repoId))) {
                throw new Error('User is not allowed to create commit in this repo');
            }
            const isCommitExist = await prisma.commits.findMany({
                where: { message: data.message }
            });
            if (isCommitExist.length) throw new Error('Commit already exists');
    
            const commit = await prisma.commits.create({
                data: {
                    message: data.message,
                    repoId: parseInt(data.repoId),
                }
            });
            return commit;
        } catch (error) {
            throw new Error('Unable to create commit: ' + error.message);
        }
    }
    
    async updateCommitById(data) {
        try {
            const { id, userId, repoId, userRole } = data;
            if (!id) throw new Error('Missing commit id');
            if (!(await this.checkAccess(userRole, userId, repoId, id))) {
                throw new Error('User is not allowed to update commit in this repo');
            }
            const commit = await prisma.commits.findUnique({
                where: { id: parseInt(id) }
            });
            if (!commit) throw new Error('Commit with this Id is not found');
    
            // Проверяем, что пользователь обновляет коммит в собственном репозитории
            const repo = await prisma.repos.findUnique({
                where: { id: parseInt(commit.repoId) }
            });
            if (!repo) {
                throw new Error('Repo with this Id is not found');
            }
    
            // Проверяем наличие данных для обновления
            if (!data.message && !data.repoId) throw new Error('Missing data');
    
            // Проверяем, что коммит с таким сообщением еще не существует
            const isCommitExist = await prisma.commits.findMany({
                where: { message: data.message }
            });
            if (isCommitExist.length) throw new Error('Commit already exists');
    
            const updatedCommit = await prisma.commits.update({
                where: { id: parseInt(id) },
                data: {
                    message: data.message,
                    repoId: parseInt(data.repoId)
                }
            });
            return updatedCommit;
        } catch (error) {
            throw new Error('Unable to update commit: ' + error.message);
        }
    }
    
    async deleteCommitById(data) {
        try {
            const { id, userId, repoId, userRole } = data;
            if (!id) throw new Error('Missing commit id');
            if (!(await this.checkAccess(userRole, userId, repoId, id))) {
                throw new Error('User is not allowed to delete commit in this repo');
            }
            const commit = await prisma.commits.findUnique({
                where: { id: parseInt(id) }
            });
            if (!commit) throw new Error('Commit with this Id is not found');
    
            // Проверяем, что пользователь удаляет коммит в собственном репозитории
            const repo = await prisma.repos.findUnique({
                where: { id: parseInt(commit.repoId) }
            });
            if (!repo) {
                throw new Error('Repo with this Id is not found');
            }
    
            const deletedCommit = await prisma.commits.delete({
                where: { id: parseInt(id) }
            });
            return deletedCommit;
        } catch (error) {
            throw new Error('Unable to delete commit: ' + error.message);
        }
    }
    
    async checkAccess(userRole, userId, repoId = null, commitId = null) {
        if (userRole === 'admin') {
            return true; 
        }
        if (userRole === 'guest') {
            return true;
        }
        if (repoId) {
            // Проверяем доступ к репозиторию
            const repo = await prisma.repos.findUnique({
                where: { id: parseInt(repoId) }
            });
            if (!repo || parseInt(userId) !== parseInt(repo.authorId)) {
                return false;
            }
        }
        if (commitId) {
            // Проверяем доступ к коммиту
            const commit = await prisma.commits.findUnique({
                where: { id: parseInt(commitId) }
            });
            if (!commit) {
                return false;
            }
        }
        return true; // Пользователь имеет доступ
    }
}

module.exports = new ReposService();
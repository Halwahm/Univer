const ReposService = require('../services/repos.service');

class ReposController {
    async getAllRepos(req, res) {
        try {
            const repos = await ReposService.getAllRepos();
            res.json(repos);
        } catch (error) {
            throw new Error(error.message);
        }
    }

    async getRepoById(req, res) {
        const { id } = req.params;
        try {
            const repo = await ReposService.getRepoById(id);
            if (!repo) {
                res.status(404).json({ error: 'Repo not found' });
            } else {
                res.json(repo);
            }
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async createRepo(req, res) {
        const { id } = req.session.user;
        console.log(id)
        const data = { ...req.body, authorId: id };
        try {
            const repo = await ReposService.createRepo(data);
            res.json(repo);
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async updateRepoById(req, res) {
        const { id } = req.params;
        const newData = req.body;
        const userId = req.session.user.id;
        console.log(userId)
        try {
            const repo = await ReposService.updateRepoById(id, newData, userId);
            res.json(repo);
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async deleteRepoById(req, res) {
        const { id } = req.params;
        const userId = req.session.user.id;
        try {
            const repo = await ReposService.deleteRepoById(id, userId);
            res.json(repo);
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async getReposByIdIncludeCommits(req, res) {
        const { id } = req.params;
        const userId = req.session.user.id;
        const userRole = req.session.user.role;
        try {
            const repo = await ReposService.getReposByIdIncludeCommits(id, userId, userRole);
            if (!repo) {
                res.status(404).json({ error: 'Repo not found' });
            } else {
                res.json(repo);
            }
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async getReposByIdIncludeCommit(req, res) {
        const { id, commitId } = req.params;
        const userId = req.session.user.id;
        const userRole = req.session.user.role;
        try {
            const repo = await ReposService.getReposByIdIncludeCommit(id, userId, userRole, commitId);
            if (!repo) {
                res.status(404).json({ error: 'Repo not found' });
            } else {
                res.json(repo);
            }
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async createCommit(req, res) {
        const userId = req.session.user.id;
        const userRole = req.session.user.role;
        const data = { ...req.body, userId, userRole };
        try {
            const commit = await ReposService.createCommit(data);
            res.json(commit);
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async updateCommitById(req, res) {
        const { id } = req.params;
        const userId = req.session.user.id;
        const userRole = req.session.user.role;
        const data = { ...req.body, userId, userRole, id };
        try {
            const commit = await ReposService.updateCommitById(data);
            res.json(commit);
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }

    async deleteCommitById(req, res) {
        const { id } = req.params;
        const userId = req.session.user.id;
        const userRole = req.session.user.role;
        const data = { ...req.body, userId, userRole, id };
        try {
            const commit = await ReposService.deleteCommitById(data);
            res.json(commit);
        } catch (error) {
            res.status(500).json({ error: error.message });
        }
    }
}

module.exports = new ReposController();
CREATE TABLE "Users" (
    id SERIAL PRIMARY KEY,
    username VARCHAR(255) UNIQUE,
    password VARCHAR(255),
    role VARCHAR(255)
);

CREATE TABLE "Repos" (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255),
    "authorId" INT REFERENCES "Users"(id)
);

CREATE TABLE "Commits" (
    id SERIAL PRIMARY KEY,
    "repoId" INT REFERENCES "Repos"(id),
    message TEXT
);

ALTER TABLE "Repos"
ADD CONSTRAINT fk_author
FOREIGN KEY ("authorId")
REFERENCES "Users"(id);

ALTER TABLE "Commits"
ADD CONSTRAINT fk_repo
FOREIGN KEY ("repoId")
REFERENCES "Repos"(id);

INSERT INTO "Users" (username, password, role) VALUES
  ('user1', 'password1', 'admin'),
  ('user2', 'password2', 'user'),
  ('user3', 'password3', 'user');

-- Предположим, что user1 создал репозитории 1 и 2, user2 создал репозиторий 3
INSERT INTO "Repos" (name, "authorId") VALUES
  ('repo1', 1),
  ('repo2', 1),
  ('repo3', 2);
  
-- Предположим, что в репозитории 1 было 2 коммита, в репозитории 2 - 1 коммит
INSERT INTO "Commits" ("repoId", message) VALUES
  (1, 'Commit 1 in repo 1'),
  (1, 'Commit 2 in repo 1'),
  (2, 'Commit 1 in repo 2');



drop table "Commits";
drop table "Repos";
drop table "Users";
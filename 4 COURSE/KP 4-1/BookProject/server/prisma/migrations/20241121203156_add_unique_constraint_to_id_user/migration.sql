/*
  Warnings:

  - A unique constraint covering the columns `[ID_USER]` on the table `authors` will be added. If there are existing duplicate values, this will fail.

*/
-- CreateIndex
CREATE UNIQUE INDEX `authors_ID_USER_key` ON `authors`(`ID_USER`);

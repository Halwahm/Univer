/*
  Warnings:

  - Added the required column `ID_USER` to the `authors` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
ALTER TABLE `authors` ADD COLUMN `ID_USER` INTEGER NOT NULL;

-- AddForeignKey
ALTER TABLE `authors` ADD CONSTRAINT `authors_ID_USER_fkey` FOREIGN KEY (`ID_USER`) REFERENCES `users`(`ID`) ON DELETE RESTRICT ON UPDATE CASCADE;

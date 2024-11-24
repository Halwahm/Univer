/*
  Warnings:

  - You are about to drop the column `BOOK_STATUS` on the `books` table. All the data in the column will be lost.
  - You are about to drop the column `PRESENCE` on the `user_bookmarks` table. All the data in the column will be lost.

*/
-- AlterTable
ALTER TABLE `books` DROP COLUMN `BOOK_STATUS`;

-- AlterTable
ALTER TABLE `user_bookmarks` DROP COLUMN `PRESENCE`;

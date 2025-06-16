import {  UUID_NAME } from "common";
import { Column, Entity, PrimaryGeneratedColumn } from "typeorm";

@Entity()
export class Genre {
  @PrimaryGeneratedColumn(UUID_NAME)
  id: string;

  @Column({ nullable: false })
  name: string;
}

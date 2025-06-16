import { UUID_NAME } from 'common';
import { Entity, PrimaryGeneratedColumn, Column, OneToMany } from 'typeorm';
import { Auditt } from './auditt.entity';

@Entity()
export class User {
  @PrimaryGeneratedColumn(UUID_NAME)
  id: string;

  @Column({ length: 50 })
  email: string;

  @Column({ length: 255 })
  password: string;

  @Column({ length: 50 })
  name: string;
  @Column({ default: 'Active', length: 10 })
  status: string;
  @Column({ default: 'User', length: 50 })
  role: string;
  @OneToMany(() => Auditt, ticket => ticket.user, { onDelete: 'CASCADE' })
  auditt: Auditt[];
}

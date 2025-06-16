import { Entity, PrimaryGeneratedColumn, Column, ManyToOne } from 'typeorm';

import { UUID_NAME } from 'common';
import { User } from './user.entity';

@Entity()
export class Token {
  @PrimaryGeneratedColumn(UUID_NAME)
  id: string;

  @Column({ length: 500 })
  token: string;

  @ManyToOne(() => User, {
    onDelete: 'CASCADE',
  })
  user: User;
  
  getUserId(): string | undefined {
    return this.user && this.user.id;
  }
}

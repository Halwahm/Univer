import { UUID_NAME } from 'common';
import { Entity, PrimaryGeneratedColumn, Column, ManyToOne, JoinColumn } from 'typeorm';
import { User } from './user.entity';

@Entity()
export class Auditt {
  @PrimaryGeneratedColumn(UUID_NAME)
  id: string;

  @Column({ length: 100 })
  OperationType: string;

  @Column({ length: 100 })
  filmname: string;

  @Column({ type: 'date' })
  date: Date;

  @Column({ type: 'date' })
  datenow: Date;

  @Column({ length: 100 })
  place: string;
  
  @ManyToOne(() => User, { nullable: false ,onDelete: 'CASCADE', })
  @JoinColumn({ name: 'user' })
  user: User;
  
  getUserId(): string | undefined {
    return   (this.user && this.user.id);
  }
}

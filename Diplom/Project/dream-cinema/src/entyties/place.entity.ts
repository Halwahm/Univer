import {
  Entity,
  PrimaryGeneratedColumn,
  Column,
  ManyToOne,
  JoinColumn,
} from 'typeorm';

import { UUID_NAME } from 'common';
import { Hall } from './hall.entity';

@Entity()
export class Place {
  @PrimaryGeneratedColumn(UUID_NAME)
  id: string;

  @Column()
  place: number;

  @ManyToOne(() => Hall, {
    onDelete: 'CASCADE',
    nullable: false,
  })
  @JoinColumn({ name: 'IDHall' })
  hall: Hall;


}

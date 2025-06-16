import { UUID_NAME } from 'common';
import { Entity, PrimaryGeneratedColumn, Column } from 'typeorm';

@Entity()
export class TypePlace {
  @PrimaryGeneratedColumn(UUID_NAME)
  id: string;

  @Column()
  cost_vip: number;

  @Column()
  cost_normal: number;
}

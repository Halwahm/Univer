import { Entity, PrimaryGeneratedColumn, Column, ManyToOne, OneToMany } from 'typeorm';

import { UUID_NAME } from 'common';
import { TypePlace } from './typeplace.entity';
import { Place } from './place.entity';
import { Session } from './session.entity';

@Entity()
export class Hall {
  @PrimaryGeneratedColumn(UUID_NAME)
  id: string;

  @Column({ length: 50 })
  name: string;

  @Column()
  count_rows: number;

  @Column()
  count_place: number;

  @ManyToOne(() => TypePlace, { onDelete: 'CASCADE' })
  type_Plase: string;

  @OneToMany(() => Session, ticket => ticket.hall)
  sessions: Session[];
}

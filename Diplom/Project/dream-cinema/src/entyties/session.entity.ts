import {
  Entity,
  PrimaryGeneratedColumn,
  Column,
  JoinColumn,
  ManyToOne,
  OneToMany
} from 'typeorm';

import { UUID_NAME } from 'common';
import { Hall } from './hall.entity';
import { Film } from './film.entity';
import { Ticket } from './ticket.entity';
@Entity()
export class Session {
  @PrimaryGeneratedColumn(UUID_NAME)
  id: string;

  @Column({ type: 'date' })
  dateSession: Date;

  @Column({ type: 'time' })
  timeSession: Date;

  @ManyToOne(() => Hall, { nullable: false })
  @JoinColumn({ name: 'IDHall' })
  hall: Hall;

  @ManyToOne(() => Film, { nullable: false, onDelete: 'CASCADE' })
  @JoinColumn({ name: 'IDFilm' })
  film: Film;

  @Column({ default: 'Active', length: 10 })
  status: string;

  @OneToMany(() => Ticket, ticket => ticket.session)
  tickets: Ticket[];

  getHallId(): string | undefined {
    return this.hall && this.hall.id;
  }
  getFilmId(): string | undefined {
    return this.film && this.film.id;
  }
}

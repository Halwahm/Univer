import { Column, Entity, JoinColumn, ManyToOne, PrimaryGeneratedColumn } from 'typeorm';

import { UUID_NAME } from 'common';
import { User } from './user.entity';
import { Film } from './film.entity';

@Entity()
export class Favorite {
  @PrimaryGeneratedColumn(UUID_NAME)
  id: string;

  @ManyToOne(() => User, { nullable: false, onDelete: 'CASCADE' })
  @JoinColumn({ name: 'IdUser' })
  user: User;

  @ManyToOne(() => Film, { nullable: false, onDelete: 'CASCADE' })
  @JoinColumn({ name: 'IdFilm' })
  film: Film;

  getUserId(): string | undefined {
    return this.user && this.user.id;
  }
  getFilmId(): string | undefined {
    return this.film && this.film.id;
  }
}

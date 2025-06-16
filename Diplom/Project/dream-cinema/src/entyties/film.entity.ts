import {
  Entity,
  PrimaryGeneratedColumn,
  Column,
  ManyToOne,
  JoinColumn,
} from 'typeorm';
import { Genre } from './genre.entity'; // Import the Genre entity
import { UUID_NAME } from 'common';

@Entity()
export class Film {
  @PrimaryGeneratedColumn(UUID_NAME)
  id: string;

  @Column({ length: 50, nullable: false })
  name: string;

  @Column({ nullable: false })
  year: number;

  @Column({ type: 'time', nullable: false })
  duration: Date;

  @Column({ type: 'date', nullable: false })
  startRelease: Date;

  @Column({ type: 'date', nullable: false })
  endRelease: Date;

  @Column({ length: 500, nullable: false })
  description: string;

  @Column({ nullable: false })
  ageLimit: number;

  @ManyToOne(() => Genre, { nullable: false })
  @JoinColumn({ name: 'IDGenre' })
  genre: Genre;

  @Column({ type: 'bytea', nullable: false })
  img: Buffer;



  getgenreId(): string | undefined {
    return   (this.genre && this.genre.id);
  }
}
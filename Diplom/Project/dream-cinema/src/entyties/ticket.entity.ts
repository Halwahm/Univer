import { Entity, PrimaryGeneratedColumn, ManyToOne, Column, JoinColumn } from 'typeorm';
import { Session } from './session.entity'; // Путь к сущности Session
import { Place } from './place.entity'; // Путь к сущности Place
import { User } from './user.entity'; // Путь к сущности User
import { UUID_NAME } from 'common';

@Entity()
export class Ticket {
  @PrimaryGeneratedColumn(UUID_NAME)
  id: string;

  @ManyToOne(() => Session, {
    onDelete: 'CASCADE',
  })
  session: Session;

  @ManyToOne(() => User, {
    onDelete: 'CASCADE',
  })
  user: User;

  @ManyToOne(() => Place, {
    onDelete: 'CASCADE',
  })
  place: Place;

  @Column({ length: 6000 })
  QR: string;


  @Column({ length: 100 })
  chatr_id: string;

  @Column({ default: 'Active', length: 10 })
  status: string;
  
  getUserId(): string | undefined {
    return this.user && this.user.id;
  }
  getSessionId(): string | undefined {
    return this.session && this.session.id;
  }
  getPlaceId(): string | undefined {
    return this.place && this.place.id;
  }
}

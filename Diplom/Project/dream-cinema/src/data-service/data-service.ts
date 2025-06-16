import { Injectable } from '@nestjs/common';
import { Repository } from 'typeorm';
import { InjectRepository } from '@nestjs/typeorm';

import {
  Genre,
  Film,
  Favorite,
  Ticket,
  Place,
  Session,
  Token,
  Hall,
  TypePlace,
  Auditt,
  User,
} from 'entyties';

@Injectable()
export class DatabaseService {
  constructor(
    @InjectRepository(Genre)
    public genre: Repository<Genre>,
    @InjectRepository(Film)
    public film: Repository<Film>,
    @InjectRepository(Token)
    public token: Repository<Token>,
    @InjectRepository(User)
    public user: Repository<User>,
    @InjectRepository(TypePlace)
    public typeplace: Repository<TypePlace>,
    @InjectRepository(Hall)
    public hall: Repository<Hall>,
    @InjectRepository(Place)
    public place: Repository<Place>,
    @InjectRepository(Session)
    public session: Repository<Session>,
    @InjectRepository(Ticket)
    public ticket: Repository<Ticket>,
    @InjectRepository(Favorite)
    public favorite: Repository<Favorite>,
    @InjectRepository(Auditt)
    public auditt: Repository<Auditt>,
  ) {}
}

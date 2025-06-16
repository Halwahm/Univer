import { BadRequestException, Injectable } from '@nestjs/common';
import { classToPlain } from 'class-transformer';
import { DatabaseService } from 'data-service';
import { CreateFilmDto, UUIDDto, UpdateFilmDto } from 'dto';
import { Film } from 'entyties';
import { DeepPartial, Like } from 'typeorm';
const stripe = require('stripe')(
  'sk_test_51P8Jvj2MUfusCVLsvh1bRhqtZLXPFPkgjwCGsR24tbDpiQN4PO7L3NTRw3w1LLFQ9x4MK7h7TW0aFOxR6y7jJjzP00zJkBI9UQ',
);
@Injectable()
export class FilmService {
  constructor(private readonly databaseService: DatabaseService) {}
  async create(createFilmDto: CreateFilmDto) {
    if (createFilmDto.startRelease >= createFilmDto.endRelease) {
      throw new BadRequestException(
        'Дата начала проката не может быть позже или равна даты оканчания',
        'date',
      );
    }
    const filmName = await this.databaseService.film.findOne({
      where: {
        name: createFilmDto.name,
        year: createFilmDto.year,
      },
    });
    if (filmName) {
      if (
        filmName.name == createFilmDto.name &&
        filmName.year === filmName.year
      ) {
        throw new BadRequestException(
          'Не может быть фильма с одинаковым названием в один год',
          'name',
        );
      }
    }
    const genre = await this.databaseService.genre.findOne({
      where: {
        name: createFilmDto.genre,
      },
    });

    if (!genre) {
      const genre = await this.databaseService.genre.save({
        name: createFilmDto.genre,
      });

      createFilmDto.genre = genre.id;
    } else {
      createFilmDto.genre = genre.id;
    }

    const filmData: DeepPartial<Film> = classToPlain(createFilmDto);

    const createFilm = await this.databaseService.film.save(filmData);
    return createFilm;
  }

  async findAll() {
    const films = await this.databaseService.film.find({
      relations: ['genre'],
    });
    return films;
  }
  async GetFilmHall() {
    const films = await this.databaseService.film.find({});
    const halls = await this.databaseService.hall.find({});
    return { films, halls };
  }
  async GetDataFilm(IdFilm: string) {
    await this.databaseService.session.query('SELECT CheckSession()');
    let places = [];
    const films = await this.databaseService.film.findOne({
      where: {
        id: IdFilm,
      },
      relations: ['genre'],
    });

    const sessions = await this.databaseService.session.find({
      where: {
        film: { id: IdFilm },
        status: 'Active',
      },
      relations: ['hall', 'hall.type_Plase', 'tickets', 'tickets.place'],
    });

    return { films, sessions };
  }

  GetFilmGenre(idGenre: string) {
    return this.databaseService.film.find({
      where: { genre: { id: idGenre } },
      relations: ['genre'],
    });
  }

  async DeleteFilm(idFilm: string) {
const sessions = await this.databaseService.ticket.find({
  relations: [
    'place',
    'user',
    'session',
    'session.film',
    'session.hall',
    'session.hall.type_Plase',
  ],
  where: {
    session: {
      film: {
        id: idFilm,
      },
      status: 'Active',
    },
  },
});
    sessions.forEach(item => {
      const row = item.session.hall.count_rows;
      const place = item.session.hall.count_place;
      let seat = 1;
      let vip_place = [];
      let cheap_place = [];
      let expensiveRowStart = Math.round(row * 0.2);
      let expensiveRowEnd = row - expensiveRowStart;
      let expensiveSeatsInRowStart = Math.round(place * 0.2);
      let expensiveSeatsInRowEnd = place - expensiveSeatsInRowStart;
      for (let i = 1; i <= row; i++) {
        for (let n = 1; n <= place; n++) {
          if (
            i > expensiveRowStart &&
            i <= expensiveRowEnd &&
            n > expensiveSeatsInRowStart &&
            n <= expensiveSeatsInRowEnd
          ) {
            vip_place.push(seat);
          } else {
            cheap_place.push(seat);
          }
          seat++;
        }
      }
      (item as any).coast_set = vip_place.includes(item.place.place)
        ? item.session.hall.type_Plase['cost_vip']
        : item.session.hall.type_Plase['cost_normal'];
    });

    for (const sessionss of sessions) {
      const refund = await stripe.refunds.create({
        charge: sessionss.chatr_id,
        amount: Math.round(sessionss["coast_set"] * 100),
      });
    }
    await this.databaseService.film.delete({
      id: idFilm,
    });
    const films = await this.databaseService.film.find({});
    return films;
  }

  async GetFilmByName(idFilm: string) {
    const films = await this.databaseService.film.find({
      where: {
        name: Like(`%${idFilm}%`),
      },
    });

    return films;
  }
}

import { Injectable } from '@nestjs/common';
import { CreateSessionDto } from '../../dto/session/create.dto';
import { UpdateSessionDto } from '../../dto/session/update.dto';
import { DatabaseService } from 'data-service';
const stripe = require('stripe')(
  'sk_test_51P8Jvj2MUfusCVLsvh1bRhqtZLXPFPkgjwCGsR24tbDpiQN4PO7L3NTRw3w1LLFQ9x4MK7h7TW0aFOxR6y7jJjzP00zJkBI9UQ',
);
@Injectable()
export class SessionService {
  constructor(private readonly databaseService: DatabaseService) {}
  async create(createSessionDto: CreateSessionDto) {
    const film = await this.databaseService.session.save({
      timeSession: createSessionDto.timeSession,
      dateSession: createSessionDto.dateSession,
      hall: { id: createSessionDto.hall },
      film: { id: createSessionDto.film },
    });

    return film;
  }
  async getDataFreeHall(date, hall) {
    const session = await this.databaseService.session.find({
      where: {
        dateSession: date,
        hall: { id: hall },
      },
      relations: ['film'], //
    });
    return session;
  }

  async GetSession() {
    const sessions = await this.databaseService.session.find({
      relations: ['film', 'hall'],
      where: {
        status: 'Active',
      },
    });
    const filteredDatas = sessions.map(item => {
      delete item.film.img;
      return item;
    });

    return filteredDatas;
  }

  findOne(id: number) {
    return `This action returns a #${id} session`;
  }

  update(id: number, updateSessionDto: UpdateSessionDto) {
    return `This action updates a #${id} session`;
  }

  async DeleteSession(idSession: string) {
const sessionss = await this.databaseService.ticket.find({
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
      id: idSession,
      status: 'Active',
    },
  },
});
    sessionss.forEach(item => {
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

    for (const sessionsss of sessionss) {
      const refund = await stripe.refunds.create({
        charge: sessionsss.chatr_id,
        amount: Math.round(sessionsss['coast_set'] * 100),
      });
    }

    await this.databaseService.session.delete({
      id: idSession,
    });
   const sessions = await this.databaseService.session.find({
     relations: ['film', 'hall'],
     where: {
       status: 'Active',
     },
   });
   const filteredDatas = sessions.map(item => {
     delete item.film.img;
     return item;
   });

   return filteredDatas;
  }
}

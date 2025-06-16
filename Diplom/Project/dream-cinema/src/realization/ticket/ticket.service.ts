import { Injectable } from '@nestjs/common';
import { CreateTicketDto } from '../../dto/ticket/create.dto';
import { UpdateTicketDto } from '../../dto/ticket/update.dto';
import { DatabaseService } from 'data-service';
import { Any, In } from 'typeorm';
import * as qrcode from 'qrcode';
import { log } from 'winston';
import * as crypto from 'crypto';

@Injectable()
export class TicketService {
  constructor(private readonly databaseService: DatabaseService) {}

  async BuyTicket(sessions, tickets, id, chatr_id) {
    let massOccupied = [];

    for (let i = 0; i <= tickets.length - 1; i++) {
      const pl = await this.databaseService.place
        .createQueryBuilder('place')
        .leftJoinAndSelect('place.hall', 'hall')
        .leftJoinAndSelect('hall.sessions', 'session')
        .where('place.place = :ticket', { ticket: tickets[i] })
        .andWhere('session.id = :sessionId', { sessionId: sessions })
        .getOne();

      const checkTicket = await this.databaseService.ticket.findOne({
        where: {
          place: { id: pl.id },
          session: { id: sessions },
        },
        relations: ['place'],
      });

      if (checkTicket == null) {
        let qrCodeData = await qrcode.toDataURL(
          `Зал:${pl.hall.name}; Место:${pl.place};`,
        );
        const tick = await this.databaseService.ticket.save({
          user: { id: id },
          place: { id: pl.id },
          session: { id: sessions },
          QR: qrCodeData,
          chatr_id: chatr_id,
        });
        const secretKey = 'mySecretKey';

        const originalText = tick.id;
        const cipher = crypto.createCipher('aes-256-cbc', secretKey);
        let encryptedText = cipher.update(originalText, 'utf8', 'hex');
        encryptedText += cipher.final('hex');
        const updatedQRCodeData = await qrcode.toDataURL(
          `Зал:${pl.hall.name}; Место:${pl.place}; ID:${encryptedText}`,
        );
        // Затем обновите запись в базе данных с новыми данными QR-кода
        const foundUser = await this.databaseService.ticket.update(tick.id, {
          QR: updatedQRCodeData,
        });
      } else {
        massOccupied.push(checkTicket);
      }
    }
    return massOccupied;
  }

  async GetUserIntoSession(idsession) {
    const userinfo = await this.databaseService.ticket.find({
      where: {
        session: { id: idsession },
      },
      relations: [
        'place',
        'user',
        'session',
        'session.film',
        'session.hall',
        'session.hall.type_Plase',
      ],
    });
    userinfo.forEach(item => {
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
    return userinfo;
  }
  async CheckTicketCon(decodedText) {
    const secretKey = 'mySecretKey';
    const decipher = crypto.createDecipher('aes-256-cbc', secretKey);

    const startIndex = decodedText.indexOf('ID:') + 3;

    const idText = decodedText.substring(startIndex);
    let decryptedText = decipher.update(idText, 'hex', 'utf8');
    decryptedText += decipher.final('utf8');

    const userinfo = await this.databaseService.ticket.find({
      where: {
        id: decryptedText,
      },
      relations: ['user', 'place'],
    });
    if (userinfo) {
      const foundUser = await this.databaseService.ticket.update(
        decryptedText,
        {
          status: 'DisActive',
        },
      );
    }
    return userinfo;
  }
  async GetTicketUser(idUser: string) {
    await this.databaseService.session.query('SELECT CheckSession()');

    const tick = await this.databaseService.ticket.find({
      where: { user: { id: idUser } },
      relations: [
        'place',
        'user',
        'session',
        'session.film',
        'session.hall',
        'session.hall.type_Plase',
      ],
    });

    const filteredData = tick
      .filter(item => item.session.status === 'Active')
      .map(item => {
        delete item.session.film.img;
        return item;
      });

    filteredData.forEach(item => {
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

    return filteredData;
  }

  async Dellorder(
    id: string,
    idsession: string
  ) {
    const filmdel = await this.databaseService.ticket.delete({
      id: id,
    });

    const userinfo = await this.databaseService.ticket.find({
      where: {
        session: { id: idsession },
      },
      relations: [
        'place',
        'user',
        'session',
        'session.film',
        'session.hall',
        'session.hall.type_Plase',
      ],
    });
    userinfo.forEach(item => {
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
    return userinfo;
  }

  async DeleteTicket(idTicket: string, id: string) {
    const filmdel = await this.databaseService.ticket.delete({
      id: idTicket,
    });
    const tick = await this.databaseService.ticket.find({
      where: { user: { id: id } },
      relations: [
        'place',
        'user',
        'session',
        'session.film',
        'session.hall',
        'session.hall.type_Plase',
      ],
    });

    const filteredDatas = tick
      .filter(item => item.session.status === 'Active')
      .map(item => {
        delete item.session.film.img;
        return item;
      });

    filteredDatas.forEach(item => {
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
      console.log(vip_place);
      (item as any).coast_set = vip_place.includes(item.place.place)
        ? item.session.hall.type_Plase['cost_vip']
        : item.session.hall.type_Plase['cost_normal'];
    });
    return filteredDatas;
  }
}

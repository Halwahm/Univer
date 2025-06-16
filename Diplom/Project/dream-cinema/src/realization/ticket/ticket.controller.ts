import {
  Controller,
  Get,
  Post,
  Body,
  Patch,
  Param,
  Delete,
  UseGuards,
  Req,
  Res,
} from '@nestjs/common';
import { Response } from 'express';
import { TicketService } from './ticket.service';
import { CreateTicketDto } from '../../dto/ticket/create.dto';
import { UpdateTicketDto } from '../../dto/ticket/update.dto';
import JwtAuthGuard from 'auth/guard/jwt-auth.guard';
import RequestWithUser from 'auth/interface/request-with-user.interface';
import axios from 'axios';
import { log } from 'winston';
// eslint-disable-next-line @typescript-eslint/no-var-requires
const stripe = require('stripe')(
  'sk_test_51P8Jvj2MUfusCVLsvh1bRhqtZLXPFPkgjwCGsR24tbDpiQN4PO7L3NTRw3w1LLFQ9x4MK7h7TW0aFOxR6y7jJjzP00zJkBI9UQ',
);
@Controller('ticket')
export class TicketController {
  constructor(private readonly ticketService: TicketService) {}

  @UseGuards(JwtAuthGuard)
  @Post('BuyTicket')
  async BuyTicket(
    @Req() req: RequestWithUser,
    @Res() res: Response,
    @Body() data: any,
  ) {
    const lineItems = [
      {
        price_data: {
          currency: 'byn',
          product_data: {
            name: 'К оплате',
          },
          unit_amount: Math.round(data.fullPrice * 100),
        },
        quantity: 1,
      },
    ];

    const IdFilm = data.IdFilm;
    const session = await stripe.checkout.sessions.create({
      payment_method_types: ['card'],
      line_items: lineItems,
      mode: 'payment',
      success_url: `http://localhost:3000/Film?ID=${IdFilm}`,
      cancel_url: 'http://localhost:3000/',
    });

    res.send(session.url);
    
    const chatr_id = await this.waitForPaymentCompletion(session.id);
    return this.ticketService.BuyTicket(
      data.sessions,
      data.tickets,
      req.user.id,
      chatr_id
    );
  }

  async waitForPaymentCompletion(sessionId) {
    let tries = 0;
    const maxTries = 25;
    const delay = 1000;

    while (tries < maxTries) {
      const session = await stripe.checkout.sessions.retrieve(sessionId);
      const status = session.status;

      if (status != 'open') {
        const paymentIntentId = session.payment_intent;

      
        const paymentIntent =
          await stripe.paymentIntents.retrieve(paymentIntentId);

    

        return paymentIntent.latest_charge;
      }

      tries++;
      await new Promise(resolve => setTimeout(resolve, delay));
    }
  }

  @Post('GetUserIntoSession')
  findOne(@Body() data: any) {
    return this.ticketService.GetUserIntoSession(data.idsession);
  }
  @Post('CheckTicketCon')
  CheckTicketCon(@Body() data: any) {
    return this.ticketService.CheckTicketCon(data.data.decodedText);
  }
  @UseGuards(JwtAuthGuard)
  @Get('GetTicketUser')
  async GetTicketUser(@Req() req: RequestWithUser) {
    const result = await this.ticketService.GetTicketUser(req.user.id);
    return result;
  }

  @Delete('Dellorder')
 async Dellorder(@Body() data: any) {
    const refund = await stripe.refunds.create({
      charge: data.chatr_id,
      amount: Math.round(data.coast_set * 100),
    });
    return this.ticketService.Dellorder(
      data.id,
      data.idsession,
    );
  }
  @UseGuards(JwtAuthGuard)
  @Delete('DeleteTicket')
  async DeleteTicket(@Body() data: any, @Req() req: RequestWithUser) {

    const refund = await stripe.refunds.create({
      charge: data.chatr_id,
      amount: Math.round(data.coast_set * 100),
    });
    return this.ticketService.DeleteTicket(data.idTicket, req.user.id);
  }
}

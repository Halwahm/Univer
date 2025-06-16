import { Module } from '@nestjs/common';
import { SessionService } from './session.service';
import { SessionController } from './session.controller';
import { FilmService } from 'realization/film';

@Module({
  controllers: [SessionController],
  providers: [SessionService, FilmService],
})
export class SessionModule {}

import { Module } from '@nestjs/common';
import { FilmService } from './film.service';
import { FilmController } from './film.controller';

@Module({
  controllers: [FilmController],
  providers: [FilmService],
})
export class FilmModule {}

import { Controller, Get, Post, Body, Patch, Param, Delete, BadRequestException } from '@nestjs/common';
import { SessionService } from './session.service';
import { CreateSessionDto } from '../../dto/session/create.dto';
import { UpdateSessionDto } from '../../dto/session/update.dto';
import { FilmService } from 'realization/film';

@Controller('session')
export class SessionController {
  constructor(
    private readonly sessionService: SessionService,
    private readonly filmService: FilmService,
  ) {}

  @Post('AddSession')
  async create(@Body() createSessionDto: CreateSessionDto) {
    const FreeHall = await this.sessionService.getDataFreeHall(
      createSessionDto.dateSession,
      createSessionDto.hall,
    );
    const cinema = await this.filmService.GetDataFilm(createSessionDto.film);

    if (
      new Date(cinema.films.endRelease) < new Date(createSessionDto.dateSession)
    ) {
      throw new BadRequestException(`Прокат фильма уже закончен`, 'date');
    }
    if (
      new Date(cinema.films.startRelease) >
      new Date(createSessionDto.dateSession)
    ) {
      throw new BadRequestException(`Прокат фильма еще не начался `, 'date');
    }

    const timeString = `${createSessionDto.timeSession}`;
    const cinDuration = `${cinema.films.duration}`;
    const [hourss, minutess] = cinDuration.split(':');
    const cinDurations = new Date();
    cinDurations.setUTCHours(Number(hourss), Number(minutess), 0, 0);
    const [hours, minutes] = timeString.split(':');
    const times = new Date();
    times.setUTCHours(Number(hours), Number(minutes), 0, 0);
    const StartTime = times.getUTCHours() * 60 + times.getMinutes();
    const timeFilm =
      cinDurations.getUTCHours() * 60 + cinDurations.getMinutes();
    FreeHall.map(item => {
      const cinDurationi = `${item.timeSession}`;
      const [hoursi, minutesi] = cinDurationi.split(':');
      const cinDurationsi = new Date();
      cinDurationsi.setUTCHours(Number(hoursi), Number(minutesi), 0, 0);
      const cinDurationis = `${item.film.duration}`;
      const [hoursis, minutesis] = cinDurationis.split(':');
      const cinDurationsis = new Date();
      cinDurationsis.setUTCHours(Number(hoursis), Number(minutesis), 0, 0);
      const timeOtherSession =
        cinDurationsi.getMinutes() + cinDurationsi.getUTCHours() * 60;
      const timeStartOtherSession =
        cinDurationsis.getMinutes() + cinDurationsis.getUTCHours() * 60;

      if (
        timeFilm + StartTime >= timeStartOtherSession &&
        StartTime <= timeOtherSession + timeStartOtherSession
      ) {
        throw new BadRequestException(
          `В данное время в данном зале идет фильм`,
          'hall',
        );
      }
    });
    const filmData = await this.sessionService.create(createSessionDto);

    return filmData;
  }

  @Get('GetSession')
  GetSession() {
    return this.sessionService.GetSession();
  }

  @Get(':id')
  findOne(@Param('id') id: string) {
    return this.sessionService.findOne(+id);
  }

  @Patch(':id')
  update(@Param('id') id: string, @Body() updateSessionDto: UpdateSessionDto) {
    return this.sessionService.update(+id, updateSessionDto);
  }

  @Delete('DeleteSession')
  DeleteSession(@Body() data: any) {
    return this.sessionService.DeleteSession(data.idSession);
  }
}

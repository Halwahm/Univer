import {
  Controller,
  Get,
  Post,
  Body,
  UseInterceptors,
  UploadedFile,
  UseGuards,
  Delete,
  BadRequestException
} from '@nestjs/common';
import { FilmService } from './film.service';
import { CreateFilmDto } from '../../dto/film/create.dto';
import { FileInterceptor } from '@nestjs/platform-express';
import { UUIDDto } from 'dto';

// import { UpdateFilmDto } from '../../dto/film/update.dto';

@Controller('film')
export class FilmController {
  constructor(private readonly filmService: FilmService) {}

  @Post('AddFilm')
  @UseInterceptors(FileInterceptor('image'))
  async creates(
    @Body() createFilmDto: CreateFilmDto,
    @UploadedFile() file: any,
  ) {


    if (!file) {
      throw new BadRequestException('Добавте постер', 'img');
    }
     createFilmDto.img = file.buffer;
    return await this.filmService.create(createFilmDto);
  }

  @Get('Home')
  async findAll() {
    return await this.filmService.findAll();
  }

  @Post('GetDataFilm')
  async GetDataFilm(@Body() IdFilm: any) {
    return await this.filmService.GetDataFilm(IdFilm.idFilm);
  }

  @Post('GetFilmGenre')
  GetFilmGenre(@Body() idGenre: any) {
    return this.filmService.GetFilmGenre(idGenre.idGenre);
  }

  @Delete('DeleteFilm')
  DeleteFilm(@Body() data: any) {
    return this.filmService.DeleteFilm(data.idFilm);
  }
  @Get('GetFilmHall')
  GetFilmHall() {
    return this.filmService.GetFilmHall();
  }

  @Post('GetFilmByName')
  GetFilmByName(@Body() data: any) {
 
    return this.filmService.GetFilmByName(data.search);
  }
}

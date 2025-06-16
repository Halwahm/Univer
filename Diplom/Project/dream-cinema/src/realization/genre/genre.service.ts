import { Injectable } from '@nestjs/common';
import { DatabaseService } from 'data-service';
import { CreateGenreDto, UpdateGenreDto } from 'dto';



@Injectable()
export class GenreService {
  constructor(private readonly databaseService: DatabaseService) {}
  create(createGenreDto: CreateGenreDto) {
    return this.databaseService.genre.save(createGenreDto);
  }

  findAll() {
    return this.databaseService.genre.find();
  }


}

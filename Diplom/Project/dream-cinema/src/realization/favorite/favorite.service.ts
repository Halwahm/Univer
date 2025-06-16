import { Injectable } from '@nestjs/common';
import { CreateFavoriteDto } from '../../dto/favorite/create.dto';
import { UpdateFavoriteDto } from '../../dto/favorite/update.dto';
import { DatabaseService } from 'data-service';
import { Favorite } from 'entyties';

@Injectable()
export class FavoriteService {
  constructor(private readonly databaseService: DatabaseService) {}

  async GetFavFilm(idUser: string, IdFilm: string) {
    const films = await this.databaseService.favorite.findOne({
      where: {
        film: { id: IdFilm },
        user: { id: idUser },
      },
    });

    return films;
  }

  async removeFavorite(idUser: string, IdFilm: string) {
    const films = await this.databaseService.favorite.delete({
      film: { id: IdFilm },
      user: { id: idUser },
    });

    return films;
  }

  async addFavorite(idUser: string, IdFilm: string) {
    const films = await this.databaseService.favorite.save({
      film: { id: IdFilm },
      user: { id: idUser },
    });

    return films;
  }

  async GetFavoriteFilm(idUser: string) {
    const films = await this.databaseService.favorite.find({
      where: {
        user: { id: idUser },
      },
      relations: ['film'],
    });

    return films;
  }
}

import { Controller, Get, Post, Body, Patch, Param, Delete, Req, UseGuards } from '@nestjs/common';
import { FavoriteService } from './favorite.service';
import { CreateFavoriteDto } from '../../dto/favorite/create.dto';
import { UpdateFavoriteDto } from '../../dto/favorite/update.dto';
import RequestWithUser from 'auth/interface/request-with-user.interface';

import JwtRefreshGuard from 'auth/guard/jwt-refresh.guard';
import JwtAuthGuard from 'auth/guard/jwt-auth.guard';

@Controller('favorite')
export class FavoriteController {
  constructor(private readonly favoriteService: FavoriteService) {}

  @UseGuards(JwtAuthGuard)
  @Post('GetFavFilm')
  findAll(@Req() req: RequestWithUser, @Body() IdFilm: any) {
    return this.favoriteService.GetFavFilm(req.user.id, IdFilm.idFilm);
  }

  @UseGuards(JwtAuthGuard)
  @Post('addFavorite')
  addFavorite(@Req() req: RequestWithUser, @Body() IdFilm: any) {
    return this.favoriteService.addFavorite(req.user.id, IdFilm.idfilm);
  }

  @UseGuards(JwtAuthGuard)
  @Post('removeFavorite')
  removeFavorite(@Req() req: RequestWithUser, @Body() IdFilm: any) {
    return this.favoriteService.removeFavorite(req.user.id, IdFilm.idfilm);
  }

  @UseGuards(JwtAuthGuard)
  @Get('GetFavoriteFilm')
  GetFavoriteFilm(@Req() req: RequestWithUser) {
  
    return this.favoriteService.GetFavoriteFilm(req.user.id);
  }
}

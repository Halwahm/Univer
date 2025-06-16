import { MiddlewareConsumer, Module, NestModule } from '@nestjs/common';
import { MulterModule } from '@nestjs/platform-express';
import { diskStorage } from 'multer';

import { EnvConfigModule } from 'config';
import { GenreModule } from './realization/genre/genre.module';
import { PostgresDataServiceModule } from 'data-service';
import { FilmModule } from './realization/film/film.module';
import { UserModule } from './realization/user/user.module';
import { FavoriteModule } from './realization/favorite/favorite.module';
import { TicketModule } from './realization/ticket/ticket.module';
import { PlaceModule } from './realization/place/place.module';
import { SessionModule } from './realization/session/session.module';
import { TokenModule } from './realization/token/token.module';
import { HallModule } from './realization/hall/hall.module';
import { TypePlaceModule } from './realization/typeplace/typeplace.module';
import { AudittModule } from './realization/auditt/auditt.module';
import { AuthModule } from 'auth';
import { SeedModule } from 'seed';


@Module({
  imports: [
    EnvConfigModule,
    GenreModule,
    PostgresDataServiceModule,
    FilmModule,
    UserModule,
    FavoriteModule,
    TicketModule,
    PlaceModule,
    SessionModule,
    TokenModule,
    HallModule,
    TypePlaceModule,
    AudittModule,
    AuthModule,
    SeedModule,
    MulterModule.register({
      storage: diskStorage({}),
    }),
  ],

})
export class AppModule  {}

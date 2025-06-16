import { ConfigService } from '@nestjs/config';
import { Global, Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';

import { DATABASE_TYPE, ENV_VARIABLES_NAMES } from 'common';
import {
  Genre,
  Film,
  User,
  Favorite,
  Place,
  Ticket,
  Session,
  Token,
  Hall,
  TypePlace,
  Auditt,
} from 'entyties';

import { EnvConfigModule } from 'config';

import { DatabaseService } from './data-service';

@Global()
@Module({
  imports: [
    TypeOrmModule.forRootAsync({
      imports: [EnvConfigModule],
      inject: [ConfigService],
      useFactory: (configService: ConfigService) => ({
        type: DATABASE_TYPE,
        host: configService.get(ENV_VARIABLES_NAMES.HOST),
        port: configService.get(ENV_VARIABLES_NAMES.DATABASE_PORT),
        username: configService.get(ENV_VARIABLES_NAMES.USER),
        password: configService.get(ENV_VARIABLES_NAMES.PASSWORD),
        database: configService.get(ENV_VARIABLES_NAMES.DATABASE_NAME),
        entities: [
          Genre,
          Film,
          User,
          Favorite,
          Place,
          Ticket,
          Session,
          Token,
          Hall,
          TypePlace,
          Auditt,
        ],
        synchronize: true, //TODO: before deploy
        autoLoadEntities: true, //TODO:before deploy
        ssl: !!configService.get(ENV_VARIABLES_NAMES.SSL_TLS),
        extra: {
          ssl: !!configService.get(ENV_VARIABLES_NAMES.SSL_TLS)
            ? {
                PromiseRejectionEvent: false,
              }
            : null,
        },
      }),
    }),
    TypeOrmModule.forFeature([
      Genre,
      Film,
      User,
      Favorite,
      Place,
      Ticket,
      Session,
      Token,
      Hall,
      TypePlace,
      Auditt,
    ]),
  ],
  providers: [DatabaseService],
  exports: [DatabaseService],
})
export class PostgresDataServiceModule {}

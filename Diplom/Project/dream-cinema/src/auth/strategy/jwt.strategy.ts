import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { PassportStrategy } from '@nestjs/passport';
import { Request } from 'express';
import { ExtractJwt, Strategy } from 'passport-jwt';

import TokenPayload from 'auth/interface/token-payload.interface';
import { DatabaseService } from 'data-service';
import { User } from 'entyties';
import { SECRET_KEY } from 'common';

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy) {
  constructor(
    readonly configService: ConfigService,
    readonly databaseService: DatabaseService,
  ) {
    //   super({
    //     jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
    //     secretOrKey: configService.get<string>('ACCESS_TOKEN_SECRET'),
    //     ignoreExpiration: configService.get<boolean>('`IGNORE_EXPIRATION`'),
    //   });
    // }

    super({
      jwtFromRequest: ExtractJwt.fromExtractors([
        JwtStrategy.extractAccessToken,
      ]),
      ignoreExpiration: configService.get<boolean>('IGNORE_EXPIRATION'),
      secretOrKey: configService.get<string>(SECRET_KEY),
    });
  }

  static extractAccessToken(request: Request) {
    const cookies = request?.cookies;
    const accessToken = cookies.accessToken;
    return accessToken;
  }

  public async validate(payload: TokenPayload): Promise<User> {
    const user = await this.databaseService.user.findOne({
      where: { id: payload.id },
    });

    return user;
  }
}

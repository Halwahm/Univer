import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { ExtractJwt, Strategy } from 'passport-jwt';

import { STRATEGIES_NAMES } from 'common';
import { User } from 'entyties';
import { Request } from 'express';

import { AuthService } from 'auth/auth.service';
import TokenPayload from 'auth/interface/token-payload.interface';

@Injectable()
export class JwtRefreshTokenStrategy extends PassportStrategy(
  Strategy,
  STRATEGIES_NAMES.JWT_REFRESH,
) {
  constructor(readonly authService: AuthService) {
    super({
      jwtFromRequest: ExtractJwt.fromExtractors([
        (request: Request) => {
          return request?.cookies?.refreshToken;
        },
      ]),
      secretOrKey: authService.getRefreshToken(),
      passReqToCallback: authService.getJWTPathToCollback(),
    });
  }

  public async validate(
    request: Request,
    payload: TokenPayload,
  ): Promise<User> {
    const refreshToken = request?.cookies?.refreshToken;
    return this.authService.getUserIfRefreshTokenMatches(
      refreshToken,
      payload.id,
    );
  }
}

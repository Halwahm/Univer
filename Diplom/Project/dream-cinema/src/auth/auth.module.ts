import { Module } from '@nestjs/common';
import { JwtModule } from '@nestjs/jwt';

import { ConfigModule, ConfigService } from '@nestjs/config';
import { PassportModule } from '@nestjs/passport';
import { AuthService } from 'auth/auth.service';
import { JWT_EXPIRES_IN, SECRET_KEY } from 'common';
import { LocalStrategy } from './strategy';
import { JwtRefreshTokenStrategy } from './strategy/jwt-refresh-token.strategy';
import { JwtStrategy } from './strategy/jwt.strategy';

@Module({
  imports: [
    ConfigModule.forRoot(),
    PassportModule,
    JwtModule.registerAsync({
      imports: [ConfigModule],
      useFactory: async (configService: ConfigService) => ({
        secret: configService.get<string>(SECRET_KEY),
        signOptions: { expiresIn: configService.get<string>(JWT_EXPIRES_IN) },
      }),
      inject: [ConfigService],
    }),
  ],
  providers: [AuthService, LocalStrategy, JwtRefreshTokenStrategy, JwtStrategy],
})
export class AuthModule {}

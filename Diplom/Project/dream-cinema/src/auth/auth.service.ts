import {
  BadRequestException,
  ForbiddenException,
  Injectable,
  NotAcceptableException,
  NotFoundException,
  UnauthorizedException,
} from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import * as bcrypt from 'bcrypt';
import * as cookie from 'cookie';

import { User } from 'entyties';

import { DatabaseService } from 'data-service';

import { JwtService } from '@nestjs/jwt';
import { ACCESS_TOKEN, ENV_VARIABLES_NAMES, REFRESH_TOKEN } from 'common';
import RequestWithUser from './interface/request-with-user.interface';
import { AccessTokenResponse } from './response/access-token.response';
import { LoginResponse } from './response/login.response';

@Injectable()
export class AuthService {
  constructor(
    private readonly jwtService: JwtService,
    private readonly configService: ConfigService,
    private readonly databaseService: DatabaseService,
  ) {}

  public getRefreshToken() {
    return this.configService.get<string>('REFRESH_TOKEN_SECRET');
  }

  public getJWTPathToCollback() {
    return this.configService.get<boolean>('JWT_REFRESH_PASS_TO_CALLBACK');
  }

  async validateUser(email: string, password: string): Promise<User> {

    const user = await this.databaseService.user.findOne({ where: { email } });
    if (!user) {
      throw new NotAcceptableException('Неверный логин или пароль');
    }

    const passwordValid = await bcrypt.compare(password, user.password);

    const isAuthenticated = user && passwordValid;
    if (!isAuthenticated) {
      throw new UnauthorizedException(`Неверный логин или пароль`);
    }

    return user;
  }

  async login({ user, res }: RequestWithUser): Promise<LoginResponse> {
    try {
      const { email, id } = user;
      const fondedUser = await this.databaseService.user.findOne({
        where: { id },
      });
      if (!fondedUser)
        throw new NotFoundException(`User with such id ${id} does not exist`);
      if (!user)
        throw new NotFoundException(`User with such id ${id} does not exist`);
if (fondedUser.status==="DisActive"){
 throw new NotAcceptableException('Сожалею, но вы заблокированы, обратитесь к администратору');
} 
const { role } = user;

      const payload = { id, email, role };

      const refreshToken = this.jwtService.sign(payload, {
        secret: this.configService.get<string>(
          ENV_VARIABLES_NAMES.REFRESH_TOKEN_SECRET,
        ),
        expiresIn: this.configService.get<string>(
          ENV_VARIABLES_NAMES.REFRESH_TOKEN_EXPIRATION,
        ),
      });

      const accessToken = this.jwtService.sign(payload, {
        secret: this.configService.get<string>(
          ENV_VARIABLES_NAMES.ACCESS_TOKEN_SECRET,
        ),
        expiresIn: this.configService.get<string>(
          ENV_VARIABLES_NAMES.ACCESS_TOKEN_EXPIRATION,
        ),
      });


      const session = await this.databaseService.token.findOne({
        where: { user: { id: payload.id } },
      });

      if (!session) {
        this.databaseService.token.save({
          user: { id: payload.id },
          token: refreshToken,
        });
      }

      this.databaseService.token.update(
        { user: { id: payload.id } },
        { token: refreshToken },
      );

      res.cookie(ACCESS_TOKEN, accessToken);
      res.cookie(REFRESH_TOKEN, refreshToken);

      const accessTokenAuthorized = this.jwtService.sign(payload, {
        secret: this.configService.get<string>(
          ENV_VARIABLES_NAMES.ACCESS_TOKEN_SECRET,
        ),
        expiresIn: this.configService.get<string>(
          ENV_VARIABLES_NAMES.ACCESS_TOKEN_EXPIRATION,
        ),
      });

      return {
        accessToken: accessTokenAuthorized,
        refreshToken,
        user,
      };
    } catch (error) {
      throw new BadRequestException(
        `Ошибка входа ${user.email}: ${error.message}`,
      );
    }
  }

  public async getUserIfRefreshTokenMatches(
    refreshToken: string,
    userId: string,
  ): Promise<User> {
    const refreshTokenFromDb = await this.databaseService.token.findOne({
      where: { user: { id: userId } },
    });

    if (!refreshTokenFromDb)
      throw new NotFoundException(
        `Refresh token for user with id ${userId} does not exist `,
      );

    const { token } = refreshTokenFromDb;

    if (refreshToken !== token) {
      throw new ForbiddenException(`Access denied, userId ${userId}`);
    }

    const user = await this.databaseService.user.findOne({
      where: { id: userId },
    });
    return user;
  }

  public async getCurrentUser(req: RequestWithUser): Promise<User> {
    const user = await this.databaseService.user.findOne({
      where: { id: req.user.id },
    });

    return user;
  }

  public async refresh(req: RequestWithUser): Promise<AccessTokenResponse> {
    const payload = {
      email: req.user.email,
      id: req.user.id,
      role: req.user.role,
    };

    const accessToken = this.jwtService.sign(payload, {
      secret: this.configService.get<string>(
        ENV_VARIABLES_NAMES.ACCESS_TOKEN_SECRET,
      ),
      expiresIn: this.configService.get<string>(
        ENV_VARIABLES_NAMES.ACCESS_TOKEN_EXPIRATION,
      ),
    });

    const refreshToken = this.jwtService.sign(payload, {
      secret: this.configService.get<string>(
        ENV_VARIABLES_NAMES.REFRESH_TOKEN_SECRET,
      ),
      expiresIn: this.configService.get<string>(
        ENV_VARIABLES_NAMES.REFRESH_TOKEN_EXPIRATION,
      ),
    });

    const stats = await this.databaseService.token.update(
      { user: { id: payload.id } },
      { token: refreshToken },
    );

    if (!stats.affected)
      throw new NotFoundException(
        `Not found session with user id ${payload.id} to update it`,
      );

    const refreshTokenCookie = cookie.serialize('refreshToken', refreshToken, {
      httpOnly: this.configService.get<boolean>(
        ENV_VARIABLES_NAMES.COOKIE_HTTP_ONLY,
      ),
      path: this.configService.get<string>(ENV_VARIABLES_NAMES.COOKIE_PATH),
      maxAge: this.configService.get<number>(
        ENV_VARIABLES_NAMES.COOKIE_MAX_AGE,
      ),
    });

    req.res.setHeader('Set-Cookie', refreshTokenCookie);

    return { accessToken };
  }
}

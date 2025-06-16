import { Body, Controller, Post, Req, UseGuards } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import * as bcrypt from 'bcrypt';

import { RegisterUserDto } from 'dto';
import { User } from 'entyties';
import { UserService } from 'realization';
import { SALT_OR_ROUNDS } from '../common/constants/auth/salt.constants';
import { AuthService } from './auth.service';
import JwtRefreshGuard from './guard/jwt-refresh.guard';
import RequestWithUser from './interface/request-with-user.interface';
import { AccessTokenResponse } from './response/access-token.response';

@Controller('auth')
export default class AuthController {
  constructor(
    private authService: AuthService,
    private usersService: UserService,
  ) {}

  @Post('/sign-up')
  async createUser(@Body() createUserDto: RegisterUserDto): Promise<User> {
    const saltOrRounds = SALT_OR_ROUNDS;
    const hashedPassword = await bcrypt.hash(
      createUserDto.password,
      saltOrRounds,
    );
    createUserDto.password = hashedPassword;
    const result = await this.usersService.create(createUserDto);
    return result;
  }

  @UseGuards(AuthGuard('local'))
  @Post('sign-in')
  async login(@Req() req: RequestWithUser) {
    return this.authService.login(req);
  }

  @UseGuards(JwtRefreshGuard)
  @Post('refresh')
  public refresh(@Req() req: RequestWithUser): Promise<AccessTokenResponse> {
    return this.authService.refresh(req);
  }
}

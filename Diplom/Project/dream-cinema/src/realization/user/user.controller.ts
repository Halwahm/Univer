import {
  BadRequestException,
  Body,
  Controller,
  Delete,
  Get,
  Post,
  Put,
  Req,
  UseGuards,
} from '@nestjs/common';
import * as bcrypt from 'bcrypt';

import { RegisterUserDto } from 'dto';

import { AuthGuard } from '@nestjs/passport';
import { AccessTokenResponse } from 'auth';
import { AuthService } from 'auth/auth.service';
import JwtRefreshGuard from 'auth/guard/jwt-refresh.guard';
import RequestWithUser from 'auth/interface/request-with-user.interface';
import { SALT_OR_ROUNDS, STRATEGIES_NAMES } from 'common';
import { User } from 'entyties';
import { UserService } from './user.service';
import JwtAuthGuard from 'auth/guard/jwt-auth.guard';

@Controller('user')
export class UserController {
  constructor(
    private readonly userService: UserService,
    private readonly authService: AuthService,
  ) {}

  @Post('/sign-up')
  async createUser(@Body() createUserDto: RegisterUserDto): Promise<User> {
    const emailUser = await this.userService.findUserEmail(createUserDto.email);

    if (emailUser.length !== 0) {
      throw new BadRequestException(
        `Email:Пользователь с таким email ${createUserDto.email} уже есть`,
      );
    }
    const saltOrRounds = SALT_OR_ROUNDS;

    const hashedPassword = await bcrypt.hash(
      createUserDto.password,
      saltOrRounds,
    );
    createUserDto.password = hashedPassword;
    const result = await this.userService.create(createUserDto);
    return result;
  }

  @UseGuards(AuthGuard([STRATEGIES_NAMES.LOCAL]))
  @Post('sign-in')
  async login(@Req() req: RequestWithUser) {
    return this.authService.login(req);
  }

  @UseGuards(JwtRefreshGuard)
  @Get('refresh')
  public refresh(@Req() req: RequestWithUser): Promise<AccessTokenResponse> {
    return this.authService.refresh(req);
  }
  @UseGuards(JwtAuthGuard)
  @Get('GetUsers')
  GetUsers(@Req() req: RequestWithUser) {
    return this.userService.GetUsers(req.user.id);
  }

  @UseGuards(JwtAuthGuard)
  @Get('GetUserById')
  GetUserById(@Req() req: RequestWithUser): Promise<User> {
    return this.userService.findOneById(req.user.id);
  }

  @UseGuards(JwtAuthGuard)
  @Delete('DeleteUser')
  DeleteUser(@Body() data: any, @Req() req: RequestWithUser) {
    return this.userService.DeleteUser(data.idUser, req.user.id);
  }
  @UseGuards(JwtAuthGuard)
  @Delete('UnDeleteUser')
  UnDeleteUser(@Body() data: any, @Req() req: RequestWithUser) {
    return this.userService.UnDeleteUser(data.idUser, req.user.id);
  }
  @UseGuards(JwtAuthGuard)
  @Delete('logout')
  logout(@Req() req: RequestWithUser) {
    return this.userService.logout(req);
  }

  @UseGuards(JwtAuthGuard)
  @Put('ChangeUserInfo')
  async ChangeUserInfo(@Req() req: RequestWithUser, @Body() data: any) {
    const emailUser = await this.userService.findUserEmail(data.email);

    if (emailUser.length !== 0) {
      throw new BadRequestException(
        `Пользователь с таким email ${data.email} уже есть`,
        'email',
      );
    }
    return await this.userService.ChangeUserInfo(
      req.user.id,
      data.name,
      data.email,
      data.password,
    );
  }
}

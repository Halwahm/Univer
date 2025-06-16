import { IsEmail, IsString } from 'class-validator';

import { User } from 'entyties';

type LoginPayload = Pick<User, 'email' | 'password'>;

export class LoginDto implements LoginPayload {
  @IsString()
  @IsEmail()
  email: string;

  @IsString()
  password: string;
}

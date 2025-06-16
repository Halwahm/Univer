import { User } from 'entyties';

export class LoginResponse {
  accessToken: string;

  refreshToken: string;

  user: User;
}

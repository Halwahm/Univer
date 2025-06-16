import { IsEmail, IsNotEmpty, IsString, IsDefined } from 'class-validator';

export class LoginUserDto {
  @IsDefined({ message: 'Поле email обязательно для заполнения' })
  @IsNotEmpty({ message: 'Поле email не должно быть пустым' })
  @IsString({ message: 'Должен быть строкой' })
  @IsEmail({}, { message: 'Введите корректный адрес электронной почты' })
  email: string;
  
  @IsNotEmpty({ message: 'Поле Пароль не должно быть пустым' })
  @IsDefined({ message: 'Поле Пароль обязательно для заполнения' })
  @IsString({ message: 'Пароль должен быть строкой' })
  password: string;
}

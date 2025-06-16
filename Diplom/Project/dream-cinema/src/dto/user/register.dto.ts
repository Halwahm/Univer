import {
  IsDefined,
  IsEmail,
  IsNotEmpty,
  IsString,
  Matches,
  MaxLength,
  MinLength,
} from 'class-validator';

export class RegisterUserDto {
  @IsNotEmpty({ message: 'Email:Поле email не должно быть пустым' })
  @IsString({ message: 'Email:Должен быть строкой' })
  @IsEmail({}, { message: 'Email:Введите корректный адрес электронной почты' })
  @IsDefined({ message: 'Email:Поле email обязательно для заполнения' })
  email: string;

  @IsNotEmpty({ message: 'Password:Поле Пароль не должно быть пустым' })
  @IsDefined({ message: 'Password:Поле Пароль обязательно для заполнения' })
  @IsString({ message: 'Password:Пароль должен быть строкой' })
  @Matches(/^[a-zA-Z0-9!@#$%^&*()_+{}[\]:;<>,.?~\\/`'"|-]{8,30}$/, {
    message:
      'Password:Пароль должен содержать только латинские буквы, цифры и символы. Длина пароля от 8 до 30 символов',
  })
  password: string;

  @IsNotEmpty({ message: 'Name:Поле Имя не должно быть пустым' })
  @IsDefined({ message: 'Name:Поле Имя обязательно для заполнения' })
  @IsString({ message: 'Name:Имя должно быть строкой' })
  @MinLength(3, {
    message: 'Name:Имя должно содержать не менее 3 символов',
  })
  @MaxLength(30, {
    message: 'Name:Имя должно содержать не более 30 символов',
  })
  @Matches(/^[a-zA-Zа-яА-Я]+$/, {
    message:
      'Имя должно содержать только буквы русского или английского алфавита',
  })
  name: string;
}

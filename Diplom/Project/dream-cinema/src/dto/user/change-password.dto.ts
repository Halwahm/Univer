import { IsNotEmpty, IsString, Matches, IsDefined } from 'class-validator';

export class UserPasswordChangeDto {
  @IsDefined({ message: 'Поле Пароль обязательно для заполнения' })
  @IsString({ message: 'Пароль должен быть строкой' })
  @IsNotEmpty({ message: 'Пароль не может быть пустым' })
  password: string;

  @IsDefined({ message: 'Поле Новый пароль обязательно для заполнения' })
  @IsString({ message: 'Новый пароль должен быть строкой' })
  @Matches(/^[a-zA-Z0-9!@#$%^&*()_+{}\[\]:;<>,.?~\\/`'"|-]{8,30}$/, {
    message: 'Новый пароль должен соответствовать заданным правилам',
  })
  @IsNotEmpty({ message: 'Новый пароль не может быть пустым' })
  newPassword: string;
}

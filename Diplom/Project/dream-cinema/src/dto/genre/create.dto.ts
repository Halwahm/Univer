import { IsDefined, IsNotEmpty, IsString, Matches, MaxLength, MinLength } from "class-validator";

export class CreateGenreDto {
  @IsDefined({ message: 'Поле Имя обязательно для заполнения' })
  @IsString({ message: 'Имя должно быть строкой' })
  @Matches(/^[a-zA-Zа-яА-Я]+$/, {
    message:
      'Имя должно содержать только буквы русского или английского алфавита',
  })
  @MinLength(3, { message: 'Имя должно содержать не менее 3 символов' })
  @MaxLength(6, { message: 'Имя должно содержать не более 30 символов' })
  @IsNotEmpty({ message: 'Поле Имя не должно быть пустым' })
  name: string;
}

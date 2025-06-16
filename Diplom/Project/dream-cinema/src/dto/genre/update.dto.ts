import { PartialType } from '@nestjs/mapped-types';
import { CreateGenreDto } from './create.dto';
import { IsDefined, IsNotEmpty, IsString, IsUUID, Length, Matches, MaxLength, MinLength } from 'class-validator';
import { Transform } from 'class-transformer';
import { UUID_LENGTH } from 'common';

export class UpdateGenreDto extends PartialType(CreateGenreDto) {
  @IsDefined({ message: 'Идентификатор должен быть указан' })
  @IsNotEmpty({ message: 'Идентификатор не должен быть пустым' })
  @IsString({ message: 'Идентификатор должен быть строкой' })
  @Transform(({ value }) => value.trim()) // Если нужно убрать пробелы в начале и конце
  @IsUUID(4, { message: 'Некорректный формат UUID' })
  @Length(UUID_LENGTH, UUID_LENGTH, {
    message: 'Идентификатор должен содержать ${UUID_LENGTH} символов',
  })
  id: string;

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

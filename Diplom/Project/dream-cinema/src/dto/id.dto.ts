import { Transform } from 'class-transformer';
import {
  IsDefined,
  IsNotEmpty,
  IsString,
  IsUUID,
  Length,
} from 'class-validator';

import { UUID_LENGTH } from 'common';

export class UUIDDto {
  @IsDefined({ message: 'Идентификатор должен быть указан' })
  @IsNotEmpty({ message: 'Идентификатор не должен быть пустым' })
  @IsString({ message: 'Идентификатор должен быть строкой' })
  @Transform(({ value }) => value.trim()) // Если нужно убрать пробелы в начале и конце
  @IsUUID(4, { message: 'Некорректный формат UUID' })
  @Length(UUID_LENGTH, UUID_LENGTH, {
    message: `Идентификатор должен содержать ${UUID_LENGTH} символов`,
  })
  id: string;
}
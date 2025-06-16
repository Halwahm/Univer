import { Transform } from 'class-transformer';
import { IsDefined, IsNotEmpty, IsString, IsUUID, Length } from 'class-validator';
import { UUID_LENGTH } from 'common';
export class CreateSessionDto {
  @IsNotEmpty({ message: 'dateSession:Поля не должены быть пустыми' })
  @IsDefined({ message: 'dateSession:Дата должна быть указана' })
  dateSession: Date;

  @IsNotEmpty({ message: '  timeSession:Поля не должены быть пустыми' })
  @IsDefined({ message: '  timeSession:Время сеанса должно быть указано' })
  timeSession: Date;

  @IsNotEmpty({ message: ' hall:Поля не должены быть пустыми' })
  @IsDefined({ message: ' hall:Идентификатор должен быть указан' })
  @IsString({ message: ' hall:Идентификатор должен быть строкой' })
  @Transform(({ value }) => value.trim()) // Если нужно убрать пробелы в начале и конце
  @IsUUID(4, { message: ' hall:Некорректный формат UUID' })
  @Length(UUID_LENGTH, UUID_LENGTH, {
    message: ` hall:Идентификатор должен содержать ${UUID_LENGTH} символов`,
  })
  hall: string;

  @IsNotEmpty({ message: 'film:Поля не должены быть пустыми' })
  @IsDefined({ message: 'film:Идентификатор должен быть указан' })
  @IsString({ message: 'film:Идентификатор должен быть строкой' })
  @Transform(({ value }) => value.trim()) // Если нужно убрать пробелы в начале и конце
  @IsUUID(4, { message: 'film:Некорректный формат UUID' })
  @Length(UUID_LENGTH, UUID_LENGTH, {
    message: `film:Идентификатор должен содержать ${UUID_LENGTH} символов`,
  })
  film: string;
}

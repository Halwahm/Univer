import { Transform } from 'class-transformer';
import { IsDefined, IsNotEmpty, Max, Min } from 'class-validator';
export class CreateHallDto {
  @IsNotEmpty({ message: 'name:Поля не должены быть пустыми' })
  @IsDefined({ message: 'name:Имя должно быть указано' })
  name: string;

  @Transform(({ value }) => Number(value))
  @IsNotEmpty({ message: 'count_rows:Поля не должены быть пустыми' })
  @Min(1, { message: 'count_rows:Количество рядов не может быть меньше 1' })
  @Max(12, { message: 'count_rows:Количество рядов не может быть больше 12' })
  @IsDefined({ message: 'count_rows:Количество рядов должно быть указано' })
  count_rows: number;

  @Transform(({ value }) => Number(value))
  @IsNotEmpty({ message: 'count_place:Поля не должены быть пустыми' })
  @Min(1, { message: 'count_place:Колличество мест не может быть меньше 1' })
  @Max(12, { message: 'count_place:Колличество мест  не может быть больше 12' })
  @IsDefined({ message: 'count_place:Количество мест должно быть указано' })
  count_place: number;

  @Transform(({ value }) => Number(value))
  @IsNotEmpty({ message: 'coast_vip:Поля не должены быть пустыми' })
  @Min(1, { message: 'coast_vip:Стоимость не может быть меньше 1' })
  @IsDefined({ message: 'coast_vip:Стоимость должна быть указано' })
  coast_vip: number;

  @Transform(({ value }) => Number(value))
  @IsNotEmpty({ message: 'coast_norm:Поля не должены быть пустыми' })
  @Min(1, { message: 'coast_norm:Стоимость не может быть меньше 1' })
  @IsDefined({ message: 'coast_norm:Стоимость должна быть указано' })
  coast_norm: number;
}

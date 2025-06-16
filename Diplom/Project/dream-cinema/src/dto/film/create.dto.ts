import { Transform } from "class-transformer";
import { IsDefined, IsNotEmpty, IsString, Length, Max, Min } from "class-validator";

export class CreateFilmDto {
  @IsNotEmpty({ message: 'name:Поля не должены быть пустыми' })
  @Length(0, 50, {
    message: 'name:Название  должно содержать не более 50 символов',
  })
  @IsDefined({ message: 'name:Имя должно быть указано' })
  @Transform(({ value }) => value.trim())
  name: string;

  @Transform(({ value }) => Number(value))
  @IsNotEmpty({ message: 'year:Поля не должены быть пустым' })
  @Min(1896, { message: 'year:Год должен быть больше 1895' })
  @IsDefined({ message: 'year:Год должен быть указан' })
  year: number;

  @IsNotEmpty({ message: 'startRelease:Поля не должены быть пустыми' })
  @IsDefined({
    message: 'startRelease:Дата начала выпуска должна быть указана',
  })
  startRelease: Date;

  @IsNotEmpty({ message: 'endRelease:Поля не должены быть пустыми' })
  @IsDefined({ message: ' endRelease:Поля не должены быть пустым' })
  endRelease: Date;

  @IsNotEmpty({ message: 'description:Поля не должены быть пустым' })
  @IsString({ message: 'description:Описание должно быть строкой' })
  @Length(0, 500, {
    message: 'description:Описание должно содержать не более 500 символов',
  })
  @IsDefined({ message: 'description:Описание должно быть указано' })
  @Transform(({ value }) => value.trim())
  description: string;

  @Transform(({ value }) => Number(value))
  @IsDefined({ message: 'ageLimit:Поля не должены быть пустыми' })
  @Min(0, { message: 'ageLimit:Возрастное ограничение не может быть меньше 0' })
  @Max(21, {
    message: 'ageLimit:Возрастное ограничение не может быть больше 21',
  })
  ageLimit: number;

  img: Buffer;
  
  @IsNotEmpty({ message: 'duration:Поля не должены быть пустыми' })
  @IsDefined({ message: 'duration:Продолительность должена быть указан' })
  @Transform(({ value }) => value.trim())
  duration: string;

  @IsNotEmpty({ message: 'genre:Поля не должены быть пустыми' })
  @IsDefined({ message: 'genre:Жанр должно быть указано' })
  @Transform(({ value }) => value.trim())
  genre: string;
}

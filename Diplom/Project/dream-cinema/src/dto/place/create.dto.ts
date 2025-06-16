import { IsDefined, IsNotEmpty } from 'class-validator';
export class CreatePlaceDto {
  @IsDefined({ message: 'Тип операции должен быть указан' })
  @IsNotEmpty({ message: 'Тип операции не должен быть пустым' })
  place: number;
}

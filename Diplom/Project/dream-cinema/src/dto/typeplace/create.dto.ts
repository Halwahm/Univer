import { IsDefined, IsNotEmpty } from 'class-validator';
export class CreateTypePlaceDto {
  @IsDefined({ message: 'Тип операции должен быть указан' })
  @IsNotEmpty({ message: 'Тип операции не должен быть пустым' })
  cost_vip: number;
}

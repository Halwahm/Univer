import { IsDefined, IsNotEmpty } from 'class-validator';
export class CreateTokenDto {
  @IsDefined({ message: 'Тип операции должен быть указан' })
  @IsNotEmpty({ message: 'Тип операции не должен быть пустым' })
  token: string;
}

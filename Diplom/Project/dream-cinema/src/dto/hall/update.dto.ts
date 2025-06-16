import { PartialType } from '@nestjs/mapped-types';
import { CreateHallDto } from './create.dto';

export class UpdateHallDto extends PartialType(CreateHallDto) {}

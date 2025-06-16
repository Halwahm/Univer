import { PartialType } from '@nestjs/mapped-types';
import { CreateFilmDto } from './create.dto';

export class UpdateFilmDto extends PartialType(CreateFilmDto) {}

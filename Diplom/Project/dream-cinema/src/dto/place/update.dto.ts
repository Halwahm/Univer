import { PartialType } from '@nestjs/mapped-types';
import { CreatePlaceDto } from './create.dto';

export class UpdatePlaceDto extends PartialType(CreatePlaceDto) {}

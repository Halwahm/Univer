import { PartialType } from '@nestjs/mapped-types';
import { CreateTypePlaceDto } from './create.dto';

export class UpdateTypePlaceDto extends PartialType(CreateTypePlaceDto) {}

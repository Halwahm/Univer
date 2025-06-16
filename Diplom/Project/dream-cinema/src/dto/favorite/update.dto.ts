import { PartialType } from '@nestjs/mapped-types';
import { CreateFavoriteDto } from './create.dto';

export class UpdateFavoriteDto extends PartialType(CreateFavoriteDto) {}

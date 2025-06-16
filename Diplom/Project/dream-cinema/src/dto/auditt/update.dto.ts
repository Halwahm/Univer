import { PartialType } from '@nestjs/mapped-types';
import { CreateAudittDto } from './create.dto';

export class UpdateAudittDto extends PartialType(CreateAudittDto) {}

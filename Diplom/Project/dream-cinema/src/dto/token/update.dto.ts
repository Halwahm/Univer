import { PartialType } from '@nestjs/mapped-types';
import { CreateTokenDto } from './create.dto';

export class UpdateTokenDto extends PartialType(CreateTokenDto) {}

import { PartialType } from '@nestjs/mapped-types';
import { CreateSessionDto } from './create.dto';

export class UpdateSessionDto extends PartialType(CreateSessionDto) {}

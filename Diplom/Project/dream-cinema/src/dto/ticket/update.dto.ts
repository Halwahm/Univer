import { PartialType } from '@nestjs/mapped-types';
import { CreateTicketDto } from './create.dto';

export class UpdateTicketDto extends PartialType(CreateTicketDto) {}

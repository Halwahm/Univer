import { SetMetadata } from '@nestjs/common';

import { METADATA_KEYS, Roles } from 'common';

export const Role = (...roles: Roles[]) =>
  SetMetadata(METADATA_KEYS.role, roles);

import { applyDecorators, SetMetadata, UseGuards } from '@nestjs/common';

import { RoleGuard } from 'auth';
import { METADATA_KEYS, Roles } from 'common';

export const RolesAuth = (...roles: Roles[]) => {
  return applyDecorators(
    SetMetadata(METADATA_KEYS.role, roles),
    UseGuards(RoleGuard),
  );
};

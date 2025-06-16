import {
  CanActivate,
  ExecutionContext,
  ForbiddenException,
  Injectable,
} from '@nestjs/common';
import { Reflector } from '@nestjs/core';

import { METADATA_KEYS, Roles } from 'common';

@Injectable()
export class RoleGuard implements CanActivate {
  constructor(private reflector: Reflector) {}

  canActivate(context: ExecutionContext): boolean {
    const expectedRole = this.reflector.get<Roles>(
      METADATA_KEYS.role,
      context.getHandler(),
    );

    if (!expectedRole) {
      return true;
    }

    const ctx = context.switchToHttp().getRequest();

    const userRole = ctx.user.role;

    if (userRole == expectedRole) {
      return true;
    }

    throw new ForbiddenException('Access denied');
  }
}

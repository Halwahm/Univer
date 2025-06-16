import { Injectable } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';

import { STRATEGIES_NAMES } from 'common';

@Injectable()
export default class JwtRefreshGuard extends AuthGuard(
  STRATEGIES_NAMES.JWT_REFRESH,
) {}

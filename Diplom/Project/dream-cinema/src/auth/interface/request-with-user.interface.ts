import { User } from 'entyties';
import { Request } from 'express';

interface RequestWithUser extends Request {
  user: User;
}

export default RequestWithUser;

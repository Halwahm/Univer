import { Token } from 'entyties';

export interface ICreateSession extends Pick<Token, 'user' | 'token'> {}
